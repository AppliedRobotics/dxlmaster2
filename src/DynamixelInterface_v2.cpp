/*
 * DynamixelInterface_v2.cpp
 */

#include "DynamixelInterface_v2.h"

void DynamixelInterface::transaction(bool aExpectStatus, uint8_t answerSize)
{
    prepareTransaction();
    sendPacket(mPacket);

    if (aExpectStatus)
    {
        receivePacket(mPacket, answerSize);
    }
    else
    {
        mPacket.mStatus = DYN_STATUS_OK;
    }

    endTransaction();
}

void DynamixelInterface::transaction_v2(bool aExpectStatus, uint16_t answerSize)
{
    prepareTransaction();
    sendPacket_v2(mPacket_v2);

    if (aExpectStatus)
        receivePacket_v2(mPacket_v2, answerSize);
    else
        mPacket_v2.mStatus = DYN2_STATUS_OK;

    endTransaction();
}


/**
 *  Ping (0x01)
 */
DynamixelStatus DynamixelInterface::ping(uint8_t aVer, uint8_t aID, uint8_t *rxBuf)
{
    if (aVer == DYN_PROTOCOL_V1) 
    {
        mPacket = DynamixelPacket(aID, DYN_PING, 2, NULL);
        transaction(true);
        return mPacket.mStatus;
    }
    else 
    {
        uint8_t temp[PING_RX_PARAMS_LEN]; // For comp with old code without rx buf pointer
        if (rxBuf == NULL) 
            rxBuf = temp;
        
        mPacket_v2 = DynamixelPacket_v2(aID, PING_TX_LENGTH, INST_PING);
        mPacket_v2.mRxData = rxBuf;
        mPacket_v2.mRxDataLength = PING_RX_PARAMS_LEN;
        transaction_v2(true, PING_RX_LENGTH);
        return mPacket_v2.mStatus;
    }
}

/**
 *  Read (0x02)
 */
DynamixelStatus DynamixelInterface::read(
    uint8_t aVer, 
    uint8_t aID, 
    uint16_t aAddress, 
    uint16_t aRxSize, 
    uint8_t *aRxBuf, 
    uint8_t aStatusReturnLevel)
{
    if (aVer == DYN_PROTOCOL_V1) 
    {
        mPacket = DynamixelPacket(aID, DYN_READ, 4, aRxBuf, (uint8_t)aAddress, (uint8_t)aRxSize);
        transaction(aStatusReturnLevel > 0 && aID != BROADCAST_ID, aRxSize);
        return mPacket.mStatus;
    }
    else
    {
        uint8_t *params = (uint8_t *) malloc(READ_TX_PARAMS_LEN);
        params[0] = (DXL_LOBYTE(aAddress));
        params[1] = (DXL_HIBYTE(aAddress));
        params[2] = (DXL_LOBYTE(aRxSize));
        params[3] = (DXL_HIBYTE(aRxSize));

        mPacket_v2 = DynamixelPacket_v2(aID, READ_TX_LENGTH, INST_READ, params, READ_TX_PARAMS_LEN, /*aAddress,*/ aRxBuf, aRxSize);
        transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, READ_RX_LENGTH + aRxSize);
        free(params);
        return mPacket_v2.mStatus;
    }
}

/**
 *  Write (0x03)
 */
DynamixelStatus DynamixelInterface::write(
    uint8_t aVer, 
    uint8_t aID, 
    uint16_t aAddress,
    uint16_t aTxSize,
    const uint8_t *aTxBuf,
    uint8_t aStatusReturnLevel)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        mPacket = DynamixelPacket(aID, DYN_WRITE, (uint8_t)aTxSize + 3, aTxBuf, (uint8_t)aAddress);
        transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
        return mPacket.mStatus;
    }
    else
    {
        uint16_t params_size = WRITE_TX_PARAMS_LEN + aTxSize;
        uint8_t *params = (uint8_t *)malloc(params_size);
        params[0] = (DXL_LOBYTE(aAddress));
        params[1] = (DXL_HIBYTE(aAddress));
        
        memcpy(&params[WRITE_TX_PARAMS_LEN], aTxBuf, aTxSize);

        mPacket_v2 = DynamixelPacket_v2(aID, WRITE_TX_LENGTH + aTxSize, INST_WRITE, params, params_size/*, aAddress*/);

        transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, WRITE_RX_LENGTH);
        free(params);
        return mPacket_v2.mStatus;
    }
}

/**
 *  Reg Write (0x04)
 */
DynamixelStatus DynamixelInterface::regWrite(
    uint8_t aVer, 
    uint8_t aID, 
    uint16_t aAddress,
    uint16_t aTxSize,
    const uint8_t *aTxBuf,
    uint8_t aStatusReturnLevel)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        mPacket = DynamixelPacket(aID, DYN_REG_WRITE, (uint8_t)aTxSize + 3, aTxBuf, (uint8_t)aAddress);
        transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
        return mPacket.mStatus;
    }
    else
    {
        uint16_t params_size = WRITE_TX_PARAMS_LEN + aTxSize;
        uint8_t *params = (uint8_t *)malloc(params_size);
        params[0] = (DXL_LOBYTE(aAddress));
        params[1] = (DXL_HIBYTE(aAddress));
        
        memcpy(&params[WRITE_TX_PARAMS_LEN], aTxBuf, aTxSize);

        mPacket_v2 = DynamixelPacket_v2(aID, WRITE_TX_LENGTH + aTxSize, INST_REG_WRITE, params, params_size/*, aAddress*/);

        transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, WRITE_RX_LENGTH);
        free(params);
        return mPacket_v2.mStatus;
    }
}

/**
 *  Action (0x05)
 */
DynamixelStatus DynamixelInterface::action(uint8_t aVer, uint8_t aID, uint8_t aStatusReturnLevel)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        mPacket = DynamixelPacket(aID, DYN_ACTION, 2, NULL);
        transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
        return mPacket.mStatus;
    }
    else
    {
        mPacket_v2 = DynamixelPacket_v2(aID, ACTIO_TX_LENGTH, INST_ACTION);
        transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, ACTIO_RX_LENGTH);
        return mPacket_v2.mStatus;
    }
}

/**
 *  Factory Reset (0x06)
 */
DynamixelStatus DynamixelInterface::reset(uint8_t aVer, uint8_t aID, uint8_t aLvl, uint8_t aStatusReturnLevel)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        mPacket = DynamixelPacket(aID, DYN_RESET, 2, NULL);
        transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
        return mPacket.mStatus;
    }
    else
    {
        uint8_t level = aLvl;
        mPacket_v2 = DynamixelPacket_v2(aID, RESET_TX_LENGTH, INST_RESET, &level, 1);
        transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, RESET_RX_LENGTH);
        return mPacket_v2.mStatus;
    }
}

/**
 *  Reboot (0x08)
 */
DynamixelStatus DynamixelInterface::reboot(uint8_t aVer, uint8_t aID,  uint8_t aStatusReturnLevel)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        mPacket = DynamixelPacket(aID, DYN_REBOOT, 2, NULL);
        transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
        return mPacket.mStatus;
    }
    else
    {
        mPacket_v2 = DynamixelPacket_v2(aID, REBOOT_TX_LENGTH, INST_REBOOT);
        transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, REBOOT_RX_LENGTH);
        return mPacket_v2.mStatus;
    }
}

/**
 *  Clear (0x10)
 */
DynamixelStatus DynamixelInterface::clear(
    uint8_t aVer, 
    uint8_t aID, 
    uint16_t aTxSize,
    const uint8_t *aTxBuf,
    uint8_t aStatusReturnLevel)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        return DYN_STATUS_INSTRUCTION_ERROR;
    }
    else
    {
        uint16_t params_size = CLEAR_TX_PARAMS_LEN + aTxSize;
        uint8_t *params = (uint8_t *)malloc(params_size);
        memcpy(params, aTxBuf, aTxSize);

        mPacket_v2 = DynamixelPacket_v2(aID, CLEAR_TX_LENGTH + aTxSize, INST_CLEAR, params, params_size);

        transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, CLEAR_RX_LENGTH);
        free(params);
        return mPacket_v2.mStatus;
    }
}

/**
 *  Backup (0x20)
 */
DynamixelStatus DynamixelInterface::backup(
    uint8_t aVer, 
    uint8_t aID, 
    uint16_t aTxSize,
    const uint8_t *aTxBuf,
    uint8_t aStatusReturnLevel)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        return DYN_STATUS_INSTRUCTION_ERROR;
    }
    else
    {
        uint16_t params_size = BACKUP_TX_PARAMS_LEN + aTxSize;
        uint8_t *params = (uint8_t *)malloc(params_size);
        memcpy(params, aTxBuf, aTxSize);

        mPacket_v2 = DynamixelPacket_v2(aID, BACKUP_TX_LENGTH + aTxSize, INST_BACKUP, params, params_size);

        transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, BACKUP_RX_LENGTH);
        free(params);
        return mPacket_v2.mStatus;
    }
}

    
/**
 *  Sync Read (0x82)
 */
DynamixelStatus DynamixelInterface::syncRead(
    uint8_t aVer, 
    uint8_t nID, 
    const uint8_t *aID, 
    uint16_t aAddress, 
    uint16_t aSize, 
    uint8_t *aRxBuf)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        return DYN_STATUS_INSTRUCTION_ERROR;
    }
    else
    {
        uint16_t params_size = SYNC_READ_TX_PARAMS_LEN + nID;
        uint8_t *params = (uint8_t *)malloc(params_size);

        params[0] = (DXL_LOBYTE(aAddress));
        params[1] = (DXL_HIBYTE(aAddress));
        params[2] = (DXL_LOBYTE(aSize));
        params[3] = (DXL_HIBYTE(aSize));
        memcpy(&params[SYNC_READ_TX_PARAMS_LEN], aID, nID);

        mPacket_v2 = DynamixelPacket_v2(BROADCAST_ID, SYNC_READ_TX_LENGTH + nID, INST_SYNC_READ, params, params_size);

        prepareTransaction();

        sendPacket_v2(mPacket_v2);

        for (size_t i = 0; i < nID; i++)
        {
            DynamixelPacket_v2 xxx = DynamixelPacket_v2(aID[i], 0, 0);

            xxx.mRxDataLength = aSize;
            xxx.mRxData = &aRxBuf[i * aSize];

            receivePacket_v2(xxx, SYNC_READ_RX_LENGTH + aSize);
        }
    
        endTransaction();
        free(params);
        return mPacket_v2.mStatus;

    }

}

/**
 *  Sync Write (0x83)
 */
DynamixelStatus DynamixelInterface::syncWrite(
    uint8_t aVer, 
    uint8_t nID, 
    const uint8_t *aID,
    uint16_t aAddress, 
    uint16_t aSize,
    const uint8_t *aTxBuf)
{
    if (aVer == DYN_PROTOCOL_V1)
    {   	
        mPacket = DynamixelPacket(BROADCAST_ID, DYN_SYNC_WRITE, (aSize + 1) * nID + 4, aTxBuf, aAddress, aSize, nID, aID);
        transaction(false);
        return mPacket.mStatus;
    }
    else
    {
        uint16_t params_size = SYNC_WRITE_TX_PARAMS_LEN + nID * aSize;
        uint8_t *params = (uint8_t *)malloc(params_size);
        params[0] = (DXL_LOBYTE(aAddress));
        params[1] = (DXL_HIBYTE(aAddress));
        params[2] = (DXL_LOBYTE(aSize));
        params[3] = (DXL_HIBYTE(aSize));
        
        uint8_t offset = 1 + aSize; // id + bytes
        for (size_t i = 0; i < nID; i++)
        {
            params[SYNC_WRITE_TX_PARAMS_LEN + i * offset] = aID[i];
            memcpy(&params[SYNC_WRITE_TX_PARAMS_LEN + i * offset + 1], &aTxBuf[i * aSize],  aSize);
        }
        
        mPacket_v2 = DynamixelPacket_v2(BROADCAST_ID, SYNC_WRITE_TX_PARAMS_LEN + nID * aSize, INST_SYNC_WRITE, params, params_size);

        transaction_v2(false);
        free(params);
        return mPacket_v2.mStatus;

    }

}

/**
 *  Fast Sync Read (0x8A)
 */
DynamixelStatus DynamixelInterface::fastSyncRead(
    uint8_t aVer, 
    uint8_t nID, 
    const uint8_t *aID, 
    uint16_t aAddress, 
    uint16_t aSize, 
    uint8_t *aRxBuf)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        return DYN_STATUS_INSTRUCTION_ERROR;
    }
    else
    {
        uint16_t params_size = FAST_SYNC_READ_TX_PARAMS_LEN + nID;
        uint8_t *params = (uint8_t *)malloc(params_size);

        params[0] = (DXL_LOBYTE(aAddress));
        params[1] = (DXL_HIBYTE(aAddress));
        params[2] = (DXL_LOBYTE(aSize));
        params[3] = (DXL_HIBYTE(aSize));

        memcpy(&params[FAST_SYNC_READ_TX_PARAMS_LEN], aID, nID);

        mPacket_v2 = DynamixelPacket_v2(0xFE, FAST_SYNC_READ_TX_LENGTH + nID, INST_FAST_SYNK_READ, params, params_size);

        prepareTransaction();
        sendPacket_v2(mPacket_v2);
        uint8_t temp_status = mPacket_v2.mStatus;

        for (size_t i = 0; i < nID; i++)
        {   
            mPacket_v2.mRxDataLength = aSize;
            mPacket_v2.mRxData = &aRxBuf[i * aSize];
            receivePacket_v2(mPacket_v2, 0, RECEIVE_FAST);
        }
        
        endTransaction();
        free(params);
        return temp_status;
    }
}

/**
 *  13. Bulk Read (0x92)
 */
DynamixelStatus DynamixelInterface::bulkRead(
    uint8_t aVer, 
    uint8_t nID, 
    const uint8_t *aTxBuf, 
    uint16_t aSize, 
    uint8_t *aRxBuf)
{
    if (aVer == DYN_PROTOCOL_V1)
    {
        return DYN_STATUS_INSTRUCTION_ERROR;
    }
    else
    {
        mPacket_v2 = DynamixelPacket_v2(BROADCAST_ID, BULK_READ_TX_LENGTH + aSize, INST_BULK_READ, aTxBuf, aSize);
        prepareTransaction();
        sendPacket_v2(mPacket_v2);
        uint8_t temp_status;

        uint16_t rx_offset = 0;
        for (size_t i = 0; i < nID; i++)
        {
            mPacket_v2.mID = aTxBuf[i * 5];
            mPacket_v2.mRxDataLength = aTxBuf[1 + 5 * i] | (aTxBuf[2 + 5 * i] << 8);
            mPacket_v2.mRxData = &aRxBuf[rx_offset];
            rx_offset = rx_offset + mPacket_v2.mRxDataLength;

            receivePacket_v2(mPacket_v2, BULK_READ_RX_LENGTH + mPacket_v2.mRxDataLength);
            temp_status = temp_status | mPacket_v2.mStatus;
        }
    
        endTransaction();

        return temp_status;

    }

}

/**
 *  Sync Write (0x93)
 */
DynamixelStatus DynamixelInterface::bulkWrite(
    uint8_t aVer, 
    uint8_t nID,
    uint16_t aTxSize,  
    const uint8_t *aTxBuf)
{
    if (aVer == DYN_PROTOCOL_V1)
    {   	
        return DYN_STATUS_INSTRUCTION_ERROR;
    }
    else
    {
        mPacket_v2 = DynamixelPacket_v2(BROADCAST_ID, BULK_WRITE_TX_LENGTH + aTxSize, INST_BULK_WRITE, aTxBuf, aTxSize);
        transaction_v2(false);
        return mPacket_v2.mStatus;
    }

}
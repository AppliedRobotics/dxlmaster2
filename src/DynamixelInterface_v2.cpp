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
    //	digitalWrite(23, LOW);
    endTransaction();
}


DynamixelStatus DynamixelInterface::read(uint8_t aID, uint8_t aAddress, uint8_t aSize, uint8_t *aPtr, uint8_t aStatusReturnLevel)
{
    mPacket = DynamixelPacket(aID, DYN_READ, 4, aPtr, aAddress, aSize);
    transaction(aStatusReturnLevel > 0 && aID != BROADCAST_ID, aSize);
    return mPacket.mStatus;
}

DynamixelStatus DynamixelInterface::write(uint8_t aID, uint8_t aAddress, uint8_t aSize, const uint8_t *aPtr, uint8_t aStatusReturnLevel)
{
    mPacket = DynamixelPacket(aID, DYN_WRITE, aSize + 3, aPtr, aAddress);
    transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
    return mPacket.mStatus;
}

DynamixelStatus DynamixelInterface::regWrite(uint8_t aID, uint8_t aAddress, uint8_t aSize, const uint8_t *aPtr, uint8_t aStatusReturnLevel)
{
    mPacket = DynamixelPacket(aID, DYN_REG_WRITE, aSize + 3, aPtr, aAddress);
    transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
    return mPacket.mStatus;
}

DynamixelStatus DynamixelInterface::syncWrite(uint8_t nID, const uint8_t *aID, uint8_t aAddress, uint8_t aSize, const uint8_t *aPtr, uint8_t aStatusReturnLevel)
{
    mPacket = DynamixelPacket(BROADCAST_ID, DYN_SYNC_WRITE, (aSize + 1) * nID + 4, aPtr, aAddress, aSize, nID, aID);
    transaction(false);
    return mPacket.mStatus;
}

DynamixelStatus DynamixelInterface::ping(uint8_t aID)
{
    mPacket = DynamixelPacket(aID, DYN_PING, 2, NULL);
    transaction(true);
    return mPacket.mStatus;
}

DynamixelStatus DynamixelInterface::action(uint8_t aID, uint8_t aStatusReturnLevel)
{
    mPacket = DynamixelPacket(aID, DYN_ACTION, 2, NULL);
    transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
    return mPacket.mStatus;
}

DynamixelStatus DynamixelInterface::reset(uint8_t aID, uint8_t aStatusReturnLevel)
{
    mPacket = DynamixelPacket(aID, DYN_RESET, 2, NULL);
    transaction(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
    return mPacket.mStatus;
}


void DynamixelInterface::transaction_v2(bool aExpectStatus, uint16_t answerSize)
{
    prepareTransaction();
    sendPacket_v2(mPacket_v2, answerSize);

    if (aExpectStatus)
        receivePacket_v2(mPacket_v2, answerSize);
    else
        mPacket_v2.mStatus = DYN2_STATUS_OK;

    endTransaction();
}

DynamixelStatus DynamixelInterface::read_v2(uint8_t aID, uint16_t aAddress, uint16_t aSize, uint8_t *aPtr, uint8_t aStatusReturnLevel)
{
    mPacket_v2 = DynamixelPacket_v2(aID, DYN_READ, INST_LENGTH + READ_LENGTH + CRC_LENGTH, aPtr, aAddress, READ_LENGTH);
    transaction_v2(aStatusReturnLevel > 0 && aID != BROADCAST_ID, aSize);
    return mPacket_v2.mStatus;
}

DynamixelStatus DynamixelInterface::write_v2(uint8_t aID, uint16_t aAddress, uint16_t aSize, const uint8_t *aPtr, uint8_t aStatusReturnLevel)
{
    mPacket_v2 = DynamixelPacket_v2(aID, DYN_WRITE, INST_LENGTH + WRITE_LENGTH + aSize + CRC_LENGTH, aPtr, aAddress, aSize);
    transaction_v2(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
    return mPacket_v2.mStatus;
} 

DynamixelStatus DynamixelInterface::ping_v2(uint8_t aID)
{
    mPacket_v2 = DynamixelPacket_v2(aID, DYN_PING, INST_LENGTH + PING_LENGTH + CRC_LENGTH, NULL);
    transaction_v2(true);
    return mPacket_v2.mStatus;
}

DynamixelStatus DynamixelInterface::action_v2(uint8_t aID, uint8_t aStatusReturnLevel)
{
    mPacket_v2 = DynamixelPacket_v2(aID, DYN_ACTION, 2, NULL);
    transaction_v2(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
    return mPacket_v2.mStatus;
}

DynamixelStatus DynamixelInterface::reset_v2(uint8_t aID, uint8_t aStatusReturnLevel)
{
    mPacket_v2 = DynamixelPacket_v2(aID, DYN_RESET, 2, NULL);
    transaction_v2(aStatusReturnLevel > 1 && aID != BROADCAST_ID);
    return mPacket_v2.mStatus;
}
/*
 * DynamixelDevice.h
 */

#ifndef DYNAMIXELDEVICE_H_
#define DYNAMIXELDEVICE_H_

#include "DynamixelInterface_v2.h"
#include <HardwareSerial.h>

extern HardwareDynamixelInterface DxlMaster;

class DynamixelDevice
{
public:

    DynamixelDevice(DynamixelID aId, uint8_t aVersion = DYN_PROTOCOL_V1);

    DynamixelStatus init(void);
    DynamixelStatus status() { return mStatus; }

    DynamixelID id() { return mID; }
    DynamixelStatus changeId(uint8_t id);

    void protocolVersion(uint8_t version) { mVer = version; };
    uint8_t protocolVersion(void) {	return mVer; }

    uint8_t statusReturnLevel();
    void statusReturnLevel(uint8_t aSRL);

    uint16_t model();
    uint8_t firmware();

    void communicationSpeed(uint32_t aSpeed);

    template <class T>
    inline DynamixelStatus read(uint16_t aAddress, T &aData)
    {
        return mStatus = DxlMaster.read<T>(mVer, mID, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus read(uint16_t aAddress, uint16_t size, uint8_t *ptr)
    {
        return mStatus = DxlMaster.read(mVer, mID, aAddress, size, ptr, mStatusReturnLevel);
    }

    template <class T>
    inline DynamixelStatus write(uint16_t aAddress, const T &aData)
    {
        return mStatus = DxlMaster.write<T>(mVer, mID, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus write(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.write(mVer, mID, aAddress, size, ptr, mStatusReturnLevel);
    }

    template <class T>
    inline DynamixelStatus regWrite(uint16_t aAddress, const T &aData)
    {
        return mStatus = DxlMaster.regWrite<T>(mVer, mID, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus regWrite(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.regWrite(mVer, mID, aAddress, size, ptr, mStatusReturnLevel);
    }
        
    inline DynamixelStatus syncRead(uint8_t nID, const uint8_t *aID, uint16_t aAddress, uint16_t aLen, uint8_t *rxPtr)
    {
        return mStatus = DxlMaster.syncRead(mVer, nID, aID, aAddress, aLen, rxPtr);
    }

    /**
     * \brief Instruction to control multiple devices simultaneously using one Instruction Packet
     * uint8_t IDs = 5 ;
     * uint8_t dataLen = 4;
     * uint8_t []
     * The function wait for the packet to be completly sent (using Stream.flush)
     */
    inline DynamixelStatus syncWrite(uint8_t nID, const uint8_t *aID, uint16_t aAddress, uint16_t aSize, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.syncWrite(mVer, nID, aID, aAddress, aSize, ptr);

    }
    

    DynamixelStatus ping(uint8_t *buf = NULL)
    {
        return mStatus = DxlMaster.ping(mVer, mID, buf);
    }

    DynamixelStatus action(void)
    {
        return mStatus = DxlMaster.action(mVer, BROADCAST_ID, mStatusReturnLevel);
    }

    DynamixelStatus reset(uint8_t alvl = 0xFF)
    {
        return mStatus = DxlMaster.reset(mVer, mID, alvl, mStatusReturnLevel);
    }

    DynamixelStatus reboot(void)
    {
        return mStatus = DxlMaster.reboot(mVer, mID, mStatusReturnLevel);
    }

    DynamixelStatus clear(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.clear(mVer, mID, size, ptr, mStatusReturnLevel);
    }

    DynamixelStatus backup(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.backup(mVer, mID, size, ptr, mStatusReturnLevel);
    }




private:
    DynamixelID mID;
    uint8_t mVer;
    uint8_t mStatusReturnLevel;
    DynamixelStatus mStatus;
};

#endif /* DYNAMIXELDEVICE_H_ */

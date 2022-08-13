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
        return mStatus = DxlMaster.read<T>(mID, mVer, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus read(uint16_t aAddress, uint16_t size, uint8_t *ptr)
    {
        return mStatus = DxlMaster.read(mID, mVer, aAddress, size, ptr, mStatusReturnLevel);
    }

    template <class T>
    inline DynamixelStatus write(uint16_t aAddress, const T &aData)
    {
        return mStatus = DxlMaster.write<T>(mID, mVer, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus write(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.write(mID, mVer, aAddress, size, ptr, mStatusReturnLevel);
    }

    template <class T>
    inline DynamixelStatus regWrite(uint16_t aAddress, const T &aData)
    {
        return mStatus = DxlMaster.regWrite<T>(mID, mVer, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus regWrite(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.regWrite(mID, mVer, aAddress, size, ptr, mStatusReturnLevel);
    }
        
    inline DynamixelStatus syncRead(uint16_t aAddress, uint16_t aLen, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.syncRead(BROADCAST_ID, mVer, aAddress, aLen, size, ptr);
    }
/*
    inline DynamixelStatus syncWrite(uint16_t aAddress, uint16_t aLen, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.syncWrite(mID, mVer, aAddress, aLen, size, ptr, mStatusReturnLevel);
    }
*/

    DynamixelStatus ping(uint8_t *buf = NULL)
    {
        return mStatus = DxlMaster.ping(mID, mVer, buf);
    }

    DynamixelStatus action(void)
    {
        return mStatus = DxlMaster.action(mID, mVer, mStatusReturnLevel);
    }

    DynamixelStatus reset(uint8_t alvl = 0xFF)
    {
        return mStatus = DxlMaster.reset(mID, mVer, alvl, mStatusReturnLevel);
    }

    DynamixelStatus reboot(void)
    {
        return mStatus = DxlMaster.reboot(mID, mVer, mStatusReturnLevel);
    }

    DynamixelStatus clear(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.clear(mID, mVer, size, ptr, mStatusReturnLevel);
    }

    DynamixelStatus backup(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.backup(mID, mVer, size, ptr, mStatusReturnLevel);
    }




private:
    DynamixelID mID;
    uint8_t mVer;
    uint8_t mStatusReturnLevel;
    DynamixelStatus mStatus;
};

#endif /* DYNAMIXELDEVICE_H_ */

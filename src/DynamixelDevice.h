/*
 * DynamixelDevice.h
 *
 * Created: 19.01.2019 17:51:17
 *  Author: potor
 */

#ifndef DYNAMIXELDEVICE_H_
#define DYNAMIXELDEVICE_H_

#include "DynamixelInterface_v2.h"
#include <HardwareSerial.h>

extern HardwareDynamixelInterface DxlMaster;

class DynamixelDevice
{
public:
    DynamixelDevice(DynamixelID aId);

    DynamixelStatus init();

    DynamixelStatus status()
    {
        return mStatus;
    }

    DynamixelID id()
    {
        return mID;
    }

    DynamixelStatus changeId(uint8_t id);

    uint8_t statusReturnLevel();
    void statusReturnLevel(uint8_t aSRL);
    
    uint16_t model();
    uint8_t firmware();

    void communicationSpeed(uint32_t aSpeed);

    template <class T>
    inline DynamixelStatus read(uint8_t aAddress, T &aData)
    {
        return mStatus = DxlMaster.read<T>(mID, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus read(uint8_t aAddress, uint8_t size, uint8_t *ptr)
    {
        return mStatus = DxlMaster.read(mID, aAddress, size, ptr, mStatusReturnLevel);
    }


    template <class T>
    inline DynamixelStatus write(uint8_t aAddress, const T &aData)
    {
        return mStatus = DxlMaster.write<T>(mID, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus write(uint8_t aAddress, uint8_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.write(mID, aAddress, size, ptr, mStatusReturnLevel);
    }


    template <class T>
    inline DynamixelStatus regWrite(uint8_t aAddress, const T &aData)
    {
        return mStatus = DxlMaster.regWrite<T>(mID, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus regWrite(uint8_t aAddress, uint8_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.regWrite(mID, aAddress, size, ptr, mStatusReturnLevel);
    }

    DynamixelStatus ping()
    {
        return mStatus = DxlMaster.ping(mID);
    }

    DynamixelStatus action()
    {
        return mStatus = DxlMaster.action(mID, mStatusReturnLevel);
    }

    DynamixelStatus reset()
    {
        return mStatus = DxlMaster.reset(mID, mStatusReturnLevel);
    }

    /* DYNAMIXEL V2 comp added: */

    template <class T>
    inline DynamixelStatus read_v2(uint16_t aAddress, T &aData)
    {
        return mStatus = DxlMaster.read_v2<T>(mID, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus read_v2(uint16_t aAddress, uint16_t size, uint8_t *ptr)
    {
        return mStatus = DxlMaster.read_v2(mID, aAddress, size, ptr, mStatusReturnLevel);
    }

    template <class T>
    inline DynamixelStatus write_v2(uint16_t aAddress, const T &aData)
    {
        return mStatus = DxlMaster.write_v2<T>(mID, aAddress, aData, mStatusReturnLevel);
    }

    inline DynamixelStatus write_v2(uint16_t aAddress, uint16_t size, const uint8_t *ptr)
    {
        return mStatus = DxlMaster.write_v2(mID, aAddress, size, ptr, mStatusReturnLevel);
    }

    DynamixelStatus ping_v2(void)
    {
        return mStatus = DxlMaster.ping_v2(mID);
    }

    DynamixelStatus action_v2(void)
    {
        return mStatus = DxlMaster.action_v2(mID, mStatusReturnLevel);
    }

    DynamixelStatus reset_v2(void)
    {
        return mStatus = DxlMaster.reset_v2(mID, mStatusReturnLevel);
    }



private:
    DynamixelID mID;
    uint8_t mStatusReturnLevel;
    DynamixelStatus mStatus;
};

#endif /* DYNAMIXELDEVICE_H_ */

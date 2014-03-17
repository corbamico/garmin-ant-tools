#include "garmin.h"
#include "antfs_host.hpp"

class CANTFSHost
{

private:
    ANTFSHost hostImp_;
public:
    BOOL Init()
    {
        BOOL bResult;
        ANTFS_RETURN eReturn;

        ANTFS_DEVICE_PARAMETERS stSearchMask;
        ANTFS_DEVICE_PARAMETERS stSearchParameters;

        //Get search device parameters
        ULONG ulDeviceID = 0;
        USHORT usManufacturerID = 0;
        USHORT usDeviceType = 1;

        //Search Mask
        stSearchMask.ulDeviceID = ulDeviceID ? 0xFFFFFFFF : 0;
        stSearchMask.usManufacturerID = usManufacturerID ? 0xFFFF : 0;
        stSearchMask.usDeviceType = usDeviceType ? 0xFFFF : 0;
        stSearchMask.ucAuthenticationType = 0;
        stSearchMask.ucStatusByte1 = 0;//ANTFS_STATUS1_DEFAULT_SEARCH_MASK;
        stSearchMask.ucStatusByte2 = 0;//ANTFS_STATUS2_DEFAULT_SEARCH_MASK;

        //Search Parameters
        stSearchParameters.ulDeviceID = ulDeviceID;
        stSearchParameters.usManufacturerID = usManufacturerID;
        stSearchParameters.usDeviceType = usDeviceType;
        stSearchParameters.ucAuthenticationType = 0;
        stSearchParameters.ucStatusByte1 = 0;
        stSearchParameters.ucStatusByte2 = 0;


        //Step 1: init
        if ((!hostImp_.Init(0,57600))
          ||(!WaitForAck(ANTFS_RESPONSE_OPEN_PASS)))
        {
            return FALSE;
        }

        //step 2: Search Device
        hostImp_.SetChannelID(FR_410_CHANNEL_DEVICE_TYPE,FR_410_CHANNEL_TRANS_TYPE);
        hostImp_.SetMessagePeriod(FR_410_MESG_PERIOD);
        hostImp_.SetProximitySearch(5);
        hostImp_.SetNetworkkey(aucNetworkkey);

        hostImp_.ClearSearchDeviceList();
        hostImp_.AddSearchDevice(&stSearchMask,&stSearchParameters);

        eReturn = hostImp_.SearchForDevice(FR_410_SEARCH_FREQ,FR_410_LINK_FREQ,0,TRUE);

        if ((!(ANTFS_RETURN_PASS==eReturn))
          ||(!WaitForAck(ANTFS_RESPONSE_CONNECT_PASS)))
        {
            return FALSE;
        }

        //step 3: Pairing



        //step 4: Pairing OK:
        if ((!(ANTFS_RETURN_PASS==eReturn))
          ||(!WaitForAck(ANTFS_RESPONSE_AUTHENTICATE_PASS)))
        {
            return FALSE;
        }
        return TRUE;

    }

    BOOL WaitForAck(ANTFS_RESPONSE expect, int timeout=999)
    {
        ANTFS_RESPONSE response;
        response = hostImp_.WaitForResponse(timeout);
        return (response == expect);
    }

    int garmin_ant_read ( garmin_unit * garmin, garmin_packet * p )
    {

    }
    int garmin_ant_write ( garmin_unit * garmin, garmin_packet * p )
    {
        int r=-1;
        ANTFS_RETURN eReturn;

        eReturn = hostImp_.ManualTransfer(0xffff,0,1,p->data);

        if((ANTFS_RETURN_PASS == hostImp_.ManualTransfer(0xffff,0,size_t,p->data))
        && WaitForAck(ANTFS_RESPONSE_MANUAL_TRANSFER_PASS))
        {
            r = size_t;
        }
        return r;
    }
};





/*
   Open the USB connection with the first Garmin device we find.  Eventually,
   I'd like to add the ability to select a particular device.  Returns 1 on
   success, 0 on failure.  Prints diagnostic information and errors to stdout.
*/
int
garmin_ant_open ( garmin_unit * garmin )
{
    BOOL bReturn;
    return bReturn;
}

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
        bResult = hostImp_.Init(0,57600);
        if(!bResult)
        {
            return bResult;
        }
    }

    BOOL WaitForAck(ANTFS_RESPONSE expect, int timeout=999)
    {
        ANTFS_RESPONSE response;
        response = hostImp_.WaitForResponse(timeout);
        return (response == expect);
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

#include <ctype.h>
#include <iomanip>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <string>


#include "cmd_def.h"
#include "openbci_gui_helpers.h"
#include "serialization.h"


namespace GanglionDetails
{
    extern int exit_code;
    extern std::list<GanglionDevice> devices;
}

void ble_evt_gap_scan_response (const struct ble_msg_gap_scan_response_evt_t *msg)
{
    char name[512];
    bool name_found_in_response = false;
    for (int i = 0; i < msg->data.len;)
    {
        int8 len = msg->data.data[i++];
        if (!len)
        {
            continue;
        }
        if (i + len > msg->data.len)
        {
            break; // not enough data
        }
        uint8 type = msg->data.data[i++];
        if (type == 0x09) // no idea what is 0x09
        {
            name_found_in_response = true;
            memcpy (name, msg->data.data + i, len - 1);
            name[len - 1] = '\0';
        }

        i += len - 1;
    }

    if (name_found_in_response)
    {
        // strcasestr is unavailable for windows
        if (strstr (name, "anglion") != NULL)
        {
            std::stringstream mac_addr;
            for (int i = 5; i > -1; i--)
            {
                mac_addr << std::setw (2) << std::setfill ('0') << std::hex
                         << (unsigned int)msg->sender.addr[i];
                if (i != 0)
                {
                    mac_addr << ":";
                }
            }

            uint8_t firmware = strstr (name, "anglion 1.3") == NULL ? 2 : 3;

            GanglionDevice device;
            device.identifier = name;
            device.mac_address = mac_addr.str ();
            device.firmware_version = firmware;

            GanglionDetails::devices.push_back (device);
            GanglionDetails::exit_code = (int)GanglionDetails::GanglionScanExitCodes::STATUS_OK;
        }
    }
}

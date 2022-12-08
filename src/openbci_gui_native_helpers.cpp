#include <chrono>
#include <ctype.h>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "SimpleBLE.h"
#include "openbci_gui_native_helpers.h"

#include "json.hpp"

using json = nlohmann::json;


int scan_for_ganglions (int timeout_sec, char *output_json, int *output_len)
{
    std::map<std::string, std::string> devices;
    auto adapter_list = SimpleBLE::Adapter::get_adapters ();
    if (adapter_list.empty ())
    {
        return (int)GanglionScanExitCodes::PORT_OPEN_ERROR;
    }

    adapter_list[0].set_callback_on_scan_found (
        [&devices] (SimpleBLE::Peripheral peripheral)
        {
            std::string identifier = peripheral.identifier ();
            std::string mac_address = peripheral.address ();
            if (strncmp (identifier.c_str (), "Ganglion", 8) == 0)
            {
                devices[identifier] = mac_address;
            }
            else if (strncmp (identifier.c_str (), "Simblee", 7) == 0)
            {
                devices[identifier] = mac_address;
            }
        });

    adapter_list[0].scan_for (timeout_sec * 1000);

    json result (devices);
    std::string s = result.dump ();
    strcpy (output_json, s.c_str ());
    *output_len = s.length ();

    return (int)GanglionScanExitCodes::STATUS_OK;
}

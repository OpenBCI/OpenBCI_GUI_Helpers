#include <ctype.h>
#include <list>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "SimpleBLE.h"
#include "openbci_gui_native_helpers.h"
#include "serialization.h"

using json = nlohmann::json;

#define SOFTWARE_REVISION_CHARACTERISTIC "00002a28-0000-1000-8000-00805f9b34fb"
#define DEVICE_INFORMATION_SERVICE "0000180a-0000-1000-8000-00805f9b34fb"

int scan_for_ganglions (int timeout_sec, char *output_json, int *output_len)
{
    std::list<SimpleBLE::Peripheral> peripherals;
    auto adapter_list = SimpleBLE::Adapter::get_adapters ();
    if (adapter_list.empty ())
    {
        return (int)GanglionScanExitCodes::PORT_OPEN_ERROR;
    }

    adapter_list[0].set_callback_on_scan_found (
        [&peripherals] (SimpleBLE::Peripheral peripheral)
        {
            std::string identifier = peripheral.identifier ();

            if (strncmp (identifier.c_str (), "Ganglion", 8) == 0 ||
                strncmp (identifier.c_str (), "Simblee", 7) == 0)
            {
                peripherals.push_back (peripheral);
            }
        });

    adapter_list[0].scan_for (timeout_sec * 1000);

    std::list<GanglionDevice> devices;
    for (auto peripheral : peripherals)
    {
        GanglionDevice device;
        device.identifier = peripheral.identifier ();
        device.mac_address = peripheral.address ();

        peripheral.connect ();

        // Read the software revision characteristic to get the firmware version
        SimpleBLE::ByteArray software_revision =
            peripheral.read (DEVICE_INFORMATION_SERVICE, SOFTWARE_REVISION_CHARACTERISTIC);

        peripheral.disconnect ();

        // Version should be in the form x.x.x stored as ASCII values in the data buffer
        device.firmware_version = (software_revision[0] == '3') ? 3 : 2;

        devices.push_back (device);
    }

    json result = devices;
    std::string s = result.dump ();
    strcpy (output_json, s.c_str ());
    *output_len = (int)s.length ();

    return (int)GanglionScanExitCodes::STATUS_OK;
}

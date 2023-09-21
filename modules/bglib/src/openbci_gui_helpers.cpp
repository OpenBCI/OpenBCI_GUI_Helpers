#include <chrono>
#include <ctype.h>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "cmd_def.h"
#include "openbci_gui_helpers.h"
#include "uart.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "json.hpp"

using json = nlohmann::json;

namespace GanglionDetails
{
    int exit_code = (int)GanglionScanExitCodes::STATUS_OK;
    std::map<std::string, std::string> devices;

    void output (uint8 len1, uint8 *data1, uint16 len2, uint8 *data2)
    {
        if (uart_tx (len1, data1) || uart_tx (len2, data2))
        {
            exit_code = (int)GanglionScanExitCodes::PORT_OPEN_ERROR;
        }
    }

    int read_message (int timeout_ms)
    {
        unsigned char *data = NULL;
        struct ble_header hdr;
        int r;

        r = uart_rx (sizeof (hdr), (unsigned char *)&hdr, timeout_ms);
        if (!r)
        {
            return -1; // timeout
        }
        else if (r < 0)
        {
            exit_code = (int)GanglionScanExitCodes::PORT_OPEN_ERROR;
            return 1; // fails to read
        }
        if (hdr.lolen)
        {
            data = new unsigned char[hdr.lolen];
            r = uart_rx (hdr.lolen, data, timeout_ms);
            if (r <= 0)
            {
                exit_code = (int)GanglionScanExitCodes::PORT_OPEN_ERROR;
                delete[] data;
                return 1; // fails to read
            }
        }

        const struct ble_msg *msg = ble_get_msg_hdr (hdr);

        if (!msg)
        {
            exit_code = (int)GanglionScanExitCodes::GENERAL_ERROR;
            delete[] data;
            return 1;
        }

        msg->handler (data);
        delete[] data;
        return 0;
    }

    int wait_for_timeout (int num_seconds)
    {
        auto start_time = std::chrono::high_resolution_clock::now ();
        int run_time = 0;
        while (run_time < num_seconds)
        {
            if (read_message (num_seconds * 1000) > 0)
            {
                break;
            }
            auto end_time = std::chrono::high_resolution_clock::now ();
            run_time =
                std::chrono::duration_cast<std::chrono::seconds> (end_time - start_time).count ();
        }
        return exit_code;
    }

    int reset_ble_dev (char *uart_port)
    {
        // Reset dongle to get it into known state
        ble_cmd_system_reset (0);
        uart_close ();
        int i;
        for (i = 0; i < 5; i++)
        {
#ifdef _WIN32
            Sleep (500);
#else
            usleep (500000);
#endif
            if (!uart_open (uart_port))
            {
                break;
            }
        }
        if (i == 5)
        {
            return (int)GanglionScanExitCodes::PORT_OPEN_ERROR;
        }
        return (int)GanglionScanExitCodes::STATUS_OK;
    }
} // namespace GanglionDetails

int scan_for_ganglions (char *serial_port, int timeout_sec, char *output_json, int *output_len)
{
    bglib_output = GanglionDetails::output;
    GanglionDetails::exit_code = (int)GanglionDetails::GanglionScanExitCodes::SYNC_ERROR;
    GanglionDetails::devices.clear ();
    if (uart_open (serial_port))
    {
        return (int)GanglionDetails::GanglionScanExitCodes::PORT_OPEN_ERROR;
    }
    int res = GanglionDetails::reset_ble_dev (serial_port);
    if (res == (int)GanglionDetails::GanglionScanExitCodes::STATUS_OK)
    {
        GanglionDetails::exit_code = (int)GanglionDetails::GanglionScanExitCodes::SYNC_ERROR;
        ble_cmd_gap_discover (gap_discover_observation);
        res = GanglionDetails::wait_for_timeout (timeout_sec);
    }
    if (res == (int)GanglionDetails::GanglionScanExitCodes::STATUS_OK)
    {
        json result (GanglionDetails::devices);
        std::string s = result.dump ();
        strcpy (output_json, s.c_str ());
        *output_len = s.length ();
    }
    ble_cmd_gap_end_procedure ();
    uart_close ();
    return res;
}

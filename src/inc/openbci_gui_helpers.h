#pragma once

#ifdef _WIN32
#define SHARED_EXPORT __declspec(dllexport)
#define CALLING_CONVENTION __cdecl
#else
#define SHARED_EXPORT
#define CALLING_CONVENTION
#endif

namespace GanglionDetails
{
    typedef enum
    {
        STATUS_OK = 0,
        PORT_OPEN_ERROR,
        GENERAL_ERROR,
        SYNC_ERROR,
        SEND_ERROR,
        RECV_ERROR
    } GanglionScanExitCodes;
}

#ifdef __cplusplus
extern "C"
{
#endif

    SHARED_EXPORT int CALLING_CONVENTION scan_for_ganglions (
        char *serial_port, int timeout_sec, char *output, int *output_len);
    SHARED_EXPORT int CALLING_CONVENTION scan_for_wifi (char *device_info, int *len);

#ifdef __cplusplus
}
#endif

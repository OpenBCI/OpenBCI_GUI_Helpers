#include "serialization.h"

void to_json (nlohmann::json &result, const GanglionDevice &device)
{
    result = nlohmann::json {{"identifier", device.identifier}, {"mac_address", device.mac_address},
        {"firmware_version", std::to_string (device.firmware_version)}};
}

void from_json (const nlohmann::json &string, GanglionDevice &device)
{
    string.at ("identifier").get_to (device.identifier);
    string.at ("mac_address").get_to (device.mac_address);
    string.at ("firmware_version").get_to (device.firmware_version);
}
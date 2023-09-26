#pragma once

#include "json.hpp"

#include <cstdint>
#include <string>

typedef struct GanglionDevice
{
    std::string identifier;
    std::string mac_address;
    uint8_t firmware_version;
} GanglionDevice;

void to_json (nlohmann::json &result, const GanglionDevice &device);
void from_json (const nlohmann::json &string, GanglionDevice &device);
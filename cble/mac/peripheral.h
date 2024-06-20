#pragma once

#include <vector>
#include <string>
#include <optional>
#include <ex/buffer.h>

class Peripheral {
public:
    Peripheral() : address("NULL"), connectable(false) {
    }
    std::string address;
    bool connectable;
    std::optional<std::string> name;
    std::optional<int> txPowerLevel;
    std::optional<ex::buffer> manufacturerData;
    std::optional<std::vector<std::pair<std::string, ex::buffer>>> serviceData;
    std::pair<std::vector<std::string>, bool> serviceUuids;
};

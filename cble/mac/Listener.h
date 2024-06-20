#pragma once

#include "ex/buffer.h"
#include "peripheral.h"

class Listener {
protected:
    virtual void onState(const std::string& status);
    virtual void onScan(const std::string& uuid, int rssi, const Peripheral& peripheral);
    void Connected(const std::string& uuid, const std::string& error = "");
    void Disconnected(const std::string& uuid);
    void RSSI(const std::string& uuid, int rssi);
    void ServicesDiscovered(const std::string& uuid, const std::vector<std::string>& serviceUuids);
    void IncludedServicesDiscovered(const std::string& uuid, const std::string& serviceUuid, const std::vector<std::string>& serviceUuids);
    void CharacteristicsDiscovered(const std::string& uuid, const std::string& serviceUuid, const std::vector<std::pair<std::string, std::vector<std::string>>>& characteristics);
    void Read(const std::string& uuid, const std::string& serviceUuid, const std::string& characteristicUuid, const ex::buffer& data, bool isNotification);
    void Write(const std::string& uuid, const std::string& serviceUuid, const std::string& characteristicUuid);
    void Notify(const std::string& uuid, const std::string& serviceUuid, const std::string& characteristicUuid, bool state);
    void DescriptorsDiscovered(const std::string& uuid, const std::string& serviceUuid, const std::string& characteristicUuid, const std::vector<std::string>& descriptorUuids);
    void ReadValue(const std::string& uuid, const std::string& serviceUuid, const std::string& characteristicUuid, const std::string& descriptorUuid, const ex::buffer& data);
    void WriteValue(const std::string& uuid, const std::string& serviceUuid, const std::string& characteristicUuid, const std::string& descriptorUuid);
    void ReadHandle(const std::string& uuid, int descriptorHandle, const std::vector<uint8_t>& data);
    void WriteHandle(const std::string& uuid, int descriptorHandle);
};

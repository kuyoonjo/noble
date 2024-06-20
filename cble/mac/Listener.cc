#include "Listener.h"
#include <iostream>

void Listener::onState(const std::string& state) {
    std::cout << "stateChange" << std::endl;
}

void Listener::onScan(const std::string& uuid, int rssi, const Peripheral& peripheral) {
    std::cout << uuid << " - " << peripheral.address << " - " << (peripheral.name.has_value() ? *peripheral.name : "NULL") << " - " << rssi << std::endl;
}

void Listener::Connected(const std::string& uuid, const std::string& error) {
    mCallback->call([uuid, error](Napi::Env env, std::vector<napi_value>& args) {
        // emit('connect', deviceUuid) error added here
        args = { _s("connect"), _u(uuid), error.empty() ? env.Null() : _s(error) };
    });
}

void Listener::Disconnected(const std::string& uuid) {
    mCallback->call([uuid](Napi::Env env, std::vector<napi_value>& args) {
        // emit('disconnect', deviceUuid);
        args = { _s("disconnect"), _u(uuid) };
    });
}

void Listener::RSSI(const std::string & uuid, int rssi) {
    mCallback->call([uuid, rssi](Napi::Env env, std::vector<napi_value>& args) {
        // emit('rssiUpdate', deviceUuid, rssi);
        args = { _s("rssiUpdate"), _u(uuid), _n(rssi) };
    });
}

void Listener::ServicesDiscovered(const std::string & uuid, const std::vector<std::string>& serviceUuids) {
    mCallback->call([uuid, serviceUuids](Napi::Env env, std::vector<napi_value>& args) {
        // emit('servicesDiscover', deviceUuid, serviceUuids)
        args = { _s("servicesDiscover"), _u(uuid), toUuidArray(env, serviceUuids) };
    });
}

void Listener::IncludedServicesDiscovered(const std::string & uuid, const std::string & serviceUuid, const std::vector<std::string>& serviceUuids) {
    mCallback->call([uuid, serviceUuid, serviceUuids](Napi::Env env, std::vector<napi_value>& args) {
        // emit('includedServicesDiscover', deviceUuid, serviceUuid, includedServiceUuids)
        args = { _s("includedServicesDiscover"), _u(uuid), _u(serviceUuid), toUuidArray(env, serviceUuids) };
    });
}

void Listener::CharacteristicsDiscovered(const std::string & uuid, const std::string & serviceUuid, const std::vector<std::pair<std::string, std::vector<std::string>>>& characteristics) {
    mCallback->call([uuid, serviceUuid, characteristics](Napi::Env env, std::vector<napi_value>& args) {
        auto arr = characteristics.empty() ? Napi::Array::New(env) : Napi::Array::New(env, characteristics.size());
        for (size_t i = 0; i < characteristics.size(); i++) {
            Napi::Object characteristic = Napi::Object::New(env);
            characteristic.Set(_s("uuid"), _u(characteristics[i].first));
            characteristic.Set(_s("properties"), toArray(env, characteristics[i].second));
            arr.Set(i, characteristic);
        }
        // emit('characteristicsDiscover', deviceUuid, serviceUuid, { uuid, properties: ['broadcast', 'read', ...]})
        args = { _s("characteristicsDiscover"), _u(uuid), _u(serviceUuid), arr };
    });
}

void Listener::Read(const std::string & uuid, const std::string & serviceUuid, const std::string & characteristicUuid, const Data& data, bool isNotification) {
    mCallback->call([uuid, serviceUuid, characteristicUuid, data, isNotification](Napi::Env env, std::vector<napi_value>& args) {
        // emit('read', deviceUuid, serviceUuid, characteristicsUuid, data, isNotification);
        args = { _s("read"), _u(uuid), _u(serviceUuid), _u(characteristicUuid), toBuffer(env, data), _b(isNotification) };
    });
}

void Listener::Write(const std::string & uuid, const std::string & serviceUuid, const std::string & characteristicUuid) {
    mCallback->call([uuid, serviceUuid, characteristicUuid](Napi::Env env, std::vector<napi_value>& args) {
        // emit('write', deviceUuid, servicesUuid, characteristicsUuid)
        args = { _s("write"), _u(uuid), _u(serviceUuid), _u(characteristicUuid) };
    });
}

void Listener::Notify(const std::string & uuid, const std::string & serviceUuid, const std::string & characteristicUuid, bool state) {
    mCallback->call([uuid, serviceUuid, characteristicUuid, state](Napi::Env env, std::vector<napi_value>& args) {
        // emit('notify', deviceUuid, servicesUuid, characteristicsUuid, state)
        args = { _s("notify"), _u(uuid), _u(serviceUuid), _u(characteristicUuid), _b(state) };
    });
}

void Listener::DescriptorsDiscovered(const std::string & uuid, const std::string & serviceUuid, const std::string & characteristicUuid, const std::vector<std::string>& descriptorUuids) {
    mCallback->call([uuid, serviceUuid, characteristicUuid, descriptorUuids](Napi::Env env, std::vector<napi_value>& args) {
        // emit('descriptorsDiscover', deviceUuid, servicesUuid, characteristicsUuid, descriptors: [uuids])
        args = { _s("descriptorsDiscover"), _u(uuid), _u(serviceUuid), _u(characteristicUuid), toUuidArray(env, descriptorUuids) };
    });
}

void Listener::ReadValue(const std::string & uuid, const std::string & serviceUuid, const std::string & characteristicUuid, const std::string& descriptorUuid, const Data& data) {
    mCallback->call([uuid, serviceUuid, characteristicUuid, descriptorUuid, data](Napi::Env env, std::vector<napi_value>& args) {
        // emit('valueRead', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid, data)
        args = { _s("valueRead"), _u(uuid), _u(serviceUuid), _u(characteristicUuid), _u(descriptorUuid), toBuffer(env, data) };
    });
}

void Listener::WriteValue(const std::string & uuid, const std::string & serviceUuid, const std::string & characteristicUuid, const std::string& descriptorUuid) {
    mCallback->call([uuid, serviceUuid, characteristicUuid, descriptorUuid](Napi::Env env, std::vector<napi_value>& args) {
        // emit('valueWrite', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid);
        args = { _s("valueWrite"), _u(uuid), _u(serviceUuid), _u(characteristicUuid), _u(descriptorUuid) };
    });
}

void Listener::ReadHandle(const std::string & uuid, int descriptorHandle, const Data& data) {
    mCallback->call([uuid, descriptorHandle, data](Napi::Env env, std::vector<napi_value>& args) {
        // emit('handleRead', deviceUuid, descriptorHandle, data);
        args = { _s("handleRead"), _u(uuid), _n(descriptorHandle), toBuffer(env, data) };
    });
}

void Listener::WriteHandle(const std::string & uuid, int descriptorHandle) {
    mCallback->call([uuid, descriptorHandle](Napi::Env env, std::vector<napi_value>& args) {
        // emit('handleWrite', deviceUuid, descriptorHandle);
        args = { _s("handleWrite"), _u(uuid), _n(descriptorHandle) };
    });
}

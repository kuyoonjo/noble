#pragma once

#include "Listener.h"
#include <string>

class Manager {
public:
void set_listener(Listener*);
void scan_start();
void scan_stop();
bool connect(const std::string& uuid);
bool disconnect(const std::string& uuid);
bool discoverServices
};

@interface BLEManager : NSObject <CBCentralManagerDelegate, CBPeripheralDelegate> {
    Listener* listener;
    bool pendingRead;
}
@property (strong) CBCentralManager *centralManager;
@property dispatch_queue_t dispatchQueue;
@property NSMutableDictionary *peripherals;

- (instancetype)init: (Listener*) listener;
- (void)scan: (NSArray<NSString*> *)serviceUUIDs allowDuplicates: (BOOL)allowDuplicates;
- (void)stopScan;
- (BOOL)connect:(NSString*) uuid;
- (BOOL)disconnect:(NSString*) uuid;
- (BOOL)updateRSSI:(NSString*) uuid;
- (BOOL)discoverServices:(NSString*) uuid serviceUuids:(NSArray<NSString*>*) services;
- (BOOL)discoverIncludedServices:(NSString*) uuid forService:(NSString*) serviceUuid services:(NSArray<NSString*>*) serviceUuids;
- (BOOL)discoverCharacteristics:(NSString*) nsAddress forService:(NSString*) service characteristics:(NSArray<NSString*>*) characteristics;
- (BOOL)read:(NSString*) uuid service:(NSString*) serviceUuid characteristic:(NSString*) characteristicUuid;
- (BOOL)write:(NSString*) uuid service:(NSString*) serviceUuid characteristic:(NSString*) characteristicUuid data:(NSData*) data withoutResponse:(BOOL)withoutResponse;
- (BOOL)notify:(NSString*) uuid service:(NSString*) serviceUuid characteristic:(NSString*) characteristicUuid on:(BOOL)on;
- (BOOL)discoverDescriptors:(NSString*) uuid service:(NSString*) serviceUuid characteristic:(NSString*) characteristicUuid;
- (BOOL)readValue:(NSString*) uuid service:(NSString*) serviceUuid characteristic:(NSString*) characteristicUuid descriptor:(NSString*) descriptorUuid;
- (BOOL)writeValue:(NSString*) uuid service:(NSString*) serviceUuid characteristic:(NSString*) characteristicUuid descriptor:(NSString*) descriptorUuid data:(NSData*) data;
- (BOOL)readHandle:(NSString*) uuid handle:(NSNumber*) handle;
- (BOOL)writeHandle:(NSString*) uuid handle:(NSNumber*) handle data:(NSData*) data;
@end

#pragma once

#include "peripheral.h"
#include "types.h"

typedef void *c_ble_manager_t;

typedef void (*c_ble_manager_on_state_handler)(const char *state);
typedef void (*c_ble_manager_on_scan_handler)(c_ble_peripheral_t peripheral);
typedef void (*c_ble_manager_on_rssi_handler)(c_ble_str_t peripheral_id,
                                              uint16_t rssi);

typedef void (*c_ble_manager_on_connect_handler)(c_ble_str_t peripheral_id);
typedef void (*c_ble_manager_on_connect_error_handler)(c_ble_str_t peripheral_id, c_ble_str_t error);
typedef void (*c_ble_manager_on_disconnect_handler)(c_ble_str_t peripheral_id);

struct c_ble_manufacturer_data_t {
  uint16_t size;
  uint8_t *buffer;
};

void c_ble_manager_init(void);
void c_ble_manager_debug_on(void);
void c_ble_manager_debug_off(void);

void c_ble_manager_scan_start(c_ble_bool_t allow_dup);
void c_ble_manager_scan_stop(void);

void c_ble_manager_discover_services(c_ble_str_t peripheral_id);
void c_ble_manager_discover_characteristics(c_ble_str_t peripheral_id, c_ble_str_t service_id);

// handlers
void c_ble_manager_set_on_state(c_ble_manager_on_state_handler);
void c_ble_manager_set_on_scan(c_ble_manager_on_scan_handler);
void c_ble_manager_set_on_rssi(c_ble_manager_on_rssi_handler);

void c_ble_manager_set_on_connect(c_ble_manager_on_connect_handler);
void c_ble_manager_set_on_connect_error(c_ble_manager_on_connect_error_handler);
void c_ble_manager_set_on_disconnect(c_ble_manager_on_disconnect_handler);
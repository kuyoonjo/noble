#pragma once

#include "types.h"
#include <stdint.h>

typedef struct {
  c_ble_str_t id;
  c_ble_str_t name;
  int rssi;
  int tx_power_level;
  c_ble_bool_t connectable;
  c_ble_buffer_t manufacturer_data;
} c_ble_peripheral_t;

void c_ble_peripheral_connect(c_ble_str_t peripheral_id);
void c_ble_peripheral_disconnect(c_ble_str_t peripheral_id);

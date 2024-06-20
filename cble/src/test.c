#include "peripheral.h"
#include "types.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <cble.h>
#include <sys/_types/_null.h>
#include <unistd.h>

uint8_t mac[] = {0x3c, 0xfa, 0xd3, 0xb1, 0x08, 0x2c};

void on_state_handler(const char *state) {
  printf("state: %s\n", state);
  c_ble_manager_scan_start(0);
}

void on_scan_handler(c_ble_peripheral_t p) {
  if (p.manufacturer_data.size &&
      !memcmp(mac, p.manufacturer_data.buffer + 2, 3)) {
    printf("found: %s %s %d %d %hhu\n", p.name, p.id, p.rssi, p.tx_power_level, p.connectable);
    c_ble_peripheral_connect(p.id);
  }
}

int main() {
  c_ble_manager_init();
  // c_ble_manager_debug_on();
  c_ble_manager_set_on_state(on_state_handler);
  c_ble_manager_set_on_scan(on_scan_handler);
  sleep(5);
  return 0;
}
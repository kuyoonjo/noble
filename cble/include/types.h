#pragma once

#include <stdint.h>

typedef char* c_ble_str_t;
typedef uint8_t c_ble_bool_t;

typedef void(*c_ble_void_handler)(void);
typedef void(*c_ble_bool_handler)(c_ble_bool_t v);

typedef struct {
    uint16_t size;
    uint8_t* buffer;
} c_ble_buffer_t;
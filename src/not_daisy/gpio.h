#pragma once

#include <cstdint>

typedef uint8_t dsy_gpio;
void dsy_gpio_write(const dsy_gpio* p, uint8_t state);
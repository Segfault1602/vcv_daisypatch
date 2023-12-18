#include "gpio.h"

void dsy_gpio_write(const dsy_gpio* p, uint8_t state)
{
    *const_cast<dsy_gpio*>(p) = state;
}
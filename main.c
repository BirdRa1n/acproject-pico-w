#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "lwip/init.h"
#include "lwip/netif.h"
#include "pico/binary_info.h"
#include "src/ssd1306/ssd1306_i2c.h"
#include "src/ssd1306/ssd1306.h"
#include "src/display/display.h"
#include "src/mqtt/mqtt.h"

int main()
{
    stdio_init_all();

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

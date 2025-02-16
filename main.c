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

// Configurações de Wi-Fi
#define WIFI_SSID ""
#define WIFI_PASS ""

// Pino do LED para indicar conexão
#define LED_PIN 12

// Configurações do i2c
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Função para piscar o LED
void piscar_led()
{
    gpio_put(LED_PIN, 1);
    sleep_ms(100);
    gpio_put(LED_PIN, 0);
    sleep_ms(100);
}

int main()
{
    stdio_init_all();

    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Configura o LED como saída
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

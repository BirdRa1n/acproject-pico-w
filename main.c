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

    display_show((char *[]){"Iniciando..."}, 1);

    // Inicializa o Wi-Fi
    if (cyw43_arch_init())
    {
        printf("Erro ao inicializar o Wi-Fi\n");

        // Exibe erro no display
        display_show((char *[]){"ACProject Pico W", "", "Erro ao inicializar"}, 3);
        return 1;
    }

    cyw43_arch_enable_sta_mode();
    printf("Conectando ao Wi-Fi...\n");
    piscar_led();

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10000))
    {
        printf("Falha ao conectar ao Wi-Fi\n");

        // Exibe erro no display
        display_show((char *[]){"WIFI", "", "FALHA AO CONECTAR"}, 3);
        return 1;
    }
    else
    {
        printf("Connected.\n");

        // Exibe mensagem de sucesso no display
        display_show((char *[]){"WIFI CONECTADO", "", WIFI_SSID}, 3);
    }

    printf("Wi-Fi conectado!\n");

    mqtt_init();

    while (true)
    {
        cyw43_arch_poll(); // Necessário para manter o Wi-Fi ativo
        sleep_ms(100);
    }

    return 0;
}

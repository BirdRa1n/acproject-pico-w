# Documentação do Projeto: ACProject Pico W

## Descrição do Projeto

O **ACProject Pico W** é um projeto desenvolvido para a plataforma Raspberry Pi Pico W, que integra funcionalidades de conectividade Wi-Fi e controle de dispositivos através de mensagens MQTT. O projeto utiliza um display OLED SSD1306 para exibir informações e status.

## Estrutura do Repositório

O repositório contém a seguinte estrutura de arquivos:

```
/CMakeLists.txt
/lwipopts.h
/main.c
/pico_sdk_import.cmake
/src
    /display
        display.c
        display.h
    /infrared
        infrared.c
        infrared.h
    /mqtt
        mqtt.c
        mqtt.h
    /ssd1306
        ssd1306.c
        ssd1306.h
        ssd1306_font.h
        ssd1306_i2c.c
        ssd1306_i2c.h
```

## Dependências

- **Raspberry Pi Pico SDK**: O projeto utiliza a SDK do Raspberry Pi Pico, que deve ser configurada corretamente.
- **LWIP**: A biblioteca LWIP é utilizada para a implementação da pilha de protocolos TCP/IP.
- **SSD1306**: Biblioteca para controle do display OLED.

## Configuração do Ambiente

1. **Instalação do SDK**: Certifique-se de que o SDK do Raspberry Pi Pico está instalado e configurado corretamente.
2. **Configuração do CMake**: O arquivo `CMakeLists.txt` é utilizado para configurar o projeto. Certifique-se de que as dependências estão corretamente referenciadas.
3. **Configuração do Wi-Fi**: No arquivo `main.c`, defina as credenciais da rede Wi-Fi:
   ```c
   #define WIFI_SSID "sua_rede_wifi"
   #define WIFI_PASS "sua_senha_wifi"
   ```

## Funcionalidades

- **Conexão Wi-Fi**: O projeto conecta-se a uma rede Wi-Fi utilizando as credenciais fornecidas.
- **MQTT**: Implementa um cliente MQTT que se inscreve em tópicos específicos e processa mensagens recebidas.
- **Display OLED**: Exibe informações sobre o status da conexão Wi-Fi e mensagens recebidas no display SSD1306.

## Estrutura do Código

### `main.c`

- Inicializa o sistema e configura o I2C para o display.
- Conecta-se à rede Wi-Fi e exibe o status no display.
- Inicializa o cliente MQTT e mantém a conexão ativa.

### `mqtt.c`

- Implementa as funções para gerenciar a conexão MQTT, incluindo a inscrição em tópicos e o tratamento de mensagens recebidas.

### `display.c`

- Contém funções para renderizar texto no display OLED.

### `infrared.c`

- Processa comandos recebidos em formato JSON e executa ações correspondentes, como ligar ou desligar um LED.

### `ssd1306.c`

- Implementa a comunicação com o display SSD1306 via I2C e funções para desenhar caracteres e strings.

## Licença

Este projeto está licenciado sob a **MIT License**. Consulte o arquivo `LICENSE` para mais detalhes.

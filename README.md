# 📌 Documentação do Projeto: ACProject Pico W

## 📖 Sobre o Projeto
O **ACProject Pico W** é um projeto desenvolvido para a plataforma **Raspberry Pi Pico W**, integrando funcionalidades de **conectividade Wi-Fi** e **controle de dispositivos via MQTT**. Além disso, o projeto utiliza um **display OLED SSD1306** para exibição de informações e status em tempo real.

---

## 📂 Estrutura do Repositório
A organização dos arquivos do projeto segue a seguinte estrutura:

```
CMakeLists.txt
lwipopts.h
main.c
pico_sdk_import.cmake
src
---- display
        display.c
        display.h
---- infrared
        infrared.c
        infrared.h
---- mqtt
        mqtt.c
        mqtt.h
---- ssd1306
        ssd1306.c
        ssd1306.h
        ssd1306_font.h
        ssd1306_i2c.c
        ssd1306_i2c.h
```

---

## 📦 Dependências
Para que o projeto funcione corretamente, as seguintes bibliotecas e SDKs devem estar configurados:

- **Raspberry Pi Pico SDK** → Framework de desenvolvimento para o Raspberry Pi Pico W.
- **LWIP** → Biblioteca para implementação da pilha de protocolos TCP/IP.
- **SSD1306** → Biblioteca para controle do display OLED SSD1306.

---

## ⚙️ Configuração do Ambiente

### 1️⃣ Instalação do SDK
Certifique-se de que o **SDK do Raspberry Pi Pico** está instalado e configurado corretamente.

### 2️⃣ Configuração do CMake
O arquivo `CMakeLists.txt` é responsável pela configuração do projeto. Verifique se todas as dependências estão corretamente referenciadas.

### 3️⃣ Configuração do Wi-Fi
No arquivo `main.c`, defina as credenciais da rede Wi-Fi:
```c
#define WIFI_SSID "sua_rede_wifi"
#define WIFI_PASS "sua_senha_wifi"
```

### 4️⃣ Definição do Cliente MQTT
No arquivo `mqtt.h`, configure as credenciais do cliente MQTT:
```c
// Configurações do Cliente MQTT
#define MQTT_CLIENT_ID "seu_id_cliente"
#define MQTT_USER "seu_usuario"
#define MQTT_PASS "sua_senha"
```

---

## 🚀 Funcionalidades
✅ **Conexão Wi-Fi** → Conecta-se a uma rede Wi-Fi automaticamente.

✅ **Cliente MQTT** → Inscreve-se em tópicos e processa mensagens recebidas.

✅ **Display OLED SSD1306** → Exibe status da conexão e mensagens recebidas.

✅ **Controle Infravermelho** → Processa comandos JSON e controla dispositivos via IR.

---

## 🛠️ Estrutura do Código

### 📌 `main.c`
🔹 Inicializa o sistema e configura o I2C para o display OLED.
🔹 Conecta-se à rede Wi-Fi e exibe o status no display.
🔹 Inicializa e mantém a conexão com o cliente MQTT.

### 📌 `mqtt.c`
🔹 Gerencia a conexão com o **broker MQTT**.
🔹 Inscreve-se em tópicos e processa mensagens.

### 📌 `display.c`
🔹 Renderiza textos no **display OLED SSD1306**.

### 📌 `infrared.c`
🔹 Processa comandos JSON recebidos e controla **dispositivos infravermelhos**.

### 📌 `ssd1306.c`
🔹 Implementa a comunicação via **I2C** com o display SSD1306.
🔹 Permite desenhar caracteres e strings na tela.

---

## 📜 Licença
Este projeto está licenciado sob a **MIT License**. Consulte o arquivo `LICENSE` para mais detalhes.

---

📌 **Mantenha-se atualizado!** Para futuras melhorias e atualizações, acompanhe este repositório. 🚀


#include "mqtt.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "lwip/init.h"
#include "lwip/netif.h"
#include "src/display/display.h"
#include "src/infrared/infrared.h"

// Definição da variável global mqtt_client
mqtt_client_t *mqtt_client;

// Buffer global para acumular dados recebidos
#define MAX_BUFFER_SIZE 8192 // Aumente o tamanho do buffer se necessário
static char received_buffer[MAX_BUFFER_SIZE];
static size_t received_buffer_len = 0;

// Função de callback para receber mensagens
void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    printf("Mensagem recebida no tópico: %s\n", topic);
}

// Função de callback para dados recebidos via MQTT
void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    // Verifica se os dados são válidos
    if (data == NULL || len == 0)
    {
        printf("Erro: Dados inválidos recebidos.\n");
        return;
    }

    // Verifica se os dados cabem no buffer
    if (received_buffer_len + len >= MAX_BUFFER_SIZE)
    {
        printf("Erro: Buffer cheio. Dados recebidos excedem o tamanho máximo.\n");
        received_buffer_len = 0; // Reseta o buffer para evitar estouro
        return;
    }

    // Copia os dados recebidos para o buffer global
    memcpy(received_buffer + received_buffer_len, data, len);
    received_buffer_len += len;

    // Adiciona um terminador nulo para tratar o buffer como string
    received_buffer[received_buffer_len] = '\0';

    // Verifica se o JSON está completo (procura por '}')
    const char *json_end = strchr(received_buffer, '}');
    if (json_end != NULL)
    {
        // Calcula o tamanho da mensagem completa
        size_t message_len = json_end - received_buffer + 1;

        // Verifica se a mensagem está completa (ou seja, se o '}' é o último caractere)
        if (message_len <= received_buffer_len)
        {
            // Processa o JSON completo
            printf("Dados recebidos (completo): %.*s\n", (int)message_len, received_buffer);
            filterCommands(received_buffer);

            // Remove a mensagem processada do buffer
            memmove(received_buffer, received_buffer + message_len, received_buffer_len - message_len);
            received_buffer_len -= message_len;
            received_buffer[received_buffer_len] = '\0'; // Adiciona o terminador nulo
        }
    }
    else
    {
        printf("Dados recebidos (parcial): %s\n", received_buffer);
    }
}

// Função de callback para confirmação de inscrição (opcional)
void mqtt_subscribe_cb(void *arg, err_t err)
{
    if (err == ERR_OK)
    {
        printf("Inscrição confirmada!\n");
    }
    else
    {
        printf("Erro na confirmação da inscrição: %d\n", err);
    }
}

// Função para se inscrever em um tópico
void subscribe_to_topic(mqtt_client_t *client, const char *topic, uint8_t qos)
{
    err_t err = mqtt_subscribe(client, topic, qos, mqtt_subscribe_cb, NULL);
    if (err != ERR_OK)
    {
        printf("Erro ao se inscrever no tópico %s: %d\n", topic, err);
    }
    else
    {
        printf("Inscrito no tópico %s com QoS %d\n", topic, qos);
    }
}

// Função para publicar uma mensagem
void publish_message(mqtt_client_t *client, const char *topic, const char *message, uint8_t qos, uint8_t retain)
{
    err_t err = mqtt_publish(client, topic, message, strlen(message), qos, retain, NULL, NULL);
    if (err != ERR_OK)
    {
        printf("Erro ao publicar mensagem no tópico %s: %d\n", topic, err);
    }
    else
    {
        printf("Mensagem publicada no tópico %s: %s\n", topic, message);
    }
}

// Função de callback para conexão MQTT
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    if (status == MQTT_CONNECT_ACCEPTED)
    {
        printf("Conectado ao broker MQTT!\n");

        // Inscreve-se em um tópico após a conexão
        subscribe_to_topic(client, "device/" MQTT_CLIENT_ID "/commands", 0);
        subscribe_to_topic(client, "device/" MQTT_CLIENT_ID "/logs", 1);
    }
    else
    {
        printf("Erro na conexao MQTT: %d\n", status);
    }
}

// Inicialização do MQTT
void mqtt_init()
{
    ip_addr_t broker_ip;
    if (!ipaddr_aton(MQTT_BROKER_IP, &broker_ip)) // Converte o endereço IP para o formato correto
    {
        printf("Erro ao converter o endereço IP do broker MQTT\n");
        return;
    }

    mqtt_client = mqtt_client_new();
    if (mqtt_client == NULL)
    {
        printf("Erro ao criar cliente MQTT\n");
        return;
    }

    // Configura os callbacks para receber mensagens
    mqtt_set_inpub_callback(mqtt_client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, NULL);

    // Estrutura de informações do cliente MQTT
    struct mqtt_connect_client_info_t client_info = {
        .client_id = MQTT_CLIENT_ID,
        .client_user = MQTT_CLIENT_ID, // Se precisar de autenticação, adicione usuário e senha
        .client_pass = MQTT_PASS,
        .keep_alive = 60,
        .will_topic = NULL,
        .will_msg = NULL,
        .will_qos = 0,
        .will_retain = 0};

    // Tenta conectar ao broker MQTT
    err_t err = mqtt_client_connect(mqtt_client, &broker_ip, MQTT_BROKER_PORT, mqtt_connection_cb, NULL, &client_info);
    if (err != ERR_OK)
    {
        printf("Erro ao tentar conectar ao broker MQTT: %d\n", err);
    }
}
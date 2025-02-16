#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

void filterCommands(const char *jsonString)
{
  if (jsonString == NULL)
  {
    printf("Erro: JSON string é nula.\n");
    return;
  }

  // Variáveis para armazenar os valores de "command" e "code"
  char command[100] = {0};
  char code[5000] = {0}; // Aumente o tamanho do buffer para 5000 caracteres
  // Ponteiros para encontrar as chaves e valores no JSON
  const char *commandKey = "\"command\":\"";
  const char *codeKey = "\"code\":\"";

  // Encontra a posição da chave "command"
  const char *commandStart = strstr(jsonString, commandKey);
  if (commandStart)
  {
    commandStart += strlen(commandKey);                 // Avança para o início do valor
    const char *commandEnd = strchr(commandStart, '"'); // Encontra o fim do valor
    if (commandEnd && (commandEnd - commandStart) < sizeof(command))
    {
      // Copia o valor de "command" para a variável
      strncpy(command, commandStart, commandEnd - commandStart);
      command[commandEnd - commandStart] = '\0'; // Adiciona o terminador nulo
    }
    else
    {
      printf("Erro: Comando inválido ou muito longo.\n");
    }
  }

  // Encontra a posição da chave "code"
  const char *codeStart = strstr(jsonString, codeKey);
  if (codeStart)
  {
    codeStart += strlen(codeKey);                 // Avança para o início do valor
    const char *codeEnd = strchr(codeStart, '"'); // Encontra o fim do valor
    if (codeEnd && (codeEnd - codeStart) < sizeof(code))
    {
      // Copia o valor de "code" para a variável
      strncpy(code, codeStart, codeEnd - codeStart);
      code[codeEnd - codeStart] = '\0'; // Adiciona o terminador nulo
    }
    else
    {
      printf("Erro: Código inválido ou muito longo.\n");
    }
  }

  // Verifica se os valores foram encontrados
  if (strlen(command) > 0 && strlen(code) > 0)
  {
    printf("Command: %s\n", command);

    // Verifica se o comando é "on" ou "off"
    if (strcmp(command, "turn_on") == 0)
    {
      printf("Ligar o LED.\n");
      gpio_put(12, 1);
      gpio_put(20, 1);
    }
    else if (strcmp(command, "turn_off") == 0)
    {
      printf("Desligar o LED.\n");
      gpio_put(12, 0);
      gpio_put(20, 0);
    }

    // uso do código (pendente)
  }
  else
  {
    printf("Formato JSON inválido ou valores faltando.\n");
  }
}
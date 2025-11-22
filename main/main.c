#include <stdio.h>
#include "freertos/FreeRTOS.h" // -> inclui o núcleo do FreeRTOS, que é o sistema operacional de tempo real do ESP32.
#include "freertos/task.h" // -> funções relacionadas a tarefas (threads) do FreeRTOS, como vTaskDelay.
#include "driver/gpio.h" // -> funções para controlar os pinos de entrada/saída digitais da ESP32.

#define LED_GPIO 2   // LED interno do ESP32
// LED_GPIO é um apelido para o número do pino onde o LED está conectado.
// Na minha esp32 devkit geralmente o pino do led esta no GPIO 2

//Nao altere o nome app_main (ESP32 exige que você use app_main() com FreeRTOS)
void app_main(void) {
    // gpio_set_direction -> define se o pino é entrada ou saída.
    // GPIO_MODE_OUTPUT -> você vai escrever valores HIGH/LOW nele (ligar ou desligar LED).
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED_GPIO, 1);  // acende
        vTaskDelay(15000 / portTICK_PERIOD_MS); 
        
//portTICK_PERIOD_MS -> converte milissegundos em ticks do FreeRTOS.
//O FreeRTOS trabalha em ticks, então precisamos dessa conversão.

        gpio_set_level(LED_GPIO, 0);  // apaga
        vTaskDelay(15000 / portTICK_PERIOD_MS);
        
    }
}

// comando para saber qual usb a esp esta -> ls /dev/tty*
// output - Varios ttys porem o com o nome `/dev/ttyACM0` e aonde a esp esta

/*
buildar -> idf.py build
flash -> idf.py -p /dev/ttyACM0 flash


monitor (terminal) -> idf.py -p /dev/ttyACM0 monitor
os tres comandos juntos -> idf.py -p /dev/ttyACM0 flash monitor
*/

//Meu idf.py estava falhando entao rodei `source ~/esp/esp-idf/export.sh` para poder rodar com idf.py

//Caso tiver problema com permissao de usb rode o comando `sudo usermod -a -G uucp $USER` e `sudo usermod -a -G tty $USER`



// OBS IMPORTANTE !!!
// Quando eu gravo um firmware na esp (ou seja faco um flash) eu nao preciso apagar ele pra economiza memoria
// quando vou fazer um novo projeto, pois se eu crio o projeto X e depois eu ir e criar o projeto Y e no Y fizer o flash
// o projeto Y vai sobrescrever o X assim nao sendo necessario remover o antigo projeto..

// Apagar memoria da esp -> idf.py -p /dev/ttyACM0 erase_flash
// Apagar e depois gravar denovo -> idf.py -p /dev/ttyACM0 erase_flash flash

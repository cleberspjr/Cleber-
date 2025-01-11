#include <stdio.h>
#include "pico/stdlib.h"

const uint led_anode = 11; // GPIO conectado ao ânodo (positivo) do LED
const uint led_cathode = 12; // GPIO conectado ao cátodo (negativo) do LED

#define DOT_DURATION 200        // Duração do ponto em milissegundos
#define DASH_DURATION 800       // Duração do traço em milissegundos
#define GAP_DURATION 125        // Intervalo entre pontos/traços
#define LETTER_GAP_DURATION 250 // Intervalo entre letras
#define CYCLE_DELAY 3000        // Intervalo entre ciclos SOS

// Função para enviar um ponto ou traço
void send_signal(uint led_anode, int duration) {
    gpio_put(led_anode, true);   // Liga o LED
    sleep_ms(duration);          // Mantém o LED aceso por 'duration'
    gpio_put(led_anode, false);  // Desliga o LED
    sleep_ms(GAP_DURATION);      // Intervalo entre sinais
}

// Função para enviar o padrão SOS
void send_sos(uint led_anode) {
    // Três pontos
    for (int i = 0; i < 3; i++) {
        send_signal(led_anode, DOT_DURATION);
    }
    sleep_ms(LETTER_GAP_DURATION); // Intervalo entre letras

    // Três traços
    for (int i = 0; i < 3; i++) {
        send_signal(led_anode, DASH_DURATION);
    }
    sleep_ms(LETTER_GAP_DURATION); // Intervalo entre letras

    // Três pontos
    for (int i = 0; i < 3; i++) {
        send_signal(led_anode, DOT_DURATION);
    }
}

int main() {
    // Inicializa os pinos do LED
    gpio_init(led_anode);
    gpio_set_dir(led_anode, GPIO_OUT);
    gpio_init(led_cathode);
    gpio_set_dir(led_cathode, GPIO_OUT);

    // Configura o cátodo como GND
    gpio_put(led_cathode, false);

    // Inicializa a comunicação padrão
    stdio_init_all();

    while (true) {
        send_sos(led_anode);      // Envia o padrão SOS
        sleep_ms(CYCLE_DELAY);   // Aguarda o intervalo entre ciclos
    }
}

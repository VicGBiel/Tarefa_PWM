#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // GPIO do servo
#define LED_RGB_PIN 12 // GPIO do LED RGB

const uint16_t WRAP_PERIOD = 12500; // Valor máximo do contador - WRAP
const float PWM_DIVISER = 200.0; // Divisor do clock para o PWM

void set_pwm_duty(uint gpio, float duty_us);
void pwm_setup();
void pwm_cycle(uint gpio);

int main() {
    stdio_init_all(); // Inicializa a entrada e saída padrão
    gpio_set_dir(LED_RGB_PIN, true); //Configura o led como saída
    pwm_setup();

    while (true) {
        pwm_cycle(SERVO_PIN);
    }
}

// Função para definir o duty cycle do PWM
void set_pwm_duty(uint gpio, float duty_us) {
    // Converte o valor em us do ciclo ativo para o valor adequado dentro da contagem do PWM
    uint level = (uint)((duty_us / 20000.0f) * WRAP_PERIOD); 
    pwm_set_gpio_level(gpio, level);            
}

// Função para configurar o PWM
void pwm_setup(){
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Configura o pino do servo como saída PWM
    gpio_set_function(LED_RGB_PIN, GPIO_FUNC_PWM); // Configura o pino do LED RGB como saída PWM  

    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o número do slice PWM para o pino do servo
    pwm_set_clkdiv(slice_num, PWM_DIVISER); // Define o divisor do clock para o PWM para o servo
    pwm_set_wrap(slice_num, WRAP_PERIOD);  // Define o valor de wrap do contador para o servo
    pwm_set_enabled(slice_num, true); // Habilita o PWM para o servo

    uint slice_num_led = pwm_gpio_to_slice_num(LED_RGB_PIN); // Obtém o número do slice PWM para o pino do LED
    pwm_set_clkdiv(slice_num_led, PWM_DIVISER); // Define o divisor do clock para o PWM para o LED
    pwm_set_wrap(slice_num_led, WRAP_PERIOD);  // Define o valor de wrap do contador para o LED
    pwm_set_enabled(slice_num_led, true); // Habilita o PWM para o LED
}

// Função que varia o PWM
void pwm_cycle(uint gpio){
    // Posição 180° (2.400µs)
    set_pwm_duty(gpio, 2400);
    sleep_ms(5000); // Pausa por 5 segundos
    
    // Posição 90° (1.470µs)
    set_pwm_duty(gpio, 1470);
    sleep_ms(5000);
    
    // Posição 0° (500µs)
    set_pwm_duty(gpio, 500);
    sleep_ms(5000);
            
    // Movimento suave entre 0° e 180°
    for (float duty = 500; duty <= 2400; duty += 5) {
        set_pwm_duty(gpio, duty);
        sleep_ms(10); // Pausa por 10ms para um movimento suave
    }
    for (float duty = 2400; duty >= 500; duty -= 5) {
        set_pwm_duty(gpio, duty);
        sleep_ms(10); // Pausa por 10ms para um movimento suave
    }
}

# Controle de Servo Motor com PWM no Raspberry Pi Pico

## Descrição
Este projeto utiliza um **Raspberry Pi Pico** para controlar um **servo motor** através de **PWM (Modulação por Largura de Pulso)**. O código ajusta o ângulo do servo com base no ciclo de trabalho do PWM e implementa uma movimentação suave entre as posições mínimas e máximas.


## Configuração do PWM
- **Frequência:** 50Hz (período de 20ms)
- **Ciclo de Trabalho para controle do Servo:**
  - 2400µs → **180°**
  - 1470µs → **90°**
  - 500µs → **0°**
- **Resolução do PWM:** `WRAP_PERIOD = 12500`
- **Divisor do clock do PWM:** `PWM_DIVISER = 200.0`

## Funcionalidade do Código
1. Configura o **PWM na GPIO 22** (conectada ao servo).
2. Ajusta o servo para **180°, 90° e 0°**, aguardando **5 segundos** em cada posição.
3. Implementa uma **movimentação suave** entre **0° e 180°** com pequenos incrementos no duty cycle para transições mais naturais.
4. O LED RGB na **GPIO 12** pode ser usado para observar variações na iluminação conforme o PWM muda.

## Como Usar
1. Compile o código.
2. Com a ferramenta Wokwi integrada ao VS Code, execute o programa.
3. Caso deseje observar o funcionamento via LED:
    3.1. Troque o argumento da função pwm_cycle dentro do loop infinito para: **LED_RGB_PIN**;
    3.2. Compile e passe o arquivo .uf2 para a BitDogLab.

## Estrutura do Código
```c
void set_pwm_duty(uint gpio, float duty_us, uint slice_num) {
    uint level = (uint)((duty_us / 20000.0f) * WRAP_PERIOD);
    pwm_set_gpio_level(gpio, level);
}
```
- Converte o tempo de ativação `duty_us` para um **valor proporcional dentro do contador PWM**.
- O `level` define **quantos ciclos** o PWM ficará **ALTO** dentro de **20ms**.

## Observações
- O **incremento de 5µs** na movimentação suave evita oscilações bruscas do servo.
- Quando adicionado LED_RGB_PIN no agurmento da função pwm_cycle, ao invés de SERVO_MOTOR, podemos observar uma
variação na luminosidade do LED. 

## Vídeo Demonstrativo
*https://youtu.be/57BzqcyS-80*


---
**Assinatura:** Victor Gabriel Guimarães Lopes


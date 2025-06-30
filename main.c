/**
 * @file main.c
 * @brief Aplicação de teste para o driver do sensor BMP280.
 *
 * Este programa inicializa o sensor, lê continuamente os dados de pressão
 * e temperatura, e os exibe no monitor serial.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "bmp280.h"

// --- Configuração da Porta I2C da BitDogLab ---
// Alterne os comentários para escolher a porta desejada para o teste.

// Configuração para I2C 1 (Esquerda) - Padrão
#define I2C_PORT i2c1
const uint I2C_SDA_PIN = 2;
const uint I2C_SCL_PIN = 3;

// Configuração para I2C 0 (Direita) - Comentado
// #define I2C_PORT i2c0
// const uint I2C_SDA_PIN = 0;
// const uint I2C_SCL_PIN = 1;


int main() {
    stdio_init_all();
    
    // Espera ativa pela conexão do monitor serial.
    while(!stdio_usb_connected()) {
        sleep_ms(100);
    }

    printf("--- Iniciando Sensor de Pressao e Temperatura BMP280 ---\n");
    printf("Usando a porta I2C com SDA no pino %d e SCL no pino %d\n", I2C_SDA_PIN, I2C_SCL_PIN);

    // Inicializa o barramento I2C com velocidade de 400kHz.
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    
    // Inicializa o sensor e lê os parâmetros de calibração uma vez.
    bmp280_init(I2C_PORT);
    bmp280_calib_params_t params;
    bmp280_get_calib_params(I2C_PORT, &params);

    printf("Sensor inicializado. Coletando dados...\n");

    while (1) {
        int32_t raw_pressure, raw_temp;
        
        // 1. Lê os valores brutos do ADC do sensor.
        bmp280_read_raw(I2C_PORT, &raw_temp, &raw_pressure);
        
        // 2. Aplica as fórmulas de compensação para obter os valores reais.
        // A conversão de temperatura deve vir primeiro.
        int32_t temp_celsius = bmp280_convert_temp(raw_temp, &params);
        int32_t pressure_pa_fixed = bmp280_convert_pressure(raw_pressure, &params);

        // 3. Imprime os dados formatados, convertendo para float.
        printf("Pressao: %.2f hPa  |  ", pressure_pa_fixed / 25600.0f);
        printf("Temperatura: %.2f C\n", temp_celsius / 100.0f);
        
        sleep_ms(1000); // Pausa de 1 segundo entre as leituras.
    }
    return 0;
}
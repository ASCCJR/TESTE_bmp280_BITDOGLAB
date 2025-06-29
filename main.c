#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "bmp280.h"

// Pinos do conector I2C 1 da BitDogLab
#define I2C_PORT i2c1
const uint I2C_SDA_PIN = 2;
const uint I2C_SCL_PIN = 3;

int main() {
    stdio_init_all();
    sleep_ms(4000);

    printf("--- Iniciando Sensor de Pressao e Temperatura BMP280 ---\n");

    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    
    bmp280_init();
    bmp280_calib_params_t params;
    bmp280_get_calib_params(&params);

    printf("Sensor inicializado. Coletando dados...\n");

    while (1) {
        int32_t raw_pressure, raw_temp;
        bmp280_read_raw(&raw_temp, &raw_pressure);
        
        int32_t temp_celsius = bmp280_convert_temp(raw_temp, &params);
        int32_t pressure_pa_fixed = bmp280_convert_pressure(raw_pressure, &params);

        // >>>>> LINHA CORRIGIDA ABAIXO <<<<<
        // 1. Dividimos por 256.0f para converter do formato de ponto fixo para Pascals.
        // 2. Dividimos por 100.0f para converter de Pascals para hectoPascais (hPa).
        printf("Pressao: %.2f hPa  |  ", pressure_pa_fixed / 25600.0f);
        printf("Temperatura: %.2f C\n", temp_celsius / 100.0f);
        
        sleep_ms(1000);
    }
    return 0;
}
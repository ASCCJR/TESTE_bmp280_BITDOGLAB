# 🌡️ Teste Modular do Sensor de Pressão e Temperatura BMP280

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Plataforma](https://img.shields.io/badge/Plataforma-Raspberry%20Pi%20Pico-purple.svg)
![Sensor](https://img.shields.io/badge/Sensor-BMP280-blueviolet.svg)

Este repositório contém um código teste para o sensor de pressão atmosférica e temperatura BMP280, da Bosch. O código foi desenvolvido em C para o Raspberry Pi Pico (BITDOGLAB).

O projeto demonstra a implementação de um driver de sensor complexo, que lida com a leitura de dados de calibração de fábrica e a aplicação de fórmulas de compensação para garantir medições precisas. A arquitetura modular separa claramente o driver do sensor da aplicação principal, facilitando sua reutilização em outros projetos.

## ✨ Funcionalidades

* **Leitura de Dados Duplos:** Coleta dados de Temperatura (em Graus Celsius) e Pressão Atmosférica (em HectoPascais, hPa).
* **Driver Modular (`bmp280.c`, `bmp280.h`):** Toda a lógica de comunicação e cálculo do sensor é encapsulada, fornecendo uma API limpa para a aplicação principal.
* **Alta Precisão:** O driver lê os parâmetros de calibração únicos de cada sensor e utiliza as fórmulas de compensação de 32 e 64 bits (conforme o datasheet da Bosch) para garantir a máxima precisão e evitar overflow nos cálculos.
* **Configuração Flexível de Porta:** Permite alternar facilmente o uso entre os barramentos I2C 0 e I2C 1 através de uma simples alteração no `main.c`.
* **Saída Serial Clara:** Exibe os dados formatados e legíveis no monitor serial a cada segundo.

## 🛠️ Hardware e Software Necessários

### Hardware
* Placa com Raspberry Pi Pico (neste projeto, foi usada a **BitDogLab**)
* Sensor de Pressão e Temperatura I2C **BMP280**

### Software
* [Raspberry Pi Pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk)
* Ambiente de compilação C/C++ (GCC para ARM, CMake)
* Um programa para monitor serial (ex: o integrado no VS Code, PuTTY, etc.)

## Configurar a Porta I2C
* Por padrão, o projeto está configurado para usar o conector I2C 1 (Esquerda) da BitDogLab.
* Para trocar para o conector I2C 0 (Direita), edite o arquivo main.c
* Comente o bloco de configuração do I2C 1.
* Descomente o bloco de configuração do I2C 0.

## Exemplo para usar a porta I2C 0:

```bash
// --- Configuração da Porta I2C 1 da BitDogLab (Comentado) ---
// #define I2C_PORT i2c1
// const uint I2C_SDA_PIN = 2;
// const uint I2C_SCL_PIN = 3;

// --- Configuração da Porta I2C 0 da BitDogLab (Ativo) ---
#define I2C_PORT i2c0
const uint I2C_SDA_PIN = 0;
const uint I2C_SCL_PIN = 1;
```
## Visualizar a Saída
* Conecte o sensor BMP280 na porta I2C configurada no Passo 2.
* Abra um monitor serial conectado à porta COM do seu Pico.
* Você verá a seguinte saída, atualizada a cada segundo:
```bash
--- Iniciando Sensor de Pressao e Temperatura BMP280 ---
Usando a porta I2C com SDA no pino 2 e SCL no pino 3
Sensor inicializado. Coletando dados...
Pressao: 1012.63 hPa  |  Temperatura: 30.16 C
Pressao: 1012.63 hPa  |  Temperatura: 30.27 C
```
## 📂 Estrutura dos Arquivos
* main.c: A aplicação principal. Orquestra a inicialização e o loop de leitura, chamando as funções do driver.
* bmp280.c: A implementação do driver do sensor, contendo a lógica de comunicação I2C e as complexas fórmulas de compensação.
* bmp280.h: O arquivo de cabeçalho (a interface ou API) para o driver do BMP280.
* CMakeLists.txt: O arquivo de build do projeto.

✍️ Autor

  ASCCJR

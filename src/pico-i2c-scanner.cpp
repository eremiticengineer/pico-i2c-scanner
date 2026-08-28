#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define SDA_PIN  8
#define SCL_PIN  9

int main() {
    stdio_init_all();

    // Give USB serial a moment to come up
    sleep_ms(2000);

    i2c_init(I2C_PORT, 100 * 1000);

    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    // Only needed if you don't already have external pull-ups
    gpio_pull_up(SCL_PIN);

    printf("I2C scanner\n");
    printf("SDA = GP%d, SCL = GP%d\n\n", SDA_PIN, SCL_PIN);

    while (true) {
        printf("Scanning...\n");

        int found = 0;

        for (uint8_t address = 0x08; address <= 0x77; ++address) {
            uint8_t dummy;

            int result = i2c_read_timeout_us(
                I2C_PORT,
                address,
                &dummy,
                1,
                false,
                2000
            );

            if (result >= 0) {
                printf("Found device at 0x%02X\n", address);
                ++found;
            }
        }

        printf("Scan complete: %d device(s) found\n\n", found);

        sleep_ms(5000);
    }
}
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

bool* inttobin_4b(int itgr) {
	static bool bin[4];
	for (int i = 3; i >= 0; --i) {
		int pot = pow(2, i);
		if (itgr < pot) {
			bin[3 - i] = false;
		} else {
			bin[3 - i] = true;
			itgr -= pot;
		}
	}
	return bin;
}

bool* inttobin_6b(int itgr) {
	static bool bin[6];
	for (int i = 5; i >= 0; --i) {
		int pot = pow(2, i);
		if (itgr < pot) {
			bin[5 - i] = false;
		} else {
			bin[5 - i] = true;
			itgr -= pot;
		}
	}
	return bin;
}

int precomma(float flo) {
	int pre = flo;
	return pre;
}

int postcomma(float flo) {
	int pre = precomma(flo);
	int post = (flo - pre) * 10;
	return post;
}

int main() {

	// set GPIOs to use
	const uint LED_PINS[] = {0, 1, 2, 5, 6, 7, 10, 13, 14, 15};

	// initialize stdio
    stdio_init_all();

	// initialize ADC
    adc_init();

	// initialize GPIOs
	for (int i = 0; i < 10; ++i) {
		uint LED_PIN = LED_PINS[i];
		gpio_init(LED_PIN);
		gpio_set_dir(LED_PIN, GPIO_OUT);
	}

	// power on the temperature sensor
	adc_set_temp_sensor_enabled(true);

    // select ADC input 4 (temperature sensor)
    adc_select_input(4);

    while (1) {

		// declare and initialize variables
		const float conversion_factor = 3.3f / (1 << 12);
		uint16_t result = adc_read();
		float temp = 27 - (((result * conversion_factor) - 0.706)/0.001721);
		int pre = precomma(temp);
		int post = postcomma(temp);
		bool* pre_bin = inttobin_6b(pre);
		bool* post_bin = inttobin_4b(post);

		// print terminal output
		printf("Raw value: 0x%03x, temperature: %f or %d.%d\n", result, temp, pre, post);

		// blink LEDs for precomma number
		for (int i = 0; i < 6; ++i) {
			if (pre_bin[i] == true) {
				printf("1");
				gpio_put(LED_PINS[i], 1);
			} else {
				printf("0");
				gpio_put(LED_PINS[i], 0);
			}
		}
		printf("\n");

		// blink LEDs for postcomma number
		for (int i = 0; i < 4; ++i) {
			if (post_bin[i]) {
				printf("1");
				gpio_put(LED_PINS[6 + i], 1);
			} else {
				printf("0");
				gpio_put(LED_PINS[6 + i], 0);
			}
		}
		printf("\n");

		// sleep
		sleep_ms(3000);

		// clear LEDs for next round
		for (int i = 0; i < 10; ++i) {
			gpio_put(LED_PINS[i], 0);
		}
    }
}

#include <stdint.h>
#include "animations.h"

void advance_mode_0(uint8_t restart, uint8_t brightness, uint8_t frames[][4]) {
	copy_init(brightness, mode_0_init, frames);
}
	
void advance_mode_1(uint8_t restart, uint8_t brightness, uint8_t frames[][4]);
	
void advance_mode_2(uint8_t restart, uint8_t brightness, uint8_t frames[][4]);
	
void advance_mode_3(uint8_t restart, uint8_t brightness, uint8_t frames[][4]);
	
void advance_mode_4(uint8_t restart, uint8_t brightness, uint8_t frames[][4]);
	
void advance_mode_5(uint8_t restart, uint8_t brightness, uint8_t frames[][4]);

void copy_init(uint8_t brightness, uint8_t mode_init[][4], uint8_t frames[][4]) {
	for (int i = 0; i < NUMBER_LEDS; i++) {
		for (int j = 0; j < 4; j++) {
			if (j == 0)
				frames[i][j] = ((brightness - mode_init[i][j]) & 0x1F) | 0xE0;
			else	
				frames[i][j] = mode_init[i][j];
		}
	}
}

void breathe_step(uint8_t brightness, uint8_t frames[][4], uint8_t direction[]) {
	for (int i = 0; i < NUMBER_LEDS; i++) {
		if ((frames[i][0] & 0x1F) == BREATHE_MAX) {
			frames[i][0]--;
			direction[i] = 0;
		}
		else if ((frames[i][0] & 0x1F) == BREATHE_MIN) {
			frames[i][0]++;
			direction[i] = 1;
		}
		else if (direction[i] != 0) {
			frames[i][0]++;
		}
		else {
			frames[i][0]--;
		}
	}
}

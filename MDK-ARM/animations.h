#include <stdint.h>

#ifndef ANIMATIONS
	#define ANIMATIONS

	#define NUMBER_LEDS 10
	#define MAX_global_brightness 31
	#define MIN_global_brightness 10
	#define BREATHE_MIN 15
	#define BREATHE_MAX 31
	
	uint8_t mode_0_init[NUMBER_LEDS][4] = {
		{0xA, 0x0, 0x0, 0xFF},
		{0xA, 0x0, 0xFF, 0xFF},
		{0xA, 0x0, 0x0, 0xFF}, 
		{0xA, 0x0, 0xFF, 0xFF},
		{0xA, 0x0, 0x0, 0xFF},
		{0xA, 0x0, 0xFF, 0xFF},
		{0xA, 0x0, 0x0, 0xFF}, 
		{0xA, 0x0, 0xFF, 0xFF},
		{0xA, 0x0, 0x0, 0xFF}, 
		{0xA, 0x0, 0xFF, 0xFF}
	};
	
	uint8_t mode_1_init[NUMBER_LEDS][4] = {
		{BREATHE_MIN, 0x0, 0x0, 0xFF},
		{BREATHE_MIN, 0x0, 0x0, 0xFF},
		{BREATHE_MIN, 0x0, 0x0, 0xFF}, 
		{BREATHE_MIN, 0x0, 0x0, 0xFF},
		{BREATHE_MIN, 0x0, 0x0, 0xFF},
		{BREATHE_MIN, 0x0, 0x0, 0xFF},
		{BREATHE_MIN, 0x0, 0x0, 0xFF}, 
		{BREATHE_MIN, 0x0, 0x0, 0xFF},
		{BREATHE_MIN, 0x0, 0x0, 0xFF}, 
		{BREATHE_MIN, 0x0, 0x0, 0xFF}
	};
	
	uint8_t mode_1_dir[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
		
	

	void advance_mode_0(uint8_t restart, uint8_t brightness, uint8_t frames[][4]); // static red and gold
	void advance_mode_1(uint8_t restart, uint8_t brightness, uint8_t frames[][4]); // red breathing
	void advance_mode_2(uint8_t restart, uint8_t brightness, uint8_t frames[][4]); // gold breathing
	void advance_mode_3(uint8_t restart, uint8_t brightness, uint8_t frames[][4]); // red and gold breathing
	void advance_mode_4(uint8_t restart, uint8_t brightness, uint8_t frames[][4]); // red and gold alternating
	void advance_mode_5(uint8_t restart, uint8_t brightness, uint8_t frames[][4]); // HSV traversal
	void copy_init(uint8_t brightness, uint8_t mode_init[][4], uint8_t frames[][4]);
	void breathe_step(uint8_t brightness, uint8_t frames[][4], uint8_t direction[]);

#endif

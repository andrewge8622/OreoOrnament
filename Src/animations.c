#include <stdint.h>
#include "animations.h"

uint8_t mode_0_init[NUMBER_LEDS][4] = {
		{BREATHE_MIN, 0x0, 0x0, 0x6F},
		{BREATHE_MIN, 0x0, 0x6F, 0x6F},
		{BREATHE_MIN, 0x0, 0x0, 0x6F}, 
		{BREATHE_MIN, 0x0, 0x6F, 0x6F},
		{BREATHE_MIN, 0x0, 0x0, 0x6F},
		{BREATHE_MIN, 0x0, 0x6F, 0x6F},
		{BREATHE_MIN, 0x0, 0x0, 0x6F}, 
		{BREATHE_MIN, 0x0, 0x6F, 0x6F},
		{BREATHE_MIN, 0x0, 0x0, 0x6F}, 
		{BREATHE_MIN, 0x0, 0x6F, 0x6F}
};
uint8_t mode_1_init[NUMBER_LEDS][4] = {
	{BREATHE_MIN, 0x0, 0x0, 0x3F},
	{BREATHE_MIN, 0x0, 0x0, 0x3F},
	{BREATHE_MIN, 0x0, 0x0, 0x3F}, 
	{BREATHE_MIN, 0x0, 0x0, 0x3F},
	{BREATHE_MIN, 0x0, 0x0, 0x3F},
	{BREATHE_MIN, 0x0, 0x0, 0x3F},
	{BREATHE_MIN, 0x0, 0x0, 0x3F}, 
	{BREATHE_MIN, 0x0, 0x0, 0x3F},
	{BREATHE_MIN, 0x0, 0x0, 0x3F}, 
	{BREATHE_MIN, 0x0, 0x0, 0x3F}
};

uint8_t mode_2_init[NUMBER_LEDS][4] = {
	{BREATHE_MIN, 0x0, 0x3F, 0x3F},
	{BREATHE_MIN, 0x0, 0x3F, 0x3F},
	{BREATHE_MIN, 0x0, 0x3F, 0x3F}, 
	{BREATHE_MIN, 0x0, 0x3F, 0x3F},
	{BREATHE_MIN, 0x0, 0x3F, 0x3F},
	{BREATHE_MIN, 0x0, 0x3F, 0x3F},
	{BREATHE_MIN, 0x0, 0x3F, 0x3F}, 
	{BREATHE_MIN, 0x0, 0x3F, 0x3F},
	{BREATHE_MIN, 0x0, 0x3F, 0x3F}, 
	{BREATHE_MIN, 0x0, 0x3F, 0x3F}
};

uint8_t mode_3_init[NUMBER_LEDS][4] = {
		{BREATHE_MIN, 0x0, 0x0, 0x3F},
		{BREATHE_MIN, 0x0, 0x3F, 0x3F},
		{BREATHE_MIN, 0x0, 0x0, 0x3F}, 
		{BREATHE_MIN, 0x0, 0x3F, 0x3F},
		{BREATHE_MIN, 0x0, 0x0, 0x3F},
		{BREATHE_MIN, 0x0, 0x3F, 0x3F},
		{BREATHE_MIN, 0x0, 0x0, 0x3F}, 
		{BREATHE_MIN, 0x0, 0x3F, 0x3F},
		{BREATHE_MIN, 0x0, 0x0, 0x3F}, 
		{BREATHE_MIN, 0x0, 0x3F, 0x3F}
	};
	
uint8_t mode_1_dir[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
uint8_t mode_2_dir[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
uint8_t mode_3_dir[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
uint8_t mode_4_dir[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
uint8_t mode_4_counter = 1;
uint8_t mode_4_rgb_index = 0;
uint8_t mode_5_init[NUMBER_LEDS][4] = {
	{BREATHE_MIN, 0x0, 0x0, 0x0},
	{BREATHE_MIN, 0x0, 0x0, 0x0},
	{BREATHE_MIN, 0x0, 0x0, 0x0}, 
	{BREATHE_MIN, 0x0, 0x0, 0x0},
	{BREATHE_MIN, 0x0, 0x0, 0x0},
	{BREATHE_MIN, 0x0, 0x0, 0x0},
	{BREATHE_MIN, 0x0, 0x0, 0x0}, 
	{BREATHE_MIN, 0x0, 0x0, 0x0},
	{BREATHE_MIN, 0x0, 0x0, 0x0}, 
	{BREATHE_MIN, 0x0, 0x0, 0x0}
};

struct color_ColorHSV color_frames[10]; 
struct color_ColorRGB temp_frame;

void advance_mode_0(uint8_t restart, uint8_t brightness, uint8_t frames[][4]) {
	copy_init(brightness, mode_0_init, frames);
}
	
void advance_mode_1(uint8_t restart, uint8_t brightness, uint8_t frames[][4]){
	if (restart) {
		copy_init(brightness, mode_1_init, frames);
	}
	else {
		breathe_step(brightness, frames, mode_1_dir);
	}
};
	
void advance_mode_2(uint8_t restart, uint8_t brightness, uint8_t frames[][4]){
	if (restart) {
		copy_init(brightness, mode_2_init, frames);
	}
	else {
		breathe_step(brightness, frames, mode_2_dir);
	}
};
	
void advance_mode_3(uint8_t restart, uint8_t brightness, uint8_t frames[][4]){
	if (restart) {
		copy_init(brightness, mode_3_init, frames);
	}
	else {
		breathe_step(brightness, frames, mode_3_dir);
	}
};
	
void advance_mode_4(uint8_t restart, uint8_t brightness, uint8_t frames[][4]){
	if (restart) {
		copy_init(brightness, mode_0_init, frames); // initialize to all red
		mode_4_counter = 0;
	}
	else {
		if (mode_4_counter > 120)
			mode_4_counter = 0;
		else if (mode_4_counter > 80)
			mode_4_rgb_index = 3;
		else if (mode_4_counter > 40)
			mode_4_rgb_index = 2;
		else
			mode_4_rgb_index = 1;
		
		for (int i = 0; i < NUMBER_LEDS; i++) {
			for (int j = 0; j < 4; j++) {
				if (j == 0)
					frames[i][j] = ((brightness + mode_1_init[i][j]) & 0x1F) | 0xE0; // borrowing from all red init
				else if (j == mode_4_rgb_index)
					frames[i][j] = 0x6F;
				else
					frames[i][j] = 0x0;
			}
		}
		mode_4_counter++;
	}
};
	
void advance_mode_5(uint8_t restart, uint8_t brightness, uint8_t frames[][4]){
	if (restart) {
		for (int i = 0; i < NUMBER_LEDS; i++) {
			color_frames[i].h = i*25;
			color_frames[i].s = 127;
			color_frames[i].v = 255;
		}
		HSV_step(brightness, frames, color_frames);
	}
	else {
		HSV_step(brightness, frames, color_frames);
	}
};

void copy_init(uint8_t brightness, uint8_t mode_init[][4], uint8_t frames[][4]) {
	for (int i = 0; i < NUMBER_LEDS; i++) {
		for (int j = 0; j < 4; j++) {
			if (j == 0)
				frames[i][j] = ((brightness + mode_init[i][j]) & 0x1F) | 0xE0;
			else	
				frames[i][j] = mode_init[i][j];
		}
	}
}

void breathe_step(uint8_t brightness, uint8_t frames[][4], uint8_t direction[]) {
	for (int i = 0; i < NUMBER_LEDS; i++) {
		if ((frames[i][0] & 0x1F) >= (BREATHE_MAX + brightness)) {
			frames[i][0]--;
			direction[i] = 0;
		}
		else if ((frames[i][0] & 0x1F) <= (BREATHE_MIN + brightness)) {
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
void HSV_step(uint8_t brightness, uint8_t frames[][4], struct color_ColorHSV color_frames[]) {
	for (int i = 0; i < NUMBER_LEDS; i++) {
		color_frames[i].h++;
		color_HSV2RGB(color_frames+i, &temp_frame);
		frames[i][0] = ((brightness / 3) + 1) | 0xE0;
		frames[i][1] = temp_frame.b/2;
		frames[i][2] = temp_frame.g/2;
		frames[i][3] = temp_frame.r/2;
	}
};

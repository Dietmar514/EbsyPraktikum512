#include <stdint.h>
#include <LPC177x_8x.h>
#include "delay.h"


//	LPC_GPIO0->SET = 0xAA00;




static uint32_t led1_value = 0x100;
static uint32_t led2_value = 0x1000;
static uint32_t led1_trigger = 0;
static uint32_t led2_trigger = 0;
static uint32_t led1_freq = 1;
static uint32_t led2_freq = 6;
static uint32_t tickcounter = 0;
static uint32_t delay = 300;

void init(void) 
{
	LPC_GPIO0->DIR = 0xFFFFFFFF;
	LPC_GPIO0->CLR = 0xFFFFFFFF;
}

void led1(void) 
{
	LPC_GPIO0->CLR = led1_value;
	if (led1_trigger == 0) 
	{
		led1_value = led1_value << 1;
		if (led1_value == 0x800) 
		{
			led1_trigger = 1;
		}
	}
	else if (led1_trigger == 1) 
	{
		led1_value = led1_value >> 1;
		if (led1_value == 0x100) 
		{
			led1_trigger = 0;
		}
	}
	LPC_GPIO0->SET = led1_value;
}



void led2(void) 
{
	LPC_GPIO0->CLR = led2_value;
	if (led2_trigger == 0)
	{
		led2_value = led2_value << 1;
		if (led2_value == 0x8000)
		{
			led2_trigger = 1;
		}
	}
	else if (led2_trigger == 1) 
	{
		led2_value = led2_value >> 1;
		if (led2_value == 0x1000) 
		{
			led2_trigger = 0;
		}
	}
	LPC_GPIO0->SET = led2_value;
}

int main(void)
{
	init();
	while (1)
	{
		if(tickcounter % led1_freq == 0)
		{
			led1();
		}
		if(tickcounter % led2_freq == 0)
		{
			led2();
		}
		tickcounter++;
		delayms(delay);
	}
}



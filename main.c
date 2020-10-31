#include <stdint.h>
#include <LPC177x_8x.h>
#include "delay.h"


uint32_t tickcounter = 0;

#define led1_freq 1;
#define led2_freq 6;
#define delay 300;	//delay in ms

void init(void) 
{
	LPC_GPIO0->DIR = 0xFFFFFFFF;
	LPC_GPIO0->CLR = 0xFFFFFFFF;
}

void led1(void) 
{
	static uint32_t led_value;
	static uint32_t led_trigger;	//toggles led direction
	if(tickcounter == 0)			//Initialize values
	{
		led_value = 0x100;
		led_trigger = 0;
	}

	LPC_GPIO0->CLR = led_value;
	if (led_trigger == 0) 
	{
		led_value = led_value << 1;
		if (led_value == 0x800) 
		{
			led_trigger = 1;
		}
	}
	else if (led_trigger == 1) 
	{
		led_value = led_value >> 1;
		if (led_value == 0x100) 
		{
			led_trigger = 0;
		}
	}
	LPC_GPIO0->SET = led_value;
}



void led2(void) 
{
	static uint32_t led_value;
	static uint32_t led_trigger;	//toggles led direction
	if (tickcounter == 0) 			//Initialize values
	{
		led_value = 0x1000;
		led_trigger = 0;
	}

	LPC_GPIO0->CLR = led_value;
	if (led_trigger == 0)
	{
		led_value = led_value << 1;
		if (led_value == 0x8000)
		{
			led_trigger = 1;
		}
	}
	else if (led_trigger == 1) 
	{
		led_value = led_value >> 1;
		if (led_value == 0x1000) 
		{
			led_trigger = 0;
		}
	}
	LPC_GPIO0->SET = led_value;
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



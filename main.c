#include <stdint.h>
#include <LPC177x_8x.h>
#include "delay.h"

#define processCount 8;
#define delay 300;	//delay in ms
#define freq 5;

#define led1_value 0x0100;
#define led2_value 0x0200;
#define led3_value 0x0400;
#define led4_value 0x0800;
#define led5_value 0x1000;
#define led6_value 0x2000;
#define led7_value 0x4000;
#define led8_value 0x8000;

uint32_t tickcounter = 0;

void (*processes[processCount])(int) = { controllLed1, controllLed2, controllLed3, controllLed4, controllLed5, controllLed6, controllLed7, controllLed8 };


void init(void) 
{
	LPC_GPIO0->DIR = 0xFFFFFFFF;
	LPC_GPIO0->CLR = 0xFFFFFFFF;
}



void controllLed1(int led_freq)			//duty-cycle = timeActive/cycleLength
{		
	if (tickcounter < led_freq == 0)
	{
		LPC_GPIO0->SET = led1_value;
	}
	else
	{
		LPC_GPIO0->CLR = led1_value;
	}

}

void controllLed2(int led_freq)
{
	if (tickcounter < led_freq == 0)
	{
		LPC_GPIO0->SET = led2_value;
	}
	else
	{
		LPC_GPIO0->CLR = led2_value;
	}
}

void controllLed3(int led_freq)
{
	if (tickcounter < led_freq == 0)
	{
		LPC_GPIO0->SET = led3_value;
	}
	else
	{
		LPC_GPIO0->CLR = led3_value;
	}
}

void controllLed4(int led_freq)
{
	if (tickcounter < led_freq == 0)
	{
		LPC_GPIO0->SET = led4_value;
	}
	else
	{
		LPC_GPIO0->CLR = led4_value;
	}
}

void controllLed5(int led_freq)
{
	if (tickcounter < led_freq == 0)
	{
		LPC_GPIO0->SET = led5_value;
	}
	else
	{
		LPC_GPIO0->CLR = led5_value;
	}
}

void controllLed6(int led_freq)
{
	if (tickcounter < led_freq == 0)
	{
		LPC_GPIO0->SET = led6_value;
	}
	else
	{
		LPC_GPIO0->CLR = led6_value;
	}
}

void controllLed7(int led_freq)
{
	if (tickcounter < led_freq == 0)
	{
		LPC_GPIO0->SET = led7_value;
	}
	else
	{
		LPC_GPIO0->CLR = led7_value;
	}
}

void controllLed8(int led_freq)
{
	if (tickcounter < led_freq == 0)
	{
		LPC_GPIO0->SET = led8_value;
	}
	else
	{
		LPC_GPIO0->CLR = led8_value;
	}
}


int main(void)
{
	init();
	while (1)
	{
		for (size_t i = 0; i < length; i++)
		{
			for (int currTask = 0; currTask < processCount; currTask++)
			{ 
				(*tasklist[currTask])(freq);
			}
		}
		tickcounter++;
		tickcount %= 100;
	}
}



#include <stdint.h>
#include <LPC177x_8x.h>
#include "delay.h"


#define delay 300	//delay in ms
#define processCount 9
#define freq 5

#define led1_value 0x0100
#define led2_value 0x0200
#define led3_value 0x0400
#define led4_value 0x0800
#define led5_value 0x1000
#define led6_value 0x2000
#define led7_value 0x4000
#define led8_value 0x8000

uint32_t tickcounter = 0;
uint32_t LEDfrequency[] = {0, 0, 0, 0, 0, 0, 0, 0};
uint32_t ledCounter = 0;


void init(void) 
{
	LPC_GPIO0->DIR = 0xFFFFFFFF;
	LPC_GPIO0->CLR = 0xFFFFFFFF;
}



void controllLed1(int led_freq)			//duty-cycle = timeActive/cycleLength
{		
	if (tickcounter < led_freq)
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
	if (tickcounter < led_freq)
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
	if (tickcounter < led_freq)
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
	if (tickcounter < led_freq)
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
	if (tickcounter < led_freq)
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
	if (tickcounter < led_freq)
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
	if (tickcounter < led_freq)
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
	if (tickcounter < led_freq)
	{
		LPC_GPIO0->SET = led8_value;
	}
	else
	{
		LPC_GPIO0->CLR = led8_value;
	}
}

void verschmiertesLauflicht(){
	
	static uint32_t currentLED;
	
	if(ledCounter == 0){
		currentLED = 0;
	}
	
	if(ledCounter % 500 == 0 && tickcounter == 0){
		LEDfrequency[currentLED] = 0;
		currentLED++;
		currentLED %= 8;
		
		if(currentLED == 0){
			LEDfrequency[currentLED] = 20;
		}
		else if(currentLED == 1){
			LEDfrequency[currentLED] = 32;
		}
		else if(currentLED == 2){
			LEDfrequency[currentLED] = 32;
		}
		else if(currentLED == 3){
			LEDfrequency[currentLED] = 32;
		}
		else if(currentLED == 4){
			LEDfrequency[currentLED] = 60;
		}
		else if(currentLED == 5){
			LEDfrequency[currentLED] = 80;
		}
		else if(currentLED == 6){
			LEDfrequency[currentLED] = 90;
		}
		else if(currentLED == 6){
			LEDfrequency[currentLED] = 100;
		}
		else if(currentLED == 7){
			LEDfrequency[currentLED] = 100;
		}
		else{
			//do nothing, should never happen
		}
	}
}




void (*tasklist[processCount])(int) = { controllLed1, controllLed2, controllLed3, controllLed4, controllLed5, controllLed6, controllLed7, controllLed8,  verschmiertesLauflicht};


int main(void)
{

	init();
	while (1)
	{
			
			for (int currTask = 0; currTask < processCount; currTask++)
			{ 
				(*tasklist[currTask])(LEDfrequency[currTask]);
			}
			


		
		tickcounter++;
		tickcounter %= 100;
		if(tickcounter == 0){
			ledCounter++;
		}
}
}

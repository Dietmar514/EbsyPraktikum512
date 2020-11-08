#include <stdint.h>
#include <LPC177x_8x.h>
#include "led.h"
#include "global.h"

uint32_t led_light_frequencies[AVAILABLE_LEDS] = {0};

void controll_led0(){	
	if (tick_counter < led_light_frequencies[0]){
		LPC_GPIO0->SET = ADDRESS_LED_0;
	}
	else{
		LPC_GPIO0->CLR = ADDRESS_LED_0;
	}

}

void controll_led1(){
	if (tick_counter < led_light_frequencies[1]){
		LPC_GPIO0->SET = ADDRESS_LED_1;
	}
	else{
		LPC_GPIO0->CLR = ADDRESS_LED_1;
	}
}

void controll_led2(){
	if (tick_counter < led_light_frequencies[2]){
		LPC_GPIO0->SET = ADDRESS_LED_2;
	}
	else{
		LPC_GPIO0->CLR = ADDRESS_LED_2;
	}
}

void controll_led3(){
	if (tick_counter < led_light_frequencies[3]){
		LPC_GPIO0->SET = ADDRESS_LED_3;
	}
	else{
		LPC_GPIO0->CLR = ADDRESS_LED_3;
	}
}

void controll_led4(){
	if (tick_counter < led_light_frequencies[4]){
		LPC_GPIO0->SET = ADDRESS_LED_4;
	}
	else{
		LPC_GPIO0->CLR = ADDRESS_LED_4;
	}
}

void controll_led5(){
	if (tick_counter < led_light_frequencies[5]){
		LPC_GPIO0->SET = ADDRESS_LED_5;
	}
	else{
		LPC_GPIO0->CLR = ADDRESS_LED_5;
	}
}

void controll_led6(){
	if (tick_counter < led_light_frequencies[6]){
		LPC_GPIO0->SET = ADDRESS_LED_6;
	}
	else{
		LPC_GPIO0->CLR = ADDRESS_LED_6;
	}
}

void controll_led7(){
	if (tick_counter < led_light_frequencies[7]){
		LPC_GPIO0->SET = ADDRESS_LED_7;
	}
	else{
		LPC_GPIO0->CLR = ADDRESS_LED_7;
	}
}

/**
 * @brief Startet ein verschmiertes Lauflicht. Auf dem led board leuchtet, je nach gesetzter Geschwindigkeit, immer eine LED mit 100 % Staerke. 
 * Nach jedem Schritt leuchtet die vorherige LED mit 30 % weniger Staerke. Die prozentuale Staerke wird durch die Häufigkeit der on/off-Zyklen bestimmt.
 */

void smeared_running_light(){


	static uint32_t led_counter;
	static uint32_t current_led;
	static uint32_t b_is_initialized;
	uint32_t b_init = 0;

	//start with LED 0	
	if(!b_init){																														
		led_counter = 0;
		b_is_initialized = 0;
	}

	if(b_init){
		
		//trigger of led_counter to enable the next LED of the running light
		if(tick_counter == 0){													
			led_counter++;
			}
	}

	b_init = 1;
	
	if(led_counter == 0){													
		current_led = 0;
	}
	
	//if counter for switching the leds and the counter for switching the power of the leds
	if(led_counter % MAX_TICKS == 0 && tick_counter == 0){

		//this if is to catch this first two unique steps
		if(b_is_initialized && current_led < 2){
			current_led = 2;
		}		
		
		switch(current_led){
			//case 0 will only be once
			case 0:{		
				led_light_frequencies[0] = 100;
				break;
			}
			//case 1 will only be once
			case 1:{
				led_light_frequencies[0] = 70;
				led_light_frequencies[1] = 100;
				led_light_frequencies[2] = 0;
				led_light_frequencies[3] = 0;
				led_light_frequencies[4] = 0;
				led_light_frequencies[5] = 0;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				break;
			}
			case 2:{
				led_light_frequencies[0] = 40;
				led_light_frequencies[1] = 70;
				led_light_frequencies[2] = 100;
				led_light_frequencies[3] = 0;
				led_light_frequencies[4] = 0;
				led_light_frequencies[5] = 0;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				b_is_initialized = 1;
				break;
			}
			case 3:{
				led_light_frequencies[0] = 10;
				led_light_frequencies[1] = 40;
				led_light_frequencies[2] = 70;
				led_light_frequencies[3] = 100;
				led_light_frequencies[4] = 0;
				led_light_frequencies[5] = 0;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				//10, 40, 70, 100, 0, 0, 0, 0
				break;
			}
			case 4:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 10;
				led_light_frequencies[2] = 40;
				led_light_frequencies[3] = 70;
				led_light_frequencies[4] = 100;
				led_light_frequencies[5] = 0;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				//0, 10, 40, 70, 100, 0, 0, 0
				break;
			}
			case 5:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 0;
				led_light_frequencies[2] = 10;
				led_light_frequencies[3] = 40;
				led_light_frequencies[4] = 700;
				led_light_frequencies[5] = 100;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				//0, 0, 10, 40, 70, 100, 0, 0
				break;
			}
			case 6:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 0;
				led_light_frequencies[2] = 0;
				led_light_frequencies[3] = 10;
				led_light_frequencies[4] = 40;
				led_light_frequencies[5] = 70;
				led_light_frequencies[6] = 100;
				led_light_frequencies[7] = 0;
				//0, 0, 0, 10, 40, 70, 100, 0
				break;
			}
			case 7:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 0;
				led_light_frequencies[2] = 0;
				led_light_frequencies[3] = 0;
				led_light_frequencies[4] = 10;
				led_light_frequencies[5] = 40;
				led_light_frequencies[6] = 70;
				led_light_frequencies[7] = 100;
				//0, 0, 0, 0, 10, 40, 70, 100
				break;
			}case 8:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 0;
				led_light_frequencies[2] = 0;
				led_light_frequencies[3] = 0;
				led_light_frequencies[4] = 0;
				led_light_frequencies[5] = 10;
				led_light_frequencies[6] = 100;
				led_light_frequencies[7] = 70;
				//0, 0, 0, 0, 0, 10, 100, 70
				break;
			}
			case 9:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 0;
				led_light_frequencies[2] = 0;
				led_light_frequencies[3] = 0;
				led_light_frequencies[4] = 0;
				led_light_frequencies[5] = 100;
				led_light_frequencies[6] = 70;
				led_light_frequencies[7] = 40;
				//0, 0, 0, 0, 0, 100, 70, 40
				break;
			}
			case 10:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 0;
				led_light_frequencies[2] = 0;
				led_light_frequencies[3] = 0;
				led_light_frequencies[4] = 100;
				led_light_frequencies[5] = 70;
				led_light_frequencies[6] = 40;
				led_light_frequencies[7] = 10;
				//0, 0, 0, 0, 100, 70, 40, 10
				break;
			}
			case 11:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 0;
				led_light_frequencies[2] = 0;
				led_light_frequencies[3] = 100;
				led_light_frequencies[4] = 70;
				led_light_frequencies[5] = 40;
				led_light_frequencies[6] = 10;
				led_light_frequencies[7] = 0;
				//0, 0, 0, 100, 70, 40, 10, 0
				break;
			}
			case 12:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 0;
				led_light_frequencies[2] = 100;
				led_light_frequencies[3] = 70;
				led_light_frequencies[4] = 40;
				led_light_frequencies[5] = 10;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				//0, 0, 100, 70, 40, 10, 0, 0
				break;
			}
			case 13:{
				led_light_frequencies[0] = 0;
				led_light_frequencies[1] = 100;
				led_light_frequencies[2] = 70;
				led_light_frequencies[3] = 40;
				led_light_frequencies[4] = 10;
				led_light_frequencies[5] = 0;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				//0, 100, 70, 40, 10, 0, 0, 0
				break;
			}
			case 14:{
				led_light_frequencies[0] = 100;
				led_light_frequencies[1] = 70;
				led_light_frequencies[2] = 40;
				led_light_frequencies[3] = 10;
				led_light_frequencies[4] = 0;
				led_light_frequencies[5] = 0;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				//100, 70, 40, 10, 0, 0, 0, 0
				break;
			}
			case 15:{
				led_light_frequencies[0] = 70;
				led_light_frequencies[1] = 100;
				led_light_frequencies[2] = 10;
				led_light_frequencies[3] = 0;
				led_light_frequencies[4] = 0;
				led_light_frequencies[5] = 0;
				led_light_frequencies[6] = 0;
				led_light_frequencies[7] = 0;
				//{70, 100, 10, 0, 0, 0, 0, 0
				break;
			}
			default:{
				//error handling
				led_light_frequencies[0] = 100;
				led_light_frequencies[1] = 100;
				led_light_frequencies[2] = 100;
				led_light_frequencies[3] = 100;
				led_light_frequencies[4] = 100;
				led_light_frequencies[5] = 100;
				led_light_frequencies[6] = 100;
				led_light_frequencies[7] = 100;
				//100, 100, 100, 100, 100, 100, 100, 100
				break;
			}
		}  //end switch cases
		
		current_led++;
		current_led %= RUNNING_LIGHT_POS;

	}	//end if led_counter % MAX_TICKS == 0 && tick_counter == 0
} //end function smeared_running_light


void controll_all_leds(){
	controll_led0();
	controll_led1();
	controll_led2();
	controll_led3();
	controll_led4();
	controll_led5();
	controll_led6();
	controll_led7();
}
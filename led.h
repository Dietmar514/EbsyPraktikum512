#if !defined(LED_H)
#define LED_H

#define ADDRESS_LED_0 0x0100
#define ADDRESS_LED_1 0x0200
#define ADDRESS_LED_2 0x0400
#define ADDRESS_LED_3 0x0800
#define ADDRESS_LED_4 0x1000
#define ADDRESS_LED_5 0x2000
#define ADDRESS_LED_6 0x4000
#define ADDRESS_LED_7 0x8000
#define MAX_TICKS 500
#define AVAILABLE_LEDS 8
#define RUNNING_LIGHT_POS 16 //TO DO: Check this

void controll_led0();
void controll_led1();
void controll_led2();
void controll_led3();
void controll_led4();
void controll_led5();
void controll_led6();
void controll_led7();
void smeared_running_light();
void controll_all_leds();

#endif
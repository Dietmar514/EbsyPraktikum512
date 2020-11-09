#include <stdint.h>
#include <LPC177x_8x.h>

uint32_t tick_counter = 0;
uint32_t led_counter = 0;

typedef uint32_t pid_t;
typedef uint32_t result_t;

#define PROCESS_COUNT 9
#define MAX_PROCESSES 9

#define ADDRESS_LED_0 0x0100
#define ADDRESS_LED_1 0x0200
#define ADDRESS_LED_2 0x0400
#define ADDRESS_LED_3 0x0800
#define ADDRESS_LED_4 0x1000
#define ADDRESS_LED_5 0x2000
#define ADDRESS_LED_6 0x4000
#define ADDRESS_LED_7 0x8000
#define MAX_TICKS 200
#define AVAILABLE_LEDS 8
#define RUNNING_LIGHT_POS 16 //TO DO: Check this

enum e_status{
	running,
	ready,
	blocked,
	terminated,
  zombie
};

struct s_process{
	void (*task)();
	pid_t pid;
	enum e_status status;
}s_process; //TO DO: Check this


pid_t pid = 0;

//array of all processes
struct s_process process_table[MAX_PROCESSES];

//array of all function pointers to all processes





void init(void) {
	LPC_GPIO0->DIR = 0xFFFFFFFF;
	LPC_GPIO0->CLR = 0xFFFFFFFF;

	for(int i = 0; i < MAX_PROCESSES; i++){
//		process_table[i] = NULL;
	}
}

pid_t get_new_pid(){
	uint32_t value = pid;
	pid++;
	return value;
}

uint32_t led_light_frequencies[AVAILABLE_LEDS] = {100};

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


	
	static uint32_t current_led;
	static uint32_t b_is_initialized;

	//start with LED 0	
	if(led_counter == 0 && tick_counter == 0){																														
		led_counter = 0;
		b_is_initialized = 0;
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




/**
 * @brief function to generate a new process
 * 
 * @param p_function pointer to function of the new process
 * @return pid_t id of new process
 */
pid_t create(void (*p_function)()){
	int new_pid = get_new_pid();
	struct s_process new_process;
	new_pid %= MAX_PROCESSES;
	new_process.pid = new_pid % MAX_PROCESSES;
	new_process.status = ready;
	new_process.task = p_function;
	process_table[new_pid] = new_process;
	
	return new_pid;
}

/**
 * @brief default function to destroy a terminated process
 * 
 * @param pid 
 * @return result_t number for errorhandling
 */

result_t destroy(pid_t _pid){
	if(process_table[_pid].status == terminated){
        process_table[_pid].status = zombie;
        return 0;
    }

		//Errorhandling
    if(process_table[_pid].status == ready){      
        return 1;
    }
        if(process_table[_pid].status == blocked){
        return 2;
    }
    if(process_table[_pid].status == running){   
        return 3;
    }
		return 4;
}

/**
 * @brief call the function of all processes which are in the process table
 * 
 */
void run_all_processes(){
		for (int pid = 0; pid < MAX_PROCESSES; pid++){                                               
			 if(process_table[pid].status == ready){
					//run process
					(*process_table[pid].task)();
					//set status to terminated after running							
					process_table[pid].status = terminated;			
			  }	
     }
	 }	
void (*tasklist[PROCESS_COUNT])() = {controll_led0, controll_led1, controll_led2, controll_led3, controll_led4, controll_led5, controll_led6, controll_led7,  smeared_running_light};
	 /**
 * @brief register all processes to the process table
 * 
 */
void register_all_processes(){
		for (int currTask = 0; currTask < PROCESS_COUNT; currTask++){		
			create(tasklist[currTask]);
		}
	}		
	
	
/**
 * @brief call the function of all processes which are in the process table
 * 
 */
void clear_process_table(){
	
     for (int pid = 0; pid < MAX_PROCESSES; pid++){		
			   if(process_table[pid].status == terminated){			
				    destroy(pid);				//don't care about return value, could be used for debugging										
			    }		
        }
}	


int main(void){

	//TO DO: Check if value of RUNNING_LIGHT_POS is correct
	//TO DO: Check struct s_process

	init();
	while(1){
		
		register_all_processes();

		run_all_processes();

		clear_process_table();

		tick_counter++;
		//to make sure that the value of tickcounter is between 0 and 100
		tick_counter %= 100;													
		if(tick_counter == 0){													
			led_counter++;
		}																													
}
}

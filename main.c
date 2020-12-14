#include <stdint.h>
#include <LPC177x_8x.h>
#include "first_context.h"
#include "switch_context.h"

typedef uint32_t pid_t;
typedef uint32_t result_t;

#define ADDRESS_LED_0 0x0100
#define ADDRESS_LED_1 0x0200
#define ADDRESS_LED_2 0x0400
#define ADDRESS_LED_3 0x0800
#define ADDRESS_LED_4 0x1000
#define ADDRESS_LED_5 0x2000
#define ADDRESS_LED_6 0x4000
#define ADDRESS_LED_7 0x8000
#define LED_GROUP_SIZE 4
#define PROCESS_COUNT 2

uint32_t current_process = 0;
uint32_t next_process = 0;
pid_t global_pid = 0;
uint8_t current_LED_grp_1 = 0;
uint8_t current_LED_grp_2 = 0;

uint8_t test_counter = 0;

uint32_t stack[PROCESS_COUNT][32];

uint32_t* curr;
uint32_t* next;

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
	int32_t remaining_runs;
	uint32_t* p_stack_pointer;
}; 


extern void first_context(uint32_t* p_sp);
extern void switch_context(uint32_t* p_old_stack, uint32_t* p_new_stack);
extern void delayms(uint32_t delay);
extern void PendSV_Hanlder(void);


//array of all processes
struct s_process process_table[PROCESS_COUNT];


void init(void) {
	LPC_GPIO0->DIR = 0xFFFFFFFF;
	LPC_GPIO0->CLR = 0xFFFFFFFF;
}

pid_t get_new_pid(){
	uint32_t value = global_pid;
	global_pid++;
	return value;
}


/**
 * @brief default function to destroy a terminated process
 * 
 * @param _pid 
 * @return result_t number for errorhandling
 */
result_t destroy(pid_t _pid){
		process_table[_pid].status = terminated;
		return 0;
}


void controll_led_grp_1(){	

	while(1){
		LPC_GPIO0->CLR = ADDRESS_LED_0 | ADDRESS_LED_1 | ADDRESS_LED_2 | ADDRESS_LED_3;
		
		switch(current_LED_grp_1){
			case 0: LPC_GPIO0->SET = ADDRESS_LED_0;
					break;
			case 1: LPC_GPIO0->SET = ADDRESS_LED_1;
					break;
			case 2: LPC_GPIO0->SET = ADDRESS_LED_2;
					break;
			case 3: LPC_GPIO0->SET = ADDRESS_LED_3;
					break;
			
			//Errorhandling
			default:LPC_GPIO0->SET = 0xFFFFFFFF;
					break;
		}
		
		current_LED_grp_1++;
		current_LED_grp_1 %= LED_GROUP_SIZE;
	}
}

void controll_led_grp_2(){
	
	while(1){

		LPC_GPIO0->CLR = ADDRESS_LED_4 | ADDRESS_LED_5 | ADDRESS_LED_6 | ADDRESS_LED_7;
		
		switch(current_LED_grp_2){
			case 0:	LPC_GPIO0->SET = ADDRESS_LED_4;
					break;
			case 1:	LPC_GPIO0->SET = ADDRESS_LED_5;
					break;
			case 2:	LPC_GPIO0->SET = ADDRESS_LED_6;
					break;
			case 3:	LPC_GPIO0->SET = ADDRESS_LED_7;
					break;
			
			//Errorhandling
			default:LPC_GPIO0->SET = 0xFFFFFFFF;
					break;
		}
		
		current_LED_grp_2++;
		current_LED_grp_2 %= LED_GROUP_SIZE;
	}
}

void idle_task(){
	
	while(1){
		delayms(500);
		test_counter++;
		if(test_counter == 8){
			destroy(0);
		}
	}
}

/**
 * @brief function to generate a new process
 * 
 * @param p_function pointer to function of the new process
 * @return pid_t id of new process
 */
pid_t create(void (*p_function)(), int _remaining_runs){
	int new_pid = get_new_pid();
	struct s_process new_process;
	new_pid %= PROCESS_COUNT;
	new_process.pid = new_pid % PROCESS_COUNT;
	new_process.status = ready;
	new_process.task = p_function;
	//-1 to run all processes for ever
	new_process.remaining_runs = _remaining_runs;

	process_table[new_pid] = new_process;

	return new_pid;
}



//array of all function pointers to all processes
void (*tasklist[PROCESS_COUNT])() = {controll_led_grp_1, controll_led_grp_2};


/**
 * @brief register all processes to the process table
 * 
 */
void register_all_processes(){
	for (int currTask = 0; currTask < PROCESS_COUNT; currTask++){	
		create(tasklist[currTask], -1);
		process_table[currTask].p_stack_pointer = &stack[currTask][18];
		*(process_table[currTask].p_stack_pointer + 13) = (uint32_t) process_table[currTask].task;
	}
}


	
	
/**
 * @brief call the function of all processes which are in the process table
 * 
 */
void clear_process_table(){
	
     for (int pid = 0; pid < PROCESS_COUNT; pid++){		
			   if(process_table[pid].status == terminated){			
				    destroy(pid);									
			    }		
        }
}

void HardFault_Handler(void){
	while (1) {
		LPC_GPIO0->SET = 0xFFFFFFFF;
		//TODO: implement some debug infos
	}
}

void SysTick_Handler(void){
	current_process %= PROCESS_COUNT;
	next_process = ((current_process + 1) % PROCESS_COUNT);
	
	while(process_table[next_process].status == terminated){
		current_process++;
		current_process %= PROCESS_COUNT;
		next_process = ((current_process + 1) % PROCESS_COUNT);
	}
	curr = process_table[current_process++].p_stack_pointer;
	next = process_table[next_process].p_stack_pointer;
	SCB->ICSR = 0x10000000; //bit 28 PendSV set
	//trigger PendSV Handler
}


int main(void){
	init();
	register_all_processes();
	SysTick->CTRL = 7;
	SysTick->LOAD = 120000;
  first_context(process_table[0].p_stack_pointer);
	while(1){
			//should never be here
	}
}


/* debug tools
Peripherals -> Core Peripherals -> System Tick Timer
Peripherals -> Core Peripherals -> Nested Vectored Interrupt Controller
*/


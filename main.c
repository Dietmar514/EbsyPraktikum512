#include <stdint.h>
#include <LPC177x_8x.h>
#include "global.h"
#include "led.h"


typedef uint32_t pid_t;
typedef uint32_t result_t;

#define PROCESS_COUNT 9
#define MAX_PROCESSES 1000


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
void (*tasklist[PROCESS_COUNT])(int) = {controll_led0, controll_led1, controll_led2, controll_led3, controll_led4, controll_led5, controll_led6, controll_led7,  smeared_running_light};




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


/**
 * @brief function to generate a new process
 * 
 * @param p_function pointer to function of the new process
 * @return pid_t id of new process
 */
pid_t create(void* p_function){
	int new_pid = get_new_pid();
	struct s_process new_process;
	new_process.pid = new_pid % MAX_PROCESSES;
	new_process.status = ready;
	new_process.task = p_function;
	process_table[new_pid] = new_process;
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
																																					
}
}

#include <stdint.h>
#include <LPC177x_8x.h>
#include "delay.h"

#typedef uint32_t pid_t;
#typedef uint32_t result_t;
#define delay 300	//delay in ms
#define processCount 9
#define freq 5
#define numLed 16
#define tick 500
#define MAX_PROCESSES 1000

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
pid_t globalPID = 0;
Process ProcessTable[MAX_PROCESSES];

enum TaskStatus{
	running,
	ready,
	blocked,
	terminated,
    zombie
}

struct Process{
	void* task;
	pid_t processID;
	TaskStatus status;
}process;


void init(void) {
	LPC_GPIO0->DIR = 0xFFFFFFFF;
	LPC_GPIO0->CLR = 0xFFFFFFFF;
}



void controllLed1(){			//duty-cycle = timeActive/cycleLength	
	if (tickcounter < LEDfrequency[0]){
		LPC_GPIO0->SET = led1_value;
	}
	else{
		LPC_GPIO0->CLR = led1_value;
	}

}

void controllLed2(){
	if (tickcounter < LEDfrequency[1]){
		LPC_GPIO0->SET = led2_value;
	}
	else{
		LPC_GPIO0->CLR = led2_value;
	}
}

void controllLed3(){
	if (tickcounter < LEDfrequency[2]){
		LPC_GPIO0->SET = led3_value;
	}
	else{
		LPC_GPIO0->CLR = led3_value;
	}
}

void controllLed4(){
	if (tickcounter < LEDfrequency[3]){
		LPC_GPIO0->SET = led4_value;
	}
	else{
		LPC_GPIO0->CLR = led4_value;
	}
}

void controllLed5(){
	if (tickcounter < LEDfrequency[4]){
		LPC_GPIO0->SET = led5_value;
	}
	else{
		LPC_GPIO0->CLR = led5_value;
	}
}

void controllLed6(){
	if (tickcounter < LEDfrequency[5]){
		LPC_GPIO0->SET = led6_value;
	}
	else{
		LPC_GPIO0->CLR = led6_value;
	}
}

void controllLed7(){
	if (tickcounter < LEDfrequency[6]){
		LPC_GPIO0->SET = led7_value;
	}
	else{
		LPC_GPIO0->CLR = led7_value;
	}
}

void controllLed8(){
	if (tickcounter < LEDfrequency[7]){
		LPC_GPIO0->SET = led8_value;
	}
	else{
		LPC_GPIO0->CLR = led8_value;
	}
}

void verschmiertesLauflicht(){
	
	static uint32_t currentLED;
	static uint32_t isInitialized;
	if(ledCounter == 0){
		currentLED = 0;
		isInitialized = 0
	}
	
	if(ledCounter % tick == 0 && tickcounter == 0){
		if(isInitialized && currentLED < 2){
			currentLED = 2;
		}		
		
		switch(currentLED){
			case 0:{
				LEDfrequency[] = {100, 0, 0, 0, 0, 0, 0, 0};
				break;
			}
			case 1:{
				LEDfrequency[] = {70, 100, 0, 0, 0, 0, 0, 0};
				break;
			}
			case 2:{
				LEDfrequency[] = {40, 70, 100, 0, 0, 0, 0, 0};
				isInitialized = 1;
				break;
			}
			case 3:{
				LEDfrequency[] = {10, 40, 70, 100, 0, 0, 0, 0};
				break;
			}
			case 4:{
				LEDfrequency[] = {0, 10, 40, 70, 100, 0, 0, 0};
				break;
			}
			case 5:{
				LEDfrequency[] = {0, 0, 10, 40, 70, 100, 0, 0};
				break;
			}
			case 6:{
				LEDfrequency[] = {0, 0, 0, 10, 40, 70, 100, 0};
				break;
			}
			case 7:{
				LEDfrequency[] = {0, 0, 0, 0, 10, 40, 70, 100};
				break;
			}case 8:{
				LEDfrequency[] = {0, 0, 0, 0, 0, 10, 100, 70};
				break;
			}
			case 9:{
				LEDfrequency[] = {0, 0, 0, 0, 0, 100, 70, 40};
				break;
			}
			case 10:{
				LEDfrequency[] = {0, 0, 0, 0, 100, 70, 40, 10};
				break;
			}
			case 11:{
				LEDfrequency[] = {0, 0, 0, 100, 70, 40, 10, 0};
				break;
			}
			case 12:{
				LEDfrequency[] = {0, 0, 100, 70, 40, 10, 0, 0};
				break;
			}
			case 13:{
				LEDfrequency[] = {0, 100, 70, 40, 10, 0, 0, 0};
				break;
			}
			case 14:{
				LEDfrequency[] = {100, 70, 40, 10, 0, 0, 0, 0};
				break;
			}
			case 15:{
				LEDfrequency[] = {70, 100, 10, 0, 0, 0, 0, 0};
				break;
			}
			default:{}
		}
		
		currentLED++;
		currentLED %= numLed;
	}
}





pid_t create(void* function){
	process createdProcess;
	createdProcess.processID = globalPID % MAX_PROCESSES;
	createdProcess.status = ready;
	createdProcess.task = function;
	ProcessTable[globalPID] = createdProcess;
	globalPID++;
}

result_t destroy(pid_t pid){
    if(ProcessTable[pid].status == ready){      //should not happens, but could happens
        ProcessTable[pid].status = zombie;
        return 1;
    }
        if(ProcessTable[pid].status == blocked){
        ProcessTable[pid].status = zombie;
        return 2;
    }
    if(ProcessTable[pid].status == running){    //process still running!
        ProcessTable[pid].status = zombie;
        return 3;
    }
    if(ProcessTable[pid].status == terminated){
        ProcessTable[pid].status = zombie;
        return 0;
    }
}



void (*tasklist[processCount])(int) = { controllLed1, controllLed2, controllLed3, controllLed4, controllLed5, controllLed6, controllLed7, controllLed8,  verschmiertesLauflicht};


int main(void){

	init();
	while (1){
		
		for (int currTask = 0; currTask < processCount; currTask++){       //create random processes
			create(tasklist[currTask]);
		}

		for (int pid = 0; pid < MAX_PROCESSES; pid++){                      //run all ready tasks bzw. registrierte Prozesse
            if(ProcessTable[pid]){                                          //ProcessTable[i] could be null bzw. uninitalisiert
			    if(ProcessTable[pid].status == ready){
				    (*ProcessTable[currTask])();                            //only run the process if the status is ready
				    ProcessTable[currTask].status = terminated;             //set status to terminated after running
			    }		
	    	}
        }


        for (int pid = 0; pid < MAX_PROCESSES; pid++){                        //destroy all terminated tasks
            if(ProcessTable[pid]){                                            //ProcessTable[i] could be null bzw. uninitalisiert
			    if(ProcessTable[pid].status == terminated){
				    destroy(i);                                               //don't care about return value, could be used for debugging
			    }		
	    	}
        }

		tickcounter++;
		tickcounter %= 100;
		if(tickcounter == 0){
			ledCounter++;
		}
}
}

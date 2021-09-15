#include "main.h"

void mili_seg(){
	//uint16_t i = 362;
	uint16_t i = 100;
	for(i;i>0;i--);
}

void delay(uint16_t ms){
	uint16_t i;
	for(i=0;i<ms;i++){
		mili_seg();
	}
} 

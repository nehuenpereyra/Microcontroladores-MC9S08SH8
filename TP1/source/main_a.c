#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "main.h"
#include "lib_time.h"

#ifdef __cplusplus
extern "C"
#endif
const TIME_DELAY = 15;
void MCU_init(void); /* Device initialization function declaration */
void recorrido(uint8_t);
void inicializacion_recorrido();

void main(void) {
	
  // Declaracion de variables
  uint8_t index = 1;
  MCU_init();	/* call Device Initialization */

  inicializacion_recorrido();
  for(;;) {
	  recorrido(index);
	  index++;
	  if(index==9) index=1;	  
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
}

void inicializacion_recorrido(){
	//Configuro como salida el puerto B
	PTBDD = 0xFF;
	//Configuro High Drive al puerto B (capacidad para entregar hasta 20mA)
	PTBDS = 0xFF;
	//Se inicializa las salidas del puerto B
	PTBD = 0x00;
}


void recorrido(char index){
	switch(index){
	case 1: PTBD = 0x01; break;
	case 2: PTBD = 0x02; break;
	case 3: PTBD = 0x04; break;
	case 4: PTBD = 0x08; break;
	case 5: PTBD = 0x10; break;
	case 6: PTBD = 0x20; break;
	case 7: PTBD = 0x40; break;
	case 8: PTBD = 0x80; break;
	}
	delay(TIME_DELAY);
};
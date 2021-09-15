#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "types.h"

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

volatile uint8_t string[11];
volatile uint32_t temperatura;
volatile uint32_t tempGrados;

void main(void) {
  MCU_init();	

  /* Configuración del ADC */
  ADCCFG = 0x18;
  APCTL1_ADPC0 = 1;
  ADCSC1 = 0x20;
  
  /* Configuro los puertos PTC0 y PTC1  como salida */
  PTCDD_PTCDD0 = 1;
  PTCDD_PTCDD1 = 1;
  
  /* Configuro los puertos PTC0 y PTC1  con valor bajo*/
  PTCD_PTCD0 = 0;
  PTCD_PTCD1 = 0;
  
  for(;;) {
	  if(ADCSC1_COCO == 1){
		  
		  /* Se mide la temperatura ambiente */
		  temperatura = ADCR;
		  if(temperatura == 0){
			  tempGrados = 0;
		  }else{
			  tempGrados = ((temperatura * 330)/1024)+ 1 ; 
		  }
		  
		 /* Se enciende el pin correspondiente segun la temperatura detectada */
	     if(temperatura>744){
	    	 PTCD_PTCD0 = 1;
	    	 PTCD_PTCD1 = 0;
	     }else{
	    	 if(temperatura<527){
	    		 PTCD_PTCD0 = 0;
	    		 PTCD_PTCD1 = 1;
	    	 }else{
	    		 PTCD_PTCD0 = 0;
	    		 PTCD_PTCD1 = 0;
	    	 }
	     }
	  }
  }
  
}

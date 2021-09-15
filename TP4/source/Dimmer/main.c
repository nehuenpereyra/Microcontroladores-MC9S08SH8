#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "types.h"

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

volatile uint16_t temperatura;

void main(void) {
  MCU_init();	

  for(;;) {
	  /* Cuando se active el flag de COCO 
	   * indica que ya se ha realizado la conversión
	   * (de un valor analogico a un valor digital, que
	   * por como esta configurado es de 1 byte) 
	   * establecemos el valor del canal del TPM para 
	   * setear el nuevo ciclo de trabajo dependiendo
	   * de la tensión medida.
	   * Como la conversión es de 1 byte y dado que el TPM
	   * se configuro con un modulo de 256 no se requiere calculo
	   * extra para establecer el ciclo de trabajo. 
	   * */
	  if(ADCSC1_COCO == 1){
		  temperatura = ADCR; 
		  TPM1C1V = ADCR;
	  }
  } 
  
}

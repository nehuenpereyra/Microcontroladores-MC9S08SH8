#include <mc9s08sh8.h>
#include "lib/sound.h"
#include "types.h"


#define PRE_TPM1_4  4
#define PRE_TPM1_8  8

#define MIN_FREQ      10
#define MAX_FREQ      1000
#define DEFAULT_FREQ  400

static uint16_t nc;

/* Inicializa el modulo TPM. Se establece la frecuencia por default a 400 Hz */
void sound_init(){
	sound_set_freq(DEFAULT_FREQ);
	sound_off();
}

/* Enciende el sonido */
void sound_on(void){
	TPM1C0SC_CH0IE = 1;
	TPM1C0SC_ELS0A = 1;
	TPM1C0SC_ELS0B = 0;
}

/* Apaga el sonido */
void sound_off(void){
	TPM1C0SC_CH0IE = 0;
	TPM1C0SC_ELS0A = 0;
	TPM1C0SC_ELS0B = 1;
}

/*
 * Permite establecer la frecuencia.
 * Parametro:
 *     f: valor de la frecuencia a realizar.
 * Retorna:
 *	   Si esta fuera de rango la recuencia 0, sino el valor 1.
 */
char sound_set_freq(const uint16_t f){	
	if (f < MIN_FREQ || f > MAX_FREQ)
		return 0;
	if(f<=15){
		TPM1SC_PS0 = 1;
		TPM1SC_PS1 = 1;
		TPM1SC_PS2 = 0;
		nc = 4000000UL/(PRE_TPM1_8*f);	
	}else{
		TPM1SC_PS0 = 0;
		TPM1SC_PS1 = 1;
		TPM1SC_PS2 = 0;
		nc = 4000000UL/(PRE_TPM1_4*f);
	}
	return 1;
}

/* Manejador de interrupción del TPM */
void sound_int_handler(){
	TPM1C0V += nc;
	TPM1C0SC;
	TPM1C0SC_CH0F=0;
}


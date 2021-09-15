/*
 * keypad.c
 *
 *  Created on: 30/04/2020
 *      Author: Nehuen
 */
#include "derivative.h" /* include peripheral declarations */
#include "main.h"
/* Determina los caracteres que se corresponden a cada tecla del teclado. */
const uint8_t KEY_PAD[4][4] = {
							{'1','2','3','A'},
							{'4','5','6','B'},
							{'7','8','9','C'},
							{'*','0','#','D'}};


void keypad_init(void){
	//Configuro las salidas de PTB [0:3] y entradas [4:7]
	PTBDD = 0x0F;
	// Configuramos las resistencias de pull-up PTB[4:7]
	PTBPE = 0xF0;
}


uint8_t teclado(){
	uint8_t secuancia[] = { 0xFE, 0xFD, 0xFB, 0xF7};
	uint8_t i, renglon, dato;
	
	for(renglon=0, i=0; i<4; i++){
		PTBD = secuancia[i];
		dato = PTBD & 0xF0;
		if(dato!=0xF0){
			//evitar rebotes
			switch(dato){
				case 0xEF: return renglon;
				case 0xD0: return renglon + 1;
				case 0xB0: return renglon + 2;
				case 0x70: return renglon + 3;
			}
		}
		renglon += 4;
	}
	// Ninguna tecla se preciono
	return 0xFF;
}


unsigned char keypad_scan(uint8_t *pressed_key){
	switch(teclado()){
		case 0: *pressed_key = KEY_PAD[0][0];
		case 1: *pressed_key = KEY_PAD[0][1];
		case 2: *pressed_key = KEY_PAD[0][2];
		case 3: *pressed_key = KEY_PAD[0][3];
		case 4: *pressed_key = KEY_PAD[1][0];
		case 5: *pressed_key = KEY_PAD[1][1];
		case 6: *pressed_key = KEY_PAD[1][2];
		case 7: *pressed_key = KEY_PAD[1][3];
		case 8: *pressed_key = KEY_PAD[2][0];
		case 9: *pressed_key = KEY_PAD[2][1];
		case 10: *pressed_key = KEY_PAD[2][2];
		case 11: *pressed_key = KEY_PAD[2][3];
		case 12: *pressed_key = KEY_PAD[3][0];
		case 13: *pressed_key = KEY_PAD[3][1];
		case 14: *pressed_key = KEY_PAD[3][2];
		case 15: *pressed_key = KEY_PAD[3][3];
		case -1: *pressed_key = -1;
	}
	return *pressed_key;
}

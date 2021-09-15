#include "types.h"
#include <math.h>   
extern volatile uint8_t string[11];
extern volatile float tempGrados;

void temp_get_string(){	
	uint8_t dig1, dig2, dig3;
	float aux;

	/*
	aux = fmod(tempGrados,10);
	dig2 = (unsigned char) aux;
	aux = fmod(aux,10);
	dig1 = (unsigned char) aux;
	aux = (aux * 10);
	dig3 = (unsigned char) aux;
	*/
	string[0] = 'T';
	string[1] = 'E';
	string[2] = 'M';
	string[3] = 'P';
	string[4] = ':';
	string[5] = 1+'0'; 
	string[6] = 2+'0';
	string[7] = '.';
	string[8] = 3+'0';
	string[9] = 'C';
	string[10] = '\0';		
}

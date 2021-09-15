#include "types.h"

extern volatile uint8_t string[11];
extern volatile uint32_t tempGrados;

void temp_get_string(){	
	uint8_t dig1, dig2, dig3;
	
	dig3 = tempGrados % 10;
	tempGrados = tempGrados / 10;
	dig2 = tempGrados % 10;
	tempGrados = tempGrados / 10;
	dig1 = tempGrados % 10;
	
	string[0] = 'T';
	string[1] = 'E';
	string[2] = 'M';
	string[3] = 'P';
	string[4] = ':';
	string[5] = dig1+'0'; 
	string[6] = dig2+'0';
	string[7] = '.';
	string[8] = dig3+'0';
	string[9] = 'C';
	string[10] = '\0';		
}

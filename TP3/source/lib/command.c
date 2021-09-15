#include "lib/command.h"

/* Defino la estructura de un comando */
struct command
{
	uint8_t stx;
	uint8_t op;
	uint8_t len;
	uint8_t data[2];
	uint8_t chks;
	uint8_t etx;
	
};

/* Defino la variable en donde se almacenara el comando recibido */
volatile static struct command receive_command;

/*
 * Parsea el arreglo recibido por parametro, si no cumple con la
 * estructura se establece en el comando recibido la operacion como invalida. 
 * Parametro:
 *     line: una arreglo que representa un comando recibido.
 */
void command_parse(const char * line){
	
	receive_command.op = COMMAND_INVALID;	
	
	if(line[0]==0x02){			
			if(line[2]==0x01 && line[5]==0x03){
				receive_command.stx = line[0];
				receive_command.op = line[1];
				receive_command.len = line[2];
				receive_command.data[0] = line[3];
				receive_command.chks = line[4];
				receive_command.etx = line[5];
			}
			if(line[2]==0x02 && line[6]==0x03){
				receive_command.stx = line[0];
				receive_command.op = line[1];
				receive_command.len = line[2];
				receive_command.data[0] = line[3];
				receive_command.data[1] = line[4];
				receive_command.chks = line[5];
				receive_command.etx = line[6];		
			}
		}
}


/*
 * Evalua el comando recibido y retorna a que operacion corresponde.
 * Retorna:
 *     El valor del comando a ejecutar.
 */
int8_t command_operation(){
	switch (receive_command.op) {
		case 0x01:
			return COMMAND_ON;
		case 0x02:
			return COMMAND_FREQ_SET;
		case 0x03:
			return COMMAND_OFF;
		default:
			return -1;
	}
}

/*
 * Convierte el dato del comando a un valor int.
 * Retorna:
 *     El valor del dato en el comando como un valor tipo int.
 */
int16_t data_to_int(){
	if(receive_command.len == 0x01){
		return receive_command.data[0];
	}
	return receive_command.data[0]*256+receive_command.data[1];
}


/* Retorna el valor del paramtros que es enviado en el comando */
void command_get_args(uint16_t * args){
	*args = data_to_int();
}

/*
 * Realiza el calculo del Checksum.
 * Retorna:
 *     El valor del calculo del checksum.
 */
int8_t command_calc_checksum(){
	int8_t checksum = receive_command.stx^receive_command.op^receive_command.len^receive_command.data[0];
	if(receive_command.len == 0x02)
		checksum ^= receive_command.data[1];
	return checksum;
}

/*
 * Establece el formato de la respuesta que se da al comando recibido.
 * Parametro:
 *     line: arreglo que representa la instruccion de respuesta al comando
 *     ingresado por el usuario.
 */
int8_t command_response(uint8_t * line){
	line[0] = 0x02;
	line[1] = receive_command.op;
	line[2] = 0x01;
	if(command_calc_checksum()== receive_command.chks){
		line[3] = 0xAA;
		if(data_to_int() < 10 || data_to_int() > 1000){
			line[3] = 0x55;
		}
	}else{
		line[3] = 0xFF;
	}
	line[4] = line[0]^line[1]^line[2]^line[3];
	line[5] = 0x03;	
}


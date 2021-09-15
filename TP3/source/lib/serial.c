#include "lib/serial.h"
#include "io/buffer.h"
#include "types.h"
#include <mc9s08sh8.h>

/* Flags de recepción de datos */
static volatile char rx = 0;

/* Buffers utilizados para recepción y transmisión de datos */
static volatile struct buffer buffer_rx;
static volatile struct buffer buffer_tx;

/* Inicializacion de los buffers de transmision y recepción */
void serial_init(){
	buffer_init(&buffer_rx);
	buffer_init(&buffer_tx);
}

/*
 * Permite enviar una cadena de caracteres de forma serie.
 * Parametro:
 *     buff: cadena de caracteres a enviar.
 */
void serial_send(const char * buff){
	SCIC2_TIE = 0;
	while (*buff) {
		if (buffer_full(&buffer_tx)) {
			SCIC2_TIE = 1;
			while (SCIC2_TIE);
		}
		buffer_push(&buffer_tx, *(buff++));
	}
	SCIC2_TIE = 1;
}

/*
 * Permite recibir una cadena de caracteres de forma serie e ir
 * almacenadola en un buffer.
 * Parametro:
 *     buff: buffer donde se almacenara la cadena recibida.
 *     n: tamaño de la cadena a recibir.
 */
void serial_recv(char * buff, const uint8_t n){
	uint8_t count = 0;
	uint8_t car;

	/* Se toma el control del buffer */
	SCIC2_RIE = 0;
	
	while (count < n ) {
		if (buffer_empty(&buffer_rx)) {
			rx = 0;
			SCIC2_RIE = 1;
			while(!rx);
			SCIC2_RIE = 0;
		}
		
		car = buffer_pop(&buffer_rx);
		*(buff++) = car;
		count++;
		
		/* Identifica si es una instruccion de 6 caracteres */
		if(car == 0x01 && count == 3)
			count++;
}

	/* Se deja de tomar el control sobre el buffer */
	SCIC2_RIE = 1;
}

/* Manejador de interrupción a ejecutarse cada vez que el hardware dispone un caracter por puerto serial */
void serial_rx_handler(){
	if (SCIS1_RDRF) {
		buffer_push(&buffer_rx, SCID);
		rx = 1;
	}

	if (buffer_full(&buffer_rx))
		SCIC2_RIE = 0;
}

/* Manejador de interrupción a ejecutarse cada vez que el hardware puede mandar un caracter por puerto serie */
void serial_tx_handler(){
	if (buffer_empty(&buffer_tx)) {
		SCIC2_TIE = 0;
		return;
	}
	
	if (SCIS1_TDRE)
		SCID = buffer_pop(&buffer_tx);
}

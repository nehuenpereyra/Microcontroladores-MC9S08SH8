#include <hidef.h>
#include "derivative.h"
#include "lib/serial.h"
#include "lib/command.h"
#include "lib/sound.h"


void MCU_init(void);


#define STR_MSIZE 7
char str[STR_MSIZE], resp[6];
static uint16_t arg;

void main(void) {
	serial_init();
	MCU_init();
	sound_init();
	for (;;) {
		serial_recv(str, STR_MSIZE);
		command_parse(str);
		switch(command_operation()) {
			case COMMAND_OFF:
			sound_off();
			command_response(resp);
			serial_send(resp);
			break;
			case COMMAND_ON:
			sound_on();
			command_response(resp);
			serial_send(resp);
			break;
			case COMMAND_FREQ_SET:
			command_get_args(&arg);
			sound_set_freq(arg);
			command_response(resp);
			serial_send(resp);
			break;
			default:
			serial_send("Comando invalido.");
		}

	}
}

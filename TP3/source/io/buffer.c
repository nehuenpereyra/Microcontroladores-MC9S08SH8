#include "io/buffer.h"
#include "types.h"

/*
 * Inicializa un buffer.
 * Parametro:
 *     b: buffer a inicializar.
 */
void buffer_init(volatile struct buffer *b){
	b->size = 0;
	b->head = 0;
	b->tail = 0;
}

/*
 * Agrega un elemento a la cola.
 * Parametro:
 *     caracter: Caracter a agregar.
 */
void buffer_push(volatile struct buffer *b, uint8_t val){
	b->array[b->head] = val;
	if (++(b->size) > BUFFER_CAPACIDAD) {
		b->size = BUFFER_CAPACIDAD;
		b->tail = (b->tail + 1) & BUFFER_MOD_MASK;
	}
	b->head = (b->head + 1) & BUFFER_MOD_MASK;
}

/*
 * Saca el primer elemento agregado a la cola.
 * Devuelve: El primer caracter agregado a la cola.
 */
uint8_t buffer_pop(volatile struct buffer *b){
	uint8_t val;
	b->size--;
	val = b->array[b->tail];
	b->tail = (b->tail + 1) & BUFFER_MOD_MASK;
	return val;
}

/*
 * Retorna el tamaño del buffer pasado por paramtro.
 */
uint8_t buffer_size(volatile struct buffer *b){
	return b->size;
}

/*
 * Comprueba si el buffer esta vacio.
 * Devuelve: Valor uno si esta vacia, cero caso contrario.
 */
uint8_t buffer_empty(volatile struct buffer *b){
	return !b->size;
}

/*
 * Comprueba si el buffer esta lleno.
 * Devuelve: Valor uno si esta compelto el buffer, cero caso contrario.
 */
uint8_t buffer_full(volatile struct buffer *b){
	return b->size == BUFFER_CAPACIDAD;
}

#include <stdint.h>
#include <stdbool.h>

//Estructura de la maquina de estados
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

//Funcion de estado inicial
void debounceFSM_init(void);

//Funcion de cambio de estado
void debounceFSM_update(void);

//Funcion de asignacion de accion cuando el boton es presionado (flanco subida)
void buttonPressed(void);

//Funcion de asignacion de accion cuando el boton es soltado (flanco bajada)
void buttonReleased(void);

//Funcion flag para identificar el estado de la tecla
bool_t readKey(void);

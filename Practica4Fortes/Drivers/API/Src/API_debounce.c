#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include "API_debounce.h"

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

#define DEBOUNCE_DELAY 40

static debounceState_t debounceState;

delay_t DelayDeb;

static bool_t button = 0;


void debounceFSM_init(void){
	debounceState = BUTTON_UP;
	delayInit(&DelayDeb,DEBOUNCE_DELAY);

}


void debounceFSM_update(void){
		switch(debounceState){
		case BUTTON_UP:
			if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==0){
				debounceState = BUTTON_FALLING;
			}
		break;

		case BUTTON_FALLING:
			if(delayRead(&DelayDeb)==1){
				if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==0){
					debounceState = BUTTON_DOWN;
					buttonPressed();
				}
				if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==1){
					debounceState = BUTTON_UP;
				}
			}
		break;

		case BUTTON_DOWN:
			if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==1){
				debounceState = BUTTON_RAISING;
			}
		break;

		case BUTTON_RAISING:
			if(delayRead(&DelayDeb)==1){
				if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==1){
					debounceState = BUTTON_UP;
					buttonReleased();
				}
				if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)==0){
					debounceState = BUTTON_DOWN;
				}
			}
		break;

		default:
		debounceState = BUTTON_UP;
		}


}
void buttonPressed(void){
	button = 1;

}

void buttonReleased(void){

}

bool_t readKey(void){

	if(button){
		button = 0;
		return 1;
	}
	else
		return 0;
}

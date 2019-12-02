#include <stm32f051x8.h>

int main(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER8_0;
	GPIOA->OTYPER &= GPIO_OTYPER_OT_8;
	unsigned long i = 0;
	GPIOA->ODR |= GPIO_ODR_8;
	while(1){
		i++;
		if(i == 100000){
			//GPIOA->ODR |= GPIO_ODR_8;
		}
		if(i == 200000){
		//	GPIOA->ODR &= GPIO_ODR_8;
			i = 0;
		}		
	}
}
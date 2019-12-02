/*RCC block adress 0x4002 1000
RCC_AHBENR 0x14
result adress 0x4002 1014
GPIOC_MODER adress 0x4800 0800
GPIOC_OTYPER adress 0x04
result adress 0x4800 0804
GPIOC_ODR adress 0x14
result adress 0x4800 0814
*/

#include <stm32f051x8.h>
#include <stm32f0xx.h>

#define RCC_AHBENR (unsigned volatile long*)0x40021014 
	
#define GPIOA_MODER (unsigned volatile long*)0x48000000
#define GPIOA_IDR (unsigned volatile long*)0x48000010

#define GPIOC_MODER (unsigned volatile long*)0x48000800
#define GPIOC_ODR (unsigned volatile long*)0x48000814
#define GPIOC_BSRR (unsigned volatile long*)0x48000818
	
#define EXTI_IMR (unsigned volatile long*)0x40010400
#define EXTI_RTSR (unsigned volatile long*)0x40010408
#define NVIC_ISER0 (unsigned volatile long*)0x00000054
	


int main(){
	//__enable_irq ();
	*(RCC_AHBENR) |= 0x80000; //enabled 19 bit to activate GPIOC
	*(RCC_AHBENR) |= 0x20000; //enabled 17 bit ti activate GPIOA	
	
	/**(EXTI_IMR) |= 0x1;
	*(EXTI_RTSR) |= 0x1;
	*(NVIC_ISER0) |= 0x20;
	NVIC_EnableIRQ (EXTI0_1_IRQn);*/
	volatile unsigned long i=0;
  i++; i++; i++;
  i=0;
	*(GPIOC_MODER) |= 0x50000;	//enabled 19 & 17 bit to activate PC9 & PC8 as output
	*(GPIOA_MODER) |= 0x0;
	

	

	/*while(1){		//blinking
		for( i=0; i<100000 ;++i )			
		*(GPIOC_ODR) &= ~0x100;
		*(GPIOC_BSRR) |= 0x2000000;
		for( i=0; i<100000 ;++i )
		*(GPIOC_ODR) |= 0x100;
		*(GPIOC_BSRR) |= 0x200;
	}	
	
	while(1){	 //more optimal blinking
		i++;
		if(i==200000){			
			*(GPIOC_ODR) &= ~0x100;
			*(GPIOC_BSRR) |= 0x2000000;
		}
		if(i==100000){
			*(GPIOC_ODR) |= 0x100;
			*(GPIOC_BSRR) |= 0x200;
		}
		if(i == 200000)
			i = 0;
	}	*/
	
	
	unsigned long mask = 0x1; //Input and blinking
	while(1){	
		i++;
		if(i==200000){			
			*(GPIOC_ODR) &= ~0x100;
			*(GPIOC_BSRR) |= 0x2000000;
		}
		unsigned long inp0 = *(GPIOA_IDR) & mask; //Reading IDR 
		if(i==100000){
			*(GPIOC_ODR) |= 0x100;			
		}
		if(i == 200000)
			i = 0;
	}	
}

void EXTI0_1_IRQHandler(void){
	*(GPIOC_BSRR) |= 0x200;
	EXTI->PR |= EXTI_PR_PR0;	
}

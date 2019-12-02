#include <stm32f051x8.h>

volatile int a = 0;
unsigned temp;
int data[2] = {0,0}; 
int di = 0;

int main(){
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER8_0;
	//GPIOC->OTYPER &= GPIO_OTYPER_OT_8;
	
	GPIOC->MODER |= GPIO_MODER_MODER9_0;
	GPIOC->OTYPER &= GPIO_OTYPER_OT_9;
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	EXTI->IMR |= EXTI_IMR_IM0; 
	EXTI->RTSR |= EXTI_RTSR_RT0;
	
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER0;
	GPIOB->MODER |= GPIO_MODER_MODER1;

	RCC->CFGR |= RCC_CFGR_ADCPRE;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	
	ADC1->CR |= ADC_CR_ADCAL;	
	while ((ADC1->CR & ADC_CR_ADCAL) != 0);	
	ADC1->CR |= ADC_CR_ADEN;
	ADC1->SMPR |= ADC_SMPR_SMP;
	ADC1->IER |= ADC_IER_EOCIE;	
	ADC1->CFGR1 |= ADC_CFGR1_CONT;
	ADC1->CHSELR |= ADC_CHSELR_CHSEL8 | ADC_CHSELR_CHSEL9;	
	ADC1->CR |= ADC_CR_ADSTART;	
	
	
	NVIC_EnableIRQ (EXTI0_1_IRQn);	
	NVIC_EnableIRQ (ADC1_IRQn);
	__enable_irq ();
	
	unsigned long i = 0;	
	//GPIOC->ODR |= GPIO_ODR_8;
	while(1){
		/*i++;
		if(i == 100000){
			GPIOC->ODR &= ~GPIO_ODR_8;
		}
		if(i == 200000){
			GPIOC->ODR |= GPIO_ODR_8;
			i = 0;
		}	*/
		if(data[0] >= 2048)
			GPIOC->ODR |= GPIO_ODR_9;
		if(data[0] < 2048)
			GPIOC->ODR &= ~GPIO_ODR_9;
		if(data[1] >= 2048)
			GPIOC->ODR |= GPIO_ODR_8;
		if(data[1] < 2048)
			GPIOC->ODR &= ~GPIO_ODR_8;
	}
}

void EXTI0_1_IRQHandler(void){	
	GPIOC->ODR |= GPIO_ODR_9;				
	for(int i = 0; i < 1000000; i++);			
	GPIOC->ODR &= ~GPIO_ODR_9;	
	EXTI->PR |= EXTI_PR_PR0;	
}

void ADC1_COMP_IRQHandler(void){		
	data[di] = ADC1->DR;
	di++;
	if(di == 2)
		di = 0;
	//GPIOC->ODR |= GPIO_ODR_9;			

	//ADC1->ISR |= ADC_ISR_EOC;
}  

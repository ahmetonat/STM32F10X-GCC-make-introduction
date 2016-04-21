# include <stm32f10x.h>
# include <stm32f10x_rcc.h>
# include <stm32f10x_gpio.h>
/* Also add: OBJS += stm32f10x_gpio.o stm32f10x_rcc.o
   in the Makefile to add the libraries. */

#define TRUE 1
#define FALSE 0

//Timer ISR sets this flag to communicate with the main program.
static __IO uint8_t TimerEventFlag;   



int main(void)
{
  //Holds the structure for the GPIO pin initialization:
  GPIO_InitTypeDef GPIO_InitStructure;  

  int MS_count =0;    //Counts the number of timer ticks (ms) so far.

  const int LED_ON_TIME = 200;        //LED on for 200ms
  const int LED_FREQUENCY = 1000;     //LED blink rate 1s (1000ms)
  
  // Enable Peripheral Clocks of the devices that will be used.
  RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE ); 

  // Configure GPIO pin that LED is connected:
  GPIO_StructInit (&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Configure SysTick Timer
  /*System timer tick is used to measure time. 
    The Cortex-M3 core used in the STM32 processors has a dedicated timer 
    for this function. Its frequency is set as a fraction of the constant
    SystemCoreClock (defined in file system_stm32f10x.c in the 
    STM32F10x Standard Peripheral Library directory.) 
    We configure it for 1 msec interrupts*/
  if (SysTick_Config(SystemCoreClock/1000))
    while (1); //If it does not work, stop here for debugging.

  while (1) {
    
    if (TimerEventFlag==TRUE){
      ++MS_count;
      TimerEventFlag=FALSE;
    }

    //Turn LED on or off depending on MS_count value.
    if(MS_count<LED_ON_TIME)
      GPIO_WriteBit (GPIOA, GPIO_Pin_5, Bit_SET);
    else if(MS_count >LED_ON_TIME && MS_count<LED_FREQUENCY)
      GPIO_WriteBit (GPIOA, GPIO_Pin_5, Bit_RESET);
    else if(MS_count >=LED_FREQUENCY) //Manage MS_count value.
      MS_count=0;  
  }//End while(1)

} //END main()


// Systic interrupt handler
//Every 1 msec, the timer triggers a call to the SysTick_Handler. 
void SysTick_Handler (void){
   TimerEventFlag = TRUE;
}


#ifdef USE_FULL_ASSERT
  void assert_failed ( uint8_t* file, uint32_t line)
  {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
  }
#endif

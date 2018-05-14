#include <stm32f4xx.h>
#include <stm32f4xx_hal_rcc.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_tim.h>

int main(void)
{
	GPIO_InitTypeDef gpio_init_struct;
	TIM_HandleTypeDef timer_handle;
	TIM_Base_InitTypeDef timer_init_struct;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_TIM9_CLK_ENABLE();

	gpio_init_struct.Pin = GPIO_PIN_13;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Pull = GPIO_NOPULL;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_init_struct.Alternate = GPIO_AF0_RTC_50Hz;
	HAL_GPIO_Init(GPIOG,&gpio_init_struct);
	
	gpio_init_struct.Pin = GPIO_PIN_0;
	gpio_init_struct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA,&gpio_init_struct);
	
	timer_init_struct.Prescaler = 0;
	timer_init_struct.CounterMode = TIM_COUNTERMODE_UP;
	timer_init_struct.Period = 16000;
	timer_init_struct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	timer_init_struct.RepetitionCounter = 0;

	
	timer_handle.Instance = TIM9;
	timer_handle.Init = timer_init_struct;
	
	HAL_TIM_Base_MspInit(&timer_handle);
	
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_SET)
		{
			HAL_GPIO_WritePin(GPIOG,GPIO_PIN_13,GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG,GPIO_PIN_13,GPIO_PIN_RESET);
		}
	}
}

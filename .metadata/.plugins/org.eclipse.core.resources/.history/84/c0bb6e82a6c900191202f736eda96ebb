
#include "stm32f10x.h"

u32 systick;

//系统滴答初始化
void SysTick_Init(void)
{
	SysTick->LOAD = (uint32_t)(SystemCoreClock/1000000-1UL);	//72M时钟,一次1us
	SysTick->VAL = 0UL;
	SysTick-> CTRL = SysTick_CTRL_ENABLE_Msk  | //使能
					 SysTick_CTRL_TICKINT_Msk | //触发异常
					 SysTick_CTRL_CLKSOURCE_Msk;	//时钟源选择
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭滴答定时器
}

void delay_us(u32 time)
{
	(systick) = time;

	SysTick->VAL = 0;
	SysTick-> CTRL |= SysTick_CTRL_ENABLE_Msk;
	while((systick));
	SysTick-> CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(u32 time)
{
	(systick) = time * 1000;

	SysTick->VAL = 0;
	SysTick-> CTRL |= SysTick_CTRL_ENABLE_Msk;
	while((systick));
	SysTick-> CTRL &= ~SysTick_CTRL_ENABLE_Msk;

}

//滴答中断
void SysTick_Handler(void)
{
	while(systick)
		(systick)--;
}

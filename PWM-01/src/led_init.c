
#include "stm32f10x.h"

#define LED PAout(8) //输出,使用的是位带操作来实现操作某个 IO 口的 1 个位

void led_initi(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PA端口

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PA.8端口设置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口的速度为50MHZ

    GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化PA
//    GPIO_SetBits(GPIOA,GPIO_Pin_8);//PA.8输出高
}

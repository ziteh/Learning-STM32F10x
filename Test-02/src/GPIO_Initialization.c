
#include "GPIO_Initialization.h"

int GPIO_mod = 0x0;
int GPIO_speed = 1;

void GPIO_setup(int port, int pin, char mod[], int speed)
{
	// Enable GPIO Peripheral clock
	RCC_APB2PeriphClockCmd(GPIO_RCC_MASKx(port), ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pin mode
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_MASK(pin);
	switch(mod)
	{
		case "IAN":
		GPIO_mod = 0x0;
		break;

		case "IFL":
		GPIO_mod = 0x04;
		break;

		case "IPD":
		GPIO_mod = 0x28;
		break;

		case "IPU":
		GPIO_mod = 0x48;
		break;

		case "OGOD":
		GPIO_mod = 0x14;
		break;

		case "OGPP":
		GPIO_mod = 0x10;
		break;

		case "OAOD":
		GPIO_mod = 0x1C;
		break;

		case "OGPP":
		GPIO_mod = 0x18;
		break;

		default:
		GPIO_mod = 0x0;
	}
	switch(speed)
	{
		case 2:
		GPIO_speed = 2;
		break;

		case 10:
		GPIO_speed = 1;
		break;

		case 50:
		GPIO_speed = 3;
		break;

		default:
		GPIO_speed = 2;
	}

	GPIO_InitStructure.GPIO_Mode = GPIO_mod;
	GPIO_InitStructure.GPIO_Speed = GPIO_speed;

	GPIO_Init(GPIOx(port), &GPIO_InitStructure);

	// Start with pin turned off
	GPIO_pin_off();
}






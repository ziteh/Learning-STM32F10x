/**
 ******************************************************************************
 * @file    GPIO_Functions.cpp
 * @author  ZiTe
 * @version V1.0.0
 * @date    04-July-2020
 * @brief   GPIO functions program
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

#include "GPIO_Functions.hpp"

/**
 * @brief Config a pin mode and speed.
 * @param PortPin:  select a pin to set.
 * @param Mode: Pin mode.
 * @param Speed: Pin speed.
 * @retval  None
 */
void GPIO_SetMode(GPIO_PortPinTypeDef PortPin,
                  GPIOMode_TypeDef Mode,
                  GPIOSpeed_TypeDef Speed)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Mode = Mode;
  GPIO_InitStructure.GPIO_Speed = Speed;
  GPIO_InitStructure.GPIO_Pin = GPIO_GetPin(PortPin);
  GPIO_Init(GPIO_GetPort(PortPin), &GPIO_InitStructure);
}

void GPIO_SetMode(GPIO_PortPinTypeDef PortPin,
                  GPIOMode_TypeDef Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // Input pin no need to set Speed.
  GPIO_InitStructure.GPIO_Mode = Mode;
  GPIO_InitStructure.GPIO_Pin = GPIO_GetPin(PortPin);
  GPIO_Init(GPIO_GetPort(PortPin), &GPIO_InitStructure);
}

/**
 * @brief Set a pin to High(1).
 * @param PortPin:  select a pin to set.
 * @retval  None
 */
void GPIO_SetHigh(GPIO_PortPinTypeDef PortPin)
{
  GPIO_GetPort(PortPin)->BSRR |= GPIO_GetPin(PortPin);
}

/**
 * @brief Set a pin to Low(0).
 * @param PortPin:  select a pin to set.
 * @retval  None
 */
void GPIO_SetLow(GPIO_PortPinTypeDef PortPin)
{
  GPIO_GetPort(PortPin)->BRR |= GPIO_GetPin(PortPin);
}

/**
 * @brief Toggle a pin from High(1) to Low(0) or from Low(0) to High(1).
 * @param PortPin:  select a pin to set.
 * @retval  None
 */
void GPIO_SetToggle(GPIO_PortPinTypeDef PortPin)
{
  GPIO_GetPort(PortPin)->ODR ^= GPIO_GetPin(PortPin);
}

/**
 * @brief Set a pin to High(1) or Low(0).
 * @param PortPin:  select a pin to set.
 * @param Value:  select High(1) or Low(0) to set.
 *                This parameter should be HIGH or LOW
 * @retval  None
 */
void GPIO_SetValue(GPIO_PortPinTypeDef PortPin, GPIO_ValueTypeDef Value)
{
  if (Value == HIGH)
    GPIO_SetHigh(PortPin);
  else if (Value == LOW)
    GPIO_SetLow(PortPin);
}

/**
 * @brief Read a input-pin value.
 * @param PortPin:  select a pin.
 * @retval  The input-pin value
 */
GPIO_ValueTypeDef GPIO_GetInputValue(GPIO_PortPinTypeDef PortPin)
{
  GPIO_ValueTypeDef PinInputValue;

  if ((GPIO_GetPort(PortPin)->IDR & GPIO_GetPin(PortPin)) != (uint32_t)Bit_RESET)
  {
    PinInputValue = HIGH;
  }
  else
  {
    PinInputValue = LOW;
  }
  return PinInputValue;
}

/**
 * @brief Read a output-pin value.
 * @param PortPin:  select a pin
 * @retval  The output-pin value
 */
GPIO_ValueTypeDef GPIO_GetOutputValue(GPIO_PortPinTypeDef PortPin)
{
  GPIO_ValueTypeDef PinOutputValue;

  if ((GPIO_GetPort(PortPin)->ODR & GPIO_GetPin(PortPin)) != (uint32_t)Bit_RESET)
  {
    PinOutputValue = HIGH;
  }
  else
  {
    PinOutputValue = LOW;
  }
  return PinOutputValue;
}

/**
 * @brief Get the port.
 * @param PortPin:  select a pin.
 * @retval  The port.
 */
GPIO_TypeDef *GPIO_GetPort(GPIO_PortPinTypeDef PortPin)
{
  if ((PortPin >= PA0) && (PortPin <= PA15)) // Port-A:  0~15
    return GPIOA;
  else if ((PortPin >= PB0) && (PortPin <= PB15)) // Port-B: 16~31
    return GPIOB;
  else if ((PortPin >= PC0) && (PortPin <= PC15)) // Port-C: 32~47
    return GPIOC;
  else if ((PortPin >= PD0) && (PortPin <= PD15)) // Port-D: 48~63
    return GPIOD;
  else if ((PortPin >= PE0) && (PortPin <= PE15)) // Port-E: 64~79
    return GPIOE;
}

/**
 * @brief Get the pin.
 * @param PortPin:  select a pin.
 * @retval  The pin.
 */
uint16_t GPIO_GetPin(GPIO_PortPinTypeDef PortPin)
{
  uint8_t Offset = 0;

  if ((PortPin >= PA0) && (PortPin <= PA15)) // Port-A:  0~15
    Offset = PA0;
  else if ((PortPin >= PB0) && (PortPin <= PB15)) // Port-B: 16~31
    Offset = PB0;
  else if ((PortPin >= PC0) && (PortPin <= PC15)) // Port-C: 32~47
    Offset = PC0;
  else if ((PortPin >= PD0) && (PortPin <= PD15)) // Port-D: 48~63
    Offset = PD0;
  else if ((PortPin >= PE0) && (PortPin <= PE15)) // Port-E: 64~79
    Offset = PE0;

  return ((uint16_t)(0x0001 << (PortPin - Offset)));
}

/* class GPIO */
GPIO::GPIO(void)
{
  this->setDefault();
}

GPIO::GPIO(GPIO_PortPinTypeDef NewPortPin)
{
  this->setDefault();
  this->setPortPin(NewPortPin);
}

void GPIO::setPortPin(GPIO_PortPinTypeDef NewPortPin)
{
  PortPin = NewPortPin;
  GPIOPortPinSetted = true;

  if (this->isSetup())
  {
    this->setInit();
  }
}

void GPIO::setMode(GPIOMode_TypeDef NewGPIOMode)
{
  GPIOMode = NewGPIOMode;
  GPIOModeSetted = true;

  // Input pin no need to set Speed.
  if ((NewGPIOMode == GPIO_Mode_AIN) ||
      (NewGPIOMode == GPIO_Mode_IN_FLOATING) ||
      (NewGPIOMode == GPIO_Mode_IPD) ||
      (NewGPIOMode == GPIO_Mode_IPU))
  {
    GPIOSpeedSetted = true;
  }

  if (this->isSetup())
  {
    this->setInit();
  }
}

void GPIO::setSpeed(GPIOSpeed_TypeDef NewGPIOSpeed)
{
  GPIOSpeed = NewGPIOSpeed;
  GPIOSpeedSetted = true;

  if (this->isSetup())
  {
    this->setInit();
  }
}

void GPIO::setValue(GPIO_ValueTypeDef NewValue)
{
  if (NewValue == HIGH)
    (this->getPort())->BSRR |= (this->getPin()); // Set value HIGH
  else if (NewValue == LOW)
    (this->getPort())->BRR |= (this->getPin()); // Set value LOW
}

void GPIO::setValueToggle(void)
{
  (this->getPort())->ODR ^= (this->getPin());
}

GPIO_ValueTypeDef GPIO::getValue()
{
  uint8_t GPIOValue;

  if ((GPIOMode == GPIO_Mode_AIN) ||
      (GPIOMode == GPIO_Mode_IN_FLOATING) ||
      (GPIOMode == GPIO_Mode_IPD) ||
      (GPIOMode == GPIO_Mode_IPU))
  {
    // This GPIO is input.
    GPIOValue = GPIO_ReadInputDataBit(this->getPort(), this->getPin());
  }
  else if ((GPIOMode == GPIO_Mode_Out_OD) ||
           (GPIOMode == GPIO_Mode_Out_PP) ||
           (GPIOMode == GPIO_Mode_AF_OD) ||
           (GPIOMode == GPIO_Mode_AF_PP))
  {
    // This GPIO is output.
    GPIOValue = GPIO_ReadOutputDataBit(this->getPort(), this->getPin());
  }

  // Convert data type from uint8_t to GPIOType::Value
  if (GPIOValue == 0)
  {
    return ((GPIO_ValueTypeDef)LOW);
  }
  else
  {
    return ((GPIO_ValueTypeDef)HIGH);
  }
}

void GPIO::setInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIOMode;
  GPIO_InitStructure.GPIO_Speed = GPIOSpeed;
  GPIO_InitStructure.GPIO_Pin = this->getPin();
  GPIO_Init(this->getPort(), &GPIO_InitStructure);

  GPIOPortPinSetted = false;
  GPIOModeSetted = false;
  GPIOSpeedSetted = false;
}

void GPIO::setDefault(void)
{
  GPIOPortPinSetted = false;
  GPIOModeSetted = false;
  GPIOSpeedSetted = false;

  GPIOMode = GPIO_Mode_IN_FLOATING;
  GPIOSpeed = GPIO_Speed_2MHz;
}

GPIO_TypeDef *GPIO::getPort(void)
{
  if (PortPin <= PA15) // Port-A:  0~15
    return GPIOA;
  else if (PortPin <= PB15) // Port-B: 16~31
    return GPIOB;
  else if (PortPin <= PC15) // Port-C: 32~47
    return GPIOC;
  else if (PortPin <= PD15) // Port-D: 48~63
    return GPIOD;
  else if (PortPin <= PE15) // Port-E: 64~79
    return GPIOE;
}

uint16_t GPIO::getPin(void)
{
  uint8_t Offset = 0;

  if (PortPin <= PA15) // Port-A:  0~15
    Offset = PA0;
  else if (PortPin <= PB15) // Port-B: 16~31
    Offset = PB0;
  else if (PortPin <= PC15) // Port-C: 32~47
    Offset = PC0;
  else if (PortPin <= PD15) // Port-D: 48~63
    Offset = PD0;
  else if (PortPin <= PE15) // Port-E: 64~79
    Offset = PE0;

  return ((uint16_t)(0x0001 << (PortPin - Offset)));
}

bool GPIO::isSetup(void)
{
  if ((GPIOPortPinSetted && GPIOModeSetted && GPIOSpeedSetted) == true)
    return true;
  else
    return false;
}

/********************************END OF FILE***********************************/

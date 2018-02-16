#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stdint.h>

struct InputList
{
	uint8_t Id;
	GPIO_TypeDef* Port;
	uint16_t GPIO_Pin;
};

class Configuration
{
public:
	static uint16_t GetInputAmount()
	{
		return inputAmount;
	}

	static InputList* GetInputList()
	{
		return inputs;
	}

	static uint8_t GetId()
	{
		return ID;
	}

private:
	static const uint8_t ID = 3;
	static const uint16_t inputAmount = 4;
	static InputList inputs[inputAmount];
};

#endif // CONFIGURATION_HPP

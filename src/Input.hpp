#ifndef INPUT_H
#define INPUT_H
#include <stdint.h>
#include "stm32f10x.h"
#include "Timer.hpp"
#include "C_Interface.hpp"

const uint16_t DEBOUNCE_TIME = 30;

class Input
{
public:
	Input(uint8_t bitPosition, GPIO_TypeDef* port, uint16_t pin);
	virtual ~Input() = default;
	bool GetState();
	void SetState(bool state);
	void Process();
	uint16_t Serialize();

private:
	uint8_t bitPosition;
	GPIO_TypeDef* port;
	uint16_t pin;
	Utilites::Timer timer;
	bool state;
	bool prevState;
};

#endif // INPUT_H

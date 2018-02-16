#include <Input.hpp>
#include <stdio.h>
#define DEV

Input::Input(uint8_t bitPosition, GPIO_TypeDef* port, uint16_t pin) : bitPosition(bitPosition),
															 	 	  port(port),
																	  pin(pin),
																	  timer(DEBOUNCE_TIME, GetClockTick),
																	  state(false),
																	  prevState(false)
{
	// Init input
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(port, &GPIO_InitStruct);
}

bool Input::GetState()
{
	return state;
}

uint16_t Input::Serialize()
{
	if(state == true)
	{
		return 1 << bitPosition;
	}
	else
	{
		return 0;
	}
}

void Input::Process()
{
	bool currentState = static_cast<bool>(port->IDR & pin);

	if(timer.GetState() != Utilites::T_STATE::STOPPED &&
			currentState == state)
	{
		timer.Stop();
	}
	else if( currentState != prevState && currentState != state)
	{
		timer.Start();
	}
	else if(timer.GetState() == Utilites::T_STATE::EXPIRED)
	{
		printf("Input %d changed %d\r\n", pin, currentState);
		state = currentState;
		timer.Stop();
	}
	prevState = currentState;
}

void Input::SetState(bool state)
{
	this->state = state;
}

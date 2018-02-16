#include <InputCard.h>
#include <algorithm>
#include "Configuration.hpp"

InputCard::InputCard() : cardState(0),
						 prevCardState(0),
						 stateChanged(false)
{
	for(size_t i = 0; i < Configuration::GetInputAmount(); i++)
	{
		inputsVector.push_back(new Input(Configuration::GetInputList()[i].Id,
										 Configuration::GetInputList()[i].Port,
										 Configuration::GetInputList()[i].GPIO_Pin));

	}
}

void InputCard::Process()
{
	cardState = 0;
	std::for_each(inputsVector.begin(), inputsVector.end(), [this](Input* in)
	{
		in->Process();
		cardState |= in->Serialize();
	});

	if(prevCardState != cardState)
	{
		stateChanged = true;
		prevCardState = cardState;
	}
}

uint16_t InputCard::GetState()
{
	stateChanged = false;
	return cardState;
}

bool InputCard::StateChanged() const
{
	return stateChanged;
}

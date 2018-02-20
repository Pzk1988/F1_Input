#include <ICommunication.hpp>
#include <stddef.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "Serial.hpp"
#include "Can.hpp"
#include <string.h>
#include <vector>
#include "InputCard.h"
#include "Configuration.hpp"
#include "Timer.hpp"


static void ProcessCan(InputCard& inputCard);

Driver::ISerial* serial;
Driver::ICommunication* commDriver;
volatile uint8_t receivedSem = 0;
volatile CanRxMsg RxMessage;
uint16_t inputState = 0;

int main(void)
{
	// System clock
	SysTick_Config(SystemCoreClock / 1000);

	// Serial driver
	serial = new Driver::Serial();
	serial->Init(115200);

	// Can driver
	commDriver = new Driver::Can(Configuration::GetId());
	commDriver->Init(Configuration::GetId());

	// InputCard
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	InputCard inputCard;

	printf("Stm32F103RB Hello World\r\n");

	while (1)
	{
		// Process input state
		inputCard.Process();

		// Send frame if any input has changed
		if(inputCard.StateChanged() == true)
		{
			uint16_t input = inputCard.GetState();
			commDriver->SendDataFrame(0x03, (uint8_t*)&input, 2);
		}

		// Process CAN transmission
		ProcessCan(inputCard);
	}
}

void ProcessCan(InputCard& inputCard)
{
	if(receivedSem == 1)
	{
		receivedSem = 0;
		if(RxMessage.RTR == CAN_RTR_Remote)
		{
			uint16_t input = inputCard.GetState();
			commDriver->SendDataFrame(0x01, (uint8_t*)&input, 2);
			printf("RTR id 0x%x from 0x%x, input 0x%x\r\n", (RxMessage.StdId & 0x1f), (RxMessage.StdId >> 5), inputCard.GetState());
		}
		else
		{
			printf("Can 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\r\n", RxMessage.StdId, ((RxMessage.Data[0]) | RxMessage.Data[1] << 8),
																			((RxMessage.Data[2]) | RxMessage.Data[3] << 8),
																			((RxMessage.Data[4]) | RxMessage.Data[5] << 8),
																			((RxMessage.Data[6]) | RxMessage.Data[7] << 8));
		}
	}
}

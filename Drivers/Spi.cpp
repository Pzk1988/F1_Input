// Project includes
#include <Spi.hpp>
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x.h"

namespace Driver
{

void Spi::Init()
{
	// Enable clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// Gpio configuration
	GPIO_InitTypeDef gpio_InitTypeDef;

	// Outputs MISO
	gpio_InitTypeDef.GPIO_Pin = GPIO_Pin_6;
	gpio_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_InitTypeDef.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &gpio_InitTypeDef);

	// Inputs MOSI, CLK, NCC
	gpio_InitTypeDef.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	gpio_InitTypeDef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_InitTypeDef.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &gpio_InitTypeDef);

	// Spi configuration
	SPI1->CR2 |= SPI_CR2_SSOE;
	SPI_InitTypeDef spi_InitTypeDef;
	spi_InitTypeDef.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi_InitTypeDef.SPI_Mode = SPI_Mode_Slave;
	spi_InitTypeDef.SPI_DataSize = SPI_DataSize_8b;
	spi_InitTypeDef.SPI_CPOL = SPI_CPOL_Low;
	spi_InitTypeDef.SPI_CPHA = SPI_CPHA_1Edge;
	spi_InitTypeDef.SPI_NSS = SPI_NSS_Hard;
	spi_InitTypeDef.SPI_FirstBit = SPI_FirstBit_MSB;
	spi_InitTypeDef.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_Init(SPI1, &spi_InitTypeDef);
	//SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

	SPI_Cmd(SPI1, ENABLE);

//	// Enable Rx interrupt
//	NVIC_InitTypeDef  NVIC_InitStruct;
//
//	// Configure the SPI interrupt priority
//	NVIC_InitStruct.NVIC_IRQChannel = SPI1_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStruct);
}

uint8_t Spi::Write(uint8_t data)
{
	SPI_I2S_SendData(SPI1, data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	return SPI_I2S_ReceiveData(SPI1);
}

} /* namespace Driver */

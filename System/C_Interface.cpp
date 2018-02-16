#include "C_Interface.hpp"

volatile uint32_t time = 0;

extern "C" void SerialWraperPut(char c)
{
	serial->Put(c);
}

uint32_t GetClockTick()
{
	return time;
}


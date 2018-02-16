#ifndef C_INTERFACE_HPP
#define C_INTERFACE_HPP
#include "ISerial.hpp"
#include <stdint.h>

extern "C" void SerialWraperPut(char c);
extern uint32_t GetClockTick();
extern Driver::ISerial* serial;
extern volatile uint32_t time;

#endif // C_INTERFACE_HPP

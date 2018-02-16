#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#include "Serial.hpp"
#include <stdio.h>
extern Driver::ISerial* serial;

namespace Utilites
{
typedef uint32_t (*CurrentTime)();

enum class T_STATE
{
	STOPPED,
	COUNTING,
	EXPIRED
};

class Timer
{

public:
	Timer(uint32_t timeout, CurrentTime currentTime) : timeout(timeout), currentTime(currentTime)
	{
		state = T_STATE::STOPPED;
	}

	void Start()
	{
		startTime = currentTime();
		state = T_STATE::COUNTING;
	}

	void Stop()
	{
		state = T_STATE::STOPPED;
	}

	T_STATE GetState()
	{
		if(state == T_STATE::COUNTING)
		{
			if(currentTime() - startTime > timeout)
			{
				state = T_STATE::EXPIRED;
			}
		}
		return state;
	}

	virtual ~Timer() {}

private:
	const uint32_t timeout;
	uint32_t startTime;
	T_STATE state;
	CurrentTime currentTime;
};

} // namespace Utilites

#endif // TIMER_H

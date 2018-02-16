#ifndef INPUTCARD_H
#define INPUTCARD_H
#include <Input.hpp>
#include <vector>

class InputCard
{
public:
	InputCard();
	virtual ~InputCard() = default;
	void Process();
	uint16_t GetState();
	bool StateChanged() const;

private:
	std::vector<Input*> inputsVector;
	uint16_t cardState;
	uint16_t prevCardState;
	bool stateChanged;
};

#endif // INPUTCARD_H

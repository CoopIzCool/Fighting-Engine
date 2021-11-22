#pragma once
#include "Inputs.h"
class InputRegister
{
public:
	InputRegister();
	~InputRegister();
	void SetInput(inputs ip);
	inputs GetInput();
	bool Update(float dt);
private:
	float activeFrames = 0;
	inputs input;
};


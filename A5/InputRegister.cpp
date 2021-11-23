#include "InputRegister.h"

InputRegister::InputRegister()
{
	activeFrames = 0;
}

InputRegister::~InputRegister()
{
}

void InputRegister::SetInput(inputs ip)
{
	input = ip;
}

inputs InputRegister::GetInput()
{
	return input;
}

bool InputRegister::Update(float dt)
{
	activeFrames += dt * 60;
	if (activeFrames > 20.0f)
	{
		activeFrames = 0;
		return false;
	}
	else 
	{
		return true;
	}

}

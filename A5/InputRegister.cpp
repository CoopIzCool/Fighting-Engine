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

inputs InputRegister::GetInput(inputs ip)
{
	return inputs();
}

bool InputRegister::Update(float dt)
{
	activeFrames += dt;
	if (activeFrames > 10.0f)
	{
		activeFrames = 0;
		return false;
	}
	else 
	{
		return true;
	}

}

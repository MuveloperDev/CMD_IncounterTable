#pragma once
#include "Enum.h"
//#include <string>
class InputBase
{
public:
	InputBase();
	~InputBase();

protected:
protected:
	UIHorizontalInput UIHorizontalInputUpdate();
	UIHorizontalInput GetCurrentHInput();
private:
	UIHorizontalInput _CURRENT_H_INPUT;
	bool _isKeyDown;
};


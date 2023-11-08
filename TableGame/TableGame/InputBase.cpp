#include "InputBase.h"
#include "GameManager.h"
#include "Utility.h"

InputBase::InputBase() :
	_CURRENT_H_INPUT(UIHorizontalInput::None), _isKeyDown(false)
{
}

InputBase::~InputBase()
{
}

UIHorizontalInput InputBase::UIHorizontalInputUpdate()
{
	SHORT lefttState = GetAsyncKeyState(VK_LEFT);
	SHORT rightState = GetAsyncKeyState(VK_RIGHT);

	bool isLeft = (lefttState & 0x8000) != 0;
	bool isRight = (rightState & 0x8000) != 0;

	if (isLeft || isRight)
	{
		if (_isKeyDown == false)
		{
			if (isLeft)
			{
				_CURRENT_H_INPUT = UIHorizontalInput::Left;
			}
			if (isRight)
			{
				_CURRENT_H_INPUT = UIHorizontalInput::Right;
			}
			_isKeyDown = true;
			return _CURRENT_H_INPUT;
		}
		_CURRENT_H_INPUT = UIHorizontalInput::None;
		return _CURRENT_H_INPUT;
	}
	else
	{
		_isKeyDown = false;
		_CURRENT_H_INPUT = UIHorizontalInput::None;
		return _CURRENT_H_INPUT;
	}
}

UIHorizontalInput InputBase::GetCurrentHInput()
{
	return _CURRENT_H_INPUT;
}

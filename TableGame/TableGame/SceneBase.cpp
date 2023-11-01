#include "SceneBase.h"
#include "GameManager.h"
#include <cstdlib> // for system

SceneBase::SceneBase(std::string InAsciiTitle) :
	_isKeyDown(false), _pointer("¢¹ "),
	_hStdout(GetStdHandle(STD_OUTPUT_HANDLE)),
	_asciiTitle(InAsciiTitle),
	_CURRENTINPUT(PlayerInputSelectMode::None)
{
	_CURRENT_BTN_IDX = 0;
}

SceneBase::~SceneBase()
{
}

void SceneBase::Run()
{
}

void SceneBase::Initialize()
{
	_buttons.clear();
	_CURRENTINPUT = PlayerInputSelectMode::None;
	_CURRENT_BTN_IDX = 0;
}

void SceneBase::Update()
{
}

void SceneBase::Render()
{
}

void SceneBase::UpdateCursor()
{
	SHORT uptState = GetAsyncKeyState(VK_UP);
	SHORT downState = GetAsyncKeyState(VK_DOWN);
	SHORT enterState = GetAsyncKeyState(VK_RETURN);

	bool isUp = (uptState & 0x8000) != 0;
	bool isDown = (downState & 0x8000) != 0;
	bool isEnter = (enterState & 0x8000) != 0;

	if (isUp || isDown || isEnter)
	{
		if (_isKeyDown == false)
		{
			if (isUp)
			{
				_CURRENTINPUT = PlayerInputSelectMode::Up;
				if (_CURRENT_BTN_IDX <= 0)
					return;
				_CURRENT_BTN_IDX--;
			}
			if (isDown)
			{
				_CURRENTINPUT = PlayerInputSelectMode::Down;
				if (_CURRENT_BTN_IDX >= _buttons.size()-1)
					return;
				_CURRENT_BTN_IDX++;
			}
			if (isEnter)
			{
				_CURRENTINPUT = PlayerInputSelectMode::Enter;
			}
		}
		_isKeyDown = true;
	}
	else
	{
		_isKeyDown = false;
	}
}

void SceneBase::Music()
{
}

bool SceneBase::SelectProcess()
{
	return false;
}

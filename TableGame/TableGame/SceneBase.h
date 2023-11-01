#pragma once
#include "Utility.h"
#include "Enum.h"
#include <stdint.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

class SceneBase
{
public:
	enum Buttons
	{
		None = -1,
		Start = 0,
		Restart,
		Exit,
	};
	SceneBase(std::string InAsciiTitle);
	virtual ~SceneBase();
	virtual void Run();
protected:
	bool _isKeyDown;
	__int32 _CURRENT_BTN_IDX;
	HANDLE _hStdout;
	std::string _pointer;
	std::string _asciiTitle;
	PlayerInputSelectMode _CURRENTINPUT;
	std::vector<Buttons> _buttons;
protected:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Music();
	virtual bool SelectProcess();
	void UpdateCursor();
};

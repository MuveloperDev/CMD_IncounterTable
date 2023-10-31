#pragma once

#include "Utility.h"
#include <stdint.h>
#include <iostream>
#include <string>
#include <windows.h>
class TitleScene
{
public:
	enum Buttons
	{
		Start = 0,
		Exit
	};
	TitleScene();
	~TitleScene();
	void Run();
private:
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srWindowRect;
	COORD coordScreen;
	void Update();
	void Render();
	bool isKeyDown;
	void UpdateCursor();
	bool CheckEnter();
	void Music();
	std::string _pointer;
	std::string _startBtnText;
	std::string _exitBtnText;
	std::string asciiTitle;
	Buttons _currentTargetBtn;
};


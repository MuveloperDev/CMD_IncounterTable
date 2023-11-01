#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "Enum.h"
#include <sstream>
#include <string>
class Utility
{
public:
	// ���� �����ڿ� ���� ���� �����ڸ� ��������� ����������
	// �̱��� �ν��Ͻ��� �� �ٸ� ���� �����ϴ� ���� ���� ���� delete Ű���带 ���.
	Utility(const Utility&) = delete;
	Utility& operator=(const Utility&) = delete;

	static Utility& GetInstance();

	void SetCursorPosition(int x, int y);
	void SetCursorInvisible();
	void ChangeTextColor(TextColors InColor, bool isForeGround);
	void ResetTextColor();
	void ClearCmd();
	void PrintTopLine();
	void PrintBottomLine();
	void PrintVerticalLine(__int32 InX);
	void PrintVerticalLine(__int32 InX, __int32 InStartY, __int32 InEndY);
	void PrintHirizontalLine(__int32 InY);
	void PrintShape(__int32 InX, __int32 InY, std::string InShape);
	void PrintComment(bool& InFlag, __int32 InStartX, __int32 InStartY, std::string InComment);
private:
	Utility();
	HANDLE _hConsole;
	TextColors _CURRENT_TEXT_COLOR;
};


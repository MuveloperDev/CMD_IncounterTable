#include "Utility.h"

void Utility::PrintVerticalLine(__int32 InX)
{
	for (__int32 i = 1; i < 28; i++)
	{
		Utility::GetInstance().SetCursorPosition(InX, i);
		std::cout << "��" << std::endl;
	}
}

void Utility::PrintHirizontalLine(__int32 InY)
{
	Utility::GetInstance().SetCursorPosition(0, InY);
	std::cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�" << std::endl;
}

Utility::Utility() {}

Utility& Utility::GetInstance()
{
	static Utility instance;
	return instance;
}

void Utility::SetCursorPosition(int x, int y)
{
	COORD cur;
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void Utility::SetCursorInvisible()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Utility::ClearCmd()
{
	system("cls");
}

void Utility::PrintTopLine()
{
	Utility::GetInstance().SetCursorPosition(0, 0);
	std::cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�" << std::endl;
}

void Utility::PrintBottomLine()
{
	Utility::GetInstance().SetCursorPosition(0, 28);
	std::cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�" << std::endl;
}

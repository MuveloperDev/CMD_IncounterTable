#include "Utility.h"

void Utility::PrintVerticalLine(__int32 InX)
{
	for (__int32 i = 1; i < 28; i++)
	{
		Utility::GetInstance().SetCursorPosition(InX, i);
		std::cout << "��" << std::endl;
	}
}

void Utility::PrintVerticalLine(__int32 InX, __int32 InStartY, __int32 InEndY)
{
	__int32 limit = InEndY - InStartY;
	for (__int32 i = 0; i <= limit; i++)
	{
		SetCursorPosition(InX, InStartY + i);
		std::cout << "��" << std::endl;
	}
}

void Utility::PrintHorizontalLine(__int32 InStartX, __int32 InEndX, __int32 InY)
{
	__int32 limit = InEndX - InStartX;
	SetCursorPosition(InStartX, InY);
	for (__int32 i = 0; i <= limit / 2; i++)
	{
		std::cout << "��";
	}
}

void Utility::PrintHirizontalLine(__int32 InY)
{
	Utility::GetInstance().SetCursorPosition(0, InY);
	std::cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�" << std::endl;
}

void Utility::PrintShape(__int32 InX, __int32 InY, std::string InShape)
{
	std::istringstream stream(InShape);
	__int32 i = 0;
	for (std::string line; std::getline(stream, line); ) {
		SetCursorPosition(InX, InY+i);
		std::cout << line << std::endl;
		i++;
	}
}

void Utility::PrintComment(bool& InFlag, __int32 InStartX, __int32 InStartY, std::string InComment)
{
	if (true == InFlag)
	{
		Utility::GetInstance().SetCursorPosition(InStartX, InStartY);
		for (__int32 i = 0; i < InComment.size()+2; i++)
			std::cout << "=";
		Utility::GetInstance().SetCursorPosition(InStartX+1, InStartY+1);
		std::cout << "\"" << InComment << "\"" << std::endl;
		Utility::GetInstance().SetCursorPosition(InStartX, InStartY+2);
		for (__int32 i = 0; i < InComment.size() + 2; i++)
			std::cout << "=";
	}
	InFlag = false;
}

Utility::Utility():
	_hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) 
{}

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

void Utility::ChangeTextColor(TextColors InColor, bool isForeGround)
{
	switch (InColor)
	{
	case TextColors::None:
		break;
	case TextColors::Red:
		if (true == isForeGround)
		{
			SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
			break;
		}
		SetConsoleTextAttribute(_hConsole, BACKGROUND_RED);
		break;
	case TextColors::Green:
		if (true == isForeGround)
		{
			SetConsoleTextAttribute(_hConsole, FOREGROUND_GREEN);
			break;
		}
		SetConsoleTextAttribute(_hConsole, BACKGROUND_GREEN);
		break;
	case TextColors::Blue:
		if (true == isForeGround)
		{
			SetConsoleTextAttribute(_hConsole, FOREGROUND_BLUE);
			break;
		}
		SetConsoleTextAttribute(_hConsole, BACKGROUND_BLUE);
		break;
	case TextColors::Intensity:
		if (true == isForeGround)
		{
			SetConsoleTextAttribute(_hConsole, FOREGROUND_INTENSITY);
			break;
		}
		SetConsoleTextAttribute(_hConsole, BACKGROUND_INTENSITY);
		break;
	default:
		break;
	}
}

void Utility::ChangeTextColor(TextColors InColor, bool isForeGround, std::function<void()> func)
{
	switch (InColor)
	{
	case TextColors::None:
		break;
	case TextColors::Red:
		if (true == isForeGround)
		{
			SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
			break;
		}
		SetConsoleTextAttribute(_hConsole, BACKGROUND_RED);
		break;
	case TextColors::Green:
		if (true == isForeGround)
		{
			SetConsoleTextAttribute(_hConsole, FOREGROUND_GREEN);
			break;
		}
		SetConsoleTextAttribute(_hConsole, BACKGROUND_GREEN);
		break;
	case TextColors::Blue:
		if (true == isForeGround)
		{
			SetConsoleTextAttribute(_hConsole, FOREGROUND_BLUE);
			break;
		}
		SetConsoleTextAttribute(_hConsole, BACKGROUND_BLUE);
		break;
	case TextColors::Intensity:
		if (true == isForeGround)
		{
			SetConsoleTextAttribute(_hConsole, FOREGROUND_INTENSITY);
			break;
		}
		SetConsoleTextAttribute(_hConsole, BACKGROUND_INTENSITY);
		break;
	default:
		break;
	}
	func();
	ResetTextColor();
}

void Utility::ResetTextColor()
{
	SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	//SetConsoleTextAttribute(_hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
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

void Utility::PrintVerticalLeftLine()
{
	Utility::GetInstance().PrintVerticalLine(0, 1, 27);
}

void Utility::PrintVerticalRightLine()
{
	Utility::GetInstance().PrintVerticalLine(118, 1, 27);
}

void Utility::PrintFrame()
{
	PrintTopLine();
	PrintBottomLine();
	PrintVerticalLeftLine();
	PrintVerticalRightLine();
}

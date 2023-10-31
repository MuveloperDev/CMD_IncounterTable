#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
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
	void ClearCmd();
	void PrintTopLine();
	void PrintBottomLine();
	void PrintVerticalLine(__int32 InX);
	void PrintHirizontalLine(__int32 InY);
private:
	Utility();

};


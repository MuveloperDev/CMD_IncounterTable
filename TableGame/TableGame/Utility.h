#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
class Utility
{
public:
	// 복사 생성자와 복사 대입 연산자를 명시적으로 삭제함으로
	// 싱글톤 인스턴스를 또 다른 곳에 복제하는 것을 막기 위해 delete 키워드를 사용.
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


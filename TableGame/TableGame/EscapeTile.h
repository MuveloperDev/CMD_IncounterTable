#pragma once

#include "GameManager.h"

class EscapeTile
{
public:
	EscapeTile(__int32 InPosX, __int32 InPosY);
	~EscapeTile();
	void Update();
	void Render();
	__int32 GetPosX();
	__int32 GetPosY();
	const wchar_t GetShape() const;
private:
	void Escape();
	const wchar_t _shape;
	__int32 _posX;
	__int32 _posY;
};


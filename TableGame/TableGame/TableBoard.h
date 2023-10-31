#pragma once

#include "TableGame.h"

class TableBoard
{
public:
	TableBoard(__int32 InTableSizeX, __int32 InTableSizeY);
	~TableBoard();

	void Awake();
	void Start();
	void Update();
	void Render();
private:
	const wchar_t _tableShape;
	const __int32 _TABLE_SIZE_X;
	const __int32 _TABLE_SIZE_Y;
};


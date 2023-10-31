#include "TableBoard.h"


//L을 붙이는 이유는 WideString임을 컴파일러에게 미리 알려주는것.
TableBoard::TableBoard( __int32 InTableSizeX, __int32 InTableSizeY) : 
	_tableShape(L'□'),
	_TABLE_SIZE_X(InTableSizeX), _TABLE_SIZE_Y(InTableSizeY)
{}

TableBoard::~TableBoard(){}

void TableBoard::Awake()
{

}

void TableBoard::Start()
{
}

void TableBoard::Update()
{
}

void TableBoard::Render()
{
	Utility::GetInstance().SetCursorPosition(40, 5);
	for (__int32 y = 0; y < _TABLE_SIZE_Y; y++)
	{
		Utility::GetInstance().SetCursorPosition(40, 5+y);
		for (__int32 x = 0; x < _TABLE_SIZE_X; x++)
		{
			if (y == GameManager::GetInstance().GetPlayer().GetPosY() && x == GameManager::GetInstance().GetPlayer().GetPosX())
			{
				GameManager::GetInstance().GetPlayer().Render();
			}
			else if (true == GameManager::GetInstance().GetMonsterMapManager().IsMonstetTile(x, y))
			{
				GameManager::GetInstance().GetMonsterMapManager().Render();
			}
			else if (true == GameManager::GetInstance().GetShopManager().IsShop(x, y))
			{
				std::wcout << GameManager::GetInstance().GetShopManager().GetShape();
			}
			else if (y == GameManager::GetInstance().GetEscapeTile().GetPosY() && x == GameManager::GetInstance().GetEscapeTile().GetPosX())
			{
				GameManager::GetInstance().GetEscapeTile().Render();
			}
			else std::wcout << _tableShape;
		}
		std::wcout << L"\n";
	}
}


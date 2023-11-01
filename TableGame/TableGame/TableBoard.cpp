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
				Utility::GetInstance().ChangeTextColor(TextColors::Green, true);
				GameManager::GetInstance().GetPlayer().Render();
				Utility::GetInstance().ResetTextColor();
			}
			else if (true == GameManager::GetInstance().GetMonsterMapManager().IsMonstetTile(x, y))
			{
				Utility::GetInstance().ChangeTextColor(TextColors::Red, false);
				GameManager::GetInstance().GetMonsterMapManager().Render();
				Utility::GetInstance().ResetTextColor();
			}
			else if (true == GameManager::GetInstance().GetShopManager().IsShop(x, y))
			{
				Utility::GetInstance().ChangeTextColor(TextColors::Green, true);
				std::wcout << GameManager::GetInstance().GetShopManager().GetShape();
				Utility::GetInstance().ResetTextColor();
			}
			else if (y == GameManager::GetInstance().GetEscapeTile().GetPosY() && x == GameManager::GetInstance().GetEscapeTile().GetPosX())
			{
				Utility::GetInstance().ChangeTextColor(TextColors::Green, true);
				GameManager::GetInstance().GetEscapeTile().Render();
				Utility::GetInstance().ResetTextColor();
			}
			else std::wcout << _tableShape;
		}
		std::wcout << L"\n";
	}
}


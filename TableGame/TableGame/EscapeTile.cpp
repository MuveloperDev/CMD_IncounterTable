#include "EscapeTile.h"

EscapeTile::EscapeTile(__int32 InPosX, __int32 InPosY) :
	_shape(L'¢Ã'),
	_posX(InPosX -1), _posY(InPosY-1)
{
	std::cout << "EscapeTile create \n";
}

EscapeTile::~EscapeTile()
{
}

void EscapeTile::Update()
{
	Escape();
}

void EscapeTile::Render()
{
	std::wcout << _shape;
}

__int32 EscapeTile::GetPosX()
{
	return _posX;
}

__int32 EscapeTile::GetPosY()
{
	return _posY;
}

const wchar_t EscapeTile::GetShape() const
{
	return _shape;
}

void EscapeTile::Escape()
{
	__int32 playerPosX = GameManager::GetInstance().GetPlayer().GetPosX();
	__int32 playerPosY = GameManager::GetInstance().GetPlayer().GetPosY();
	if (playerPosX == _posX && playerPosY == _posY)
	{
		GameManager::GetInstance().ChangeScene(Scene::Escape);
	}
}

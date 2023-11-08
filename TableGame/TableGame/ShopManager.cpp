#include "ShopManager.h"

ShopManager::ShopManager(__int32 InTableSizeX, __int32 InTableSizeY, __int32 InDifficult):
	sector1
	{
		0,
		0,
		InTableSizeX / 2 - 1,
		InTableSizeY / 2 - 1,
		MapSector::Sector1,
		InDifficult,
		0
	},
	sector2
	{
		InTableSizeX / 2,
		0,
		InTableSizeX - 1,
		InTableSizeY / 2 - 1,
		MapSector::Sector2,
		InDifficult,
		0
	},
	sector3
	{
		0,
		InTableSizeY / 2,
		InTableSizeX / 2 - 1,
		InTableSizeY - 1,
		MapSector::Sector3,
		InDifficult,
		0

	},
	sector4
	{
		InTableSizeX / 2,
		InTableSizeY / 2,
		InTableSizeX - 1,
		InTableSizeY - 1,
		MapSector::Sector4,
		InDifficult,
		0
	},
	_tableSizeX(InTableSizeX),
	_tableSizeY(InTableSizeY),
	_difficult(InDifficult),
	_shape(L'▩'),
	_currentTargetShop(nullptr)
{
}

ShopManager::~ShopManager()
{
}

void ShopManager::Awake()
{
	Initialize();
	for (const auto& [key, value] : ShopList) {
		value->Awake();
	}
}

void ShopManager::Start()
{
	for (const auto& [key, value] : ShopList) {
		value->Start();
	}
}

void ShopManager::Update()
{
	for (const auto& [key, value] : ShopList) {
		value->Update();
	}
}

void ShopManager::Render()
{
	
	for (const auto& [key, value] : ShopList) {
		value->Render();
	}
}

void ShopManager::Initialize()
{
	ShopGenerator();
}

const wchar_t ShopManager::GetShape() const
{
	return _shape;
}

bool ShopManager::IsShop(__int32 InX, __int32 InY)
{
	for (const auto& [key, value] : ShopList) {
		if (InX == value->GetPosX() && InY == value->GetPosY())
			return true;
	}
	return false;
}

void ShopManager::SetTargetShop(Shop* InShop)
{
	_currentTargetShop = InShop;
}

void ShopManager::IsPlayerOnShop()
{
	for (const auto& [key, value] : ShopList) {
		value->IsPlayerOnShop();
	}
}

Shop* ShopManager::GetTargetShop()
{
	return _currentTargetShop;
}

void ShopManager::SetPossibleGeneratePos()
{
	if (0 < _possibleCoord.size())
		_possibleCoord.clear();

	for (__int32 y = 0; y < _tableSizeY; y++)
	{
		for (__int32 x = 0; x < _tableSizeX; x++)
		{
			if (0 == y && 0 == x)
				continue;

			bool isMonsterTile = GameManager::GetInstance().GetMonsterMapManager().IsMonstetTile(x, y);
			if (true == isMonsterTile)
				continue;

			if (y == _tableSizeY - 1 && x == _tableSizeX - 1)
				continue;

			MapSector sector = SetTargetSector(x, y);
			if (_possibleCoord.find(sector) != _possibleCoord.end())
			{
				// 키가 있는 경우
				_possibleCoord[sector].push_back(TileCoordinate(x, y));
			}
			else
			{
				std::vector<TileCoordinate> coords;
				coords.push_back(TileCoordinate(x, y));
				_possibleCoord.insert({ sector,  coords });
			}
		}
	}
}

void ShopManager::ShopGenerator()
{
	SetPossibleGeneratePos();

	TileCoordinate sector1Pos = RandomCoordToSector(MapSector::Sector1);
	TileCoordinate sector2Pos = RandomCoordToSector(MapSector::Sector2);
	TileCoordinate sector3Pos = RandomCoordToSector(MapSector::Sector3);
	TileCoordinate sector4Pos = RandomCoordToSector(MapSector::Sector4);

	for (__int32 i = 0; i <= static_cast<int>(MapSector::Sector4); i++)
	{
		MapSector sector = static_cast<MapSector>(i);
		switch (sector)
		{
		case MapSector::None:
			break;
		case MapSector::Sector1:
		{
			ShopList.insert({ sector, new Shop(sector1Pos._posX, sector1Pos._posY) });
			break;
		}
		case MapSector::Sector2:
		{
			ShopList.insert({ sector, new Shop(sector2Pos._posX, sector2Pos._posY) });
			break;
		}
		case MapSector::Sector3:
		{
			ShopList.insert({ sector, new Shop(sector3Pos._posX, sector3Pos._posY) });
			break;
		}
		case MapSector::Sector4:
		{
			ShopList.insert({ sector, new Shop(sector4Pos._posX, sector4Pos._posY) });
			break;
		}
		}
		
	}
}

MapSector ShopManager::SetTargetSector(const __int32 x, const __int32 y)
{
	bool isSector1 = x >= sector1._startCoordinateX && x <= sector1._endCoordinateX &&
		y >= sector1._startCoordinateY && y <= sector1._endCoordinateY;
	bool isSector2 = x >= sector2._startCoordinateX && x <= sector2._endCoordinateX &&
		y >= sector2._startCoordinateY && y <= sector2._endCoordinateY;
	bool isSector3 = x >= sector3._startCoordinateX && x <= sector3._endCoordinateX &&
		y >= sector3._startCoordinateY && y <= sector3._endCoordinateY;
	bool isSector4 = x >= sector4._startCoordinateX && x <= sector4._endCoordinateX &&
		y >= sector4._startCoordinateY && y <= sector4._endCoordinateY;

	if (true == isSector1)
		return MapSector::Sector1;
	else if (true == isSector2)
		return MapSector::Sector2;
	else if (true == isSector3)
		return MapSector::Sector3;
	else
		return MapSector::Sector4;

	return MapSector::None;
}

TileCoordinate ShopManager::RandomCoordToSector(MapSector InSector)
{
	std::uniform_int_distribution<int> distribution(0, _possibleCoord[InSector].size()-1);
	__int32 random_number = distribution(generator);
	return _possibleCoord[InSector][random_number];
}

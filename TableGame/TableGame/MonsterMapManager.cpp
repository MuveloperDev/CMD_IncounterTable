#include "MonsterMapManager.h"


MonsterMapManager::MonsterMapManager(__int32 InTableSizeX, __int32 InTableSizeY, __int32 InDifficult) :
	_tableSizeX(InTableSizeX),
	_tableSizeY(InTableSizeY),
	sector1
	{
		0,
		0,
		InTableSizeX / 2 - 1,
		InTableSizeY / 2 - 1,
		MapSector::Sector1,
		InDifficult,
		0,
		0,
		_tableSizeY / 2
	},
	sector2
	{
		InTableSizeX / 2,
		0,
		InTableSizeX - 1,
		InTableSizeY / 2 - 1,
		MapSector::Sector2,
		InDifficult,
		0,
		0,
		_tableSizeY / 2
	},
	sector3
	{
		0,
		InTableSizeY / 2,
		InTableSizeX / 2 - 1,
		InTableSizeY - 1,
		MapSector::Sector3,
		InDifficult,
		0,
		0,
		_tableSizeY /2

	},
	sector4
	{
		InTableSizeX / 2,
		InTableSizeY / 2,
		InTableSizeX - 1,
		InTableSizeY - 1,
		MapSector::Sector4,
		InDifficult,
		0,
		0,
		_tableSizeY / 2
	},
	_targetSector(MapSector::None),
	_difficult(InDifficult),
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	_shape(L'◆')
{}

MonsterMapManager::~MonsterMapManager()
{
	for (const auto& [key, value] : _monsterTileInfo) {
		delete value;
	}
}

MapSector MonsterMapManager::SetTargetSector(const __int32 x, const __int32 y)
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
bool MonsterMapManager::IsMonstetTile(const __int32 x, const __int32 y)
{
	TileCoordinate coord { x, y };
	if (_monsterTileInfo.find(coord) == _monsterTileInfo.end())
		return false;
	return true;
}
const wchar_t MonsterMapManager::GetShape() const
{
	return _shape;
}
void MonsterMapManager::Awake()
{
	Initialize();
	for (const auto& [key, value] : _monsterTileInfo) {
		value->Awake();
	}
}
void MonsterMapManager::Start()
{
	for (const auto& [key, value] : _monsterTileInfo) {
		value->Start();
	}
}
void MonsterMapManager::Update()
{
	for (const auto& [key, value] : _monsterTileInfo) {
		value->Update();
	}
}
void MonsterMapManager::Render()
{
	std::wcout << _shape;
}
void MonsterMapManager::Initialize()
{
	if (_monsterTileInfo.size() != 0)
	{
		for (const auto& [key, value] : _monsterTileInfo) {
			delete value;
		}
		_monsterTileInfo.clear();
	}
	InitializeRandomMapPos();
}
void MonsterMapManager::GenerateRandomXPos(MapSector InSector, __int32 InLevel)
{
	switch (InSector)
	{
	case MapSector::Sector1:
	{
		std::uniform_int_distribution<int> distribution(sector1._startCoordinateX, sector1._endCoordinateX);
		__int32 random_number = distribution(generator);
		if (true == hasDuplicatedSectorPos(sector1._generatePosX, TileCoordinate(random_number, InLevel)))
		{
			GenerateRandomXPos(MapSector::Sector1, InLevel);
			break;
		}

		if (0 == InLevel && 0 == random_number)
		{
			GenerateRandomXPos(MapSector::Sector1, InLevel);
			break;
		}

		sector1._generatePosX.push_back(TileCoordinate(random_number, InLevel));
		break;
	}
	case MapSector::Sector2:
	{
		std::uniform_int_distribution<int> distribution(sector2._startCoordinateX, sector2._endCoordinateX);
		__int32 random_number = distribution(generator);
		if (true == hasDuplicatedSectorPos(sector2._generatePosX, TileCoordinate(random_number, InLevel)))
		{
			GenerateRandomXPos(MapSector::Sector2, InLevel);
			break;
		}
		sector2._generatePosX.push_back(TileCoordinate(random_number, InLevel));
		break;
	}
	case MapSector::Sector3:
	{
		std::uniform_int_distribution<int> distribution(sector3._startCoordinateX, sector3._endCoordinateX);
		__int32 random_number = distribution(generator);
		if (true == hasDuplicatedSectorPos(sector3._generatePosX, TileCoordinate(random_number, InLevel)))
		{
			GenerateRandomXPos(MapSector::Sector3, InLevel);
			break;
		}
		sector3._generatePosX.push_back(TileCoordinate(random_number, InLevel));
		break;
	}
	case MapSector::Sector4:
	{
		std::uniform_int_distribution<int> distribution(sector4._startCoordinateX, sector4._endCoordinateX);
		__int32 random_number = distribution(generator);

		if (true == hasDuplicatedSectorPos(sector4._generatePosX, TileCoordinate(random_number, InLevel)))
		{
			GenerateRandomXPos(MapSector::Sector4, InLevel);
			break;
		}

		if (_tableSizeY / 2 - 1 == InLevel && _tableSizeX - 1 == random_number)
		{
			GenerateRandomXPos(MapSector::Sector4, InLevel);
			break;
		}

		sector4._generatePosX.push_back(TileCoordinate(random_number, InLevel));
		break;
	}
	}
	
}

void MonsterMapManager::InitializeRandomMapPos()
{
	for (__int32 y = 0; y < _tableSizeY / 2; y++)
	{
		for (__int32 i = 0; i < _difficult; i++)
		{
			GenerateRandomXPos(MapSector::Sector1, y);
			GenerateRandomXPos(MapSector::Sector2, y);
			GenerateRandomXPos(MapSector::Sector3, y);
			GenerateRandomXPos(MapSector::Sector4, y);
		}
	}
	ReverseSectorPos();
	for (__int32 y = 0; y < _tableSizeY; y++)
	{
		sector1.generatingNum = 0;
		sector2.generatingNum = 0;
		sector3.generatingNum = 0;
		sector4.generatingNum = 0;

		for (__int32 x = 0; x < _tableSizeX; x++)
		{
			_targetSector = SetTargetSector(x, y);
			std::uniform_int_distribution<int> distribution(sector1._startCoordinateX, sector1._endCoordinateX);
			__int32 random_number = distribution(generator);
			switch (_targetSector)
			{
			case MapSector::None:
				break;
			case MapSector::Sector1:
				if (sector1.generatingNum < sector1._maxGeneratingNum)
				{
					TileCoordinate sector1Last = sector1._generatePosX.back();
					sector1._generatePosX.pop_back();
					_monsterTileInfo.insert({ TileCoordinate{sector1Last._posX, y},new MonsterTile(sector1Last._posX, y, GenerateRandomMonsterType()) });
					sector1.generatingNum++;
				}
				break;
			case MapSector::Sector2:
				if (sector2.generatingNum < sector2._maxGeneratingNum)
				{
					TileCoordinate sector2Last = sector2._generatePosX.back();
					sector2._generatePosX.pop_back();
					_monsterTileInfo.insert({ TileCoordinate{sector2Last._posX, y},new MonsterTile(sector2Last._posX, y, GenerateRandomMonsterType()) });
					sector2.generatingNum++;
				}
				break;
			case MapSector::Sector3:
				if (sector3.generatingNum < sector3._maxGeneratingNum)
				{
					TileCoordinate sector3Last = sector3._generatePosX.back();
					sector3._generatePosX.pop_back();
					_monsterTileInfo.insert({ TileCoordinate{sector3Last._posX, y},new MonsterTile(sector3Last._posX, y, GenerateRandomMonsterType()) });
					sector3.generatingNum++;
				}
				break;
			case MapSector::Sector4:
				if (sector4.generatingNum < sector4._maxGeneratingNum)
				{
					TileCoordinate sector4Last = sector4._generatePosX.back();
					sector4._generatePosX.pop_back();
					_monsterTileInfo.insert({ TileCoordinate{sector4Last._posX, y},new MonsterTile(sector4Last._posX, y, GenerateRandomMonsterType()) });
					sector4.generatingNum++;
				}
				break;
			}
		}
	}
}

bool MonsterMapManager::hasDuplicatedSectorPos(std::vector<TileCoordinate>& vec, TileCoordinate value)
{
	for (const auto& tile : vec) 
	{
		if (tile._posX == value._posX && tile._posY == value._posY)
			return true;
	}
	return false;
}

void MonsterMapManager::ReverseSectorPos()
{
	std::sort(sector1._generatePosX.begin(), sector1._generatePosX.end(),
		[](const TileCoordinate& a, const TileCoordinate& b) {
			return a._posY > b._posY;  // `_posX` 값을 기준으로 내림차순 정렬
		});
	std::sort(sector2._generatePosX.begin(), sector2._generatePosX.end(),
		[](const TileCoordinate& a, const TileCoordinate& b) {
			return a._posY > b._posY;  // `_posX` 값을 기준으로 내림차순 정렬
		});
	std::sort(sector3._generatePosX.begin(), sector3._generatePosX.end(),
		[](const TileCoordinate& a, const TileCoordinate& b) {
			return a._posY > b._posY;  // `_posX` 값을 기준으로 내림차순 정렬
		});
	std::sort(sector4._generatePosX.begin(), sector4._generatePosX.end(),
		[](const TileCoordinate& a, const TileCoordinate& b) {
			return a._posY > b._posY;  // `_posX` 값을 기준으로 내림차순 정렬
		});
}

SaveMonsterTileInfo MonsterMapManager::GetUnDoData()
{
	SaveMonsterTileInfo data;
	//std::map<MonsterMapManager::TileCooridnate, UnReDoManager::UndoMonsterData> data;
	for (const auto& [key, value] : _monsterTileInfo) {
		SaveMonsterData mData;
		mData.monster_Hp = value->GetMonster()->GetHp();
		mData.monster_IsClear = value->GetMonster()->GetIsClear();
		mData.isClear = value->GetIsClear();
		mData.isRun = value->GetIsRun();
		mData.type = value->GetMonster()->GetMonsterType();
		data.data.insert({ key, mData });
	}

	return data;
}

void MonsterMapManager::SetUndoData(SaveMonsterTileInfo InData)
{
	for (const auto& [key, value] : _monsterTileInfo) {
		if (InData.data.find(key) == InData.data.end())
		{
			MessageBox(NULL, (LPCWSTR)L"MonsterMapManager.SetUnDoData() : can't found key...",
				(LPCWSTR)L"Key Not Found... ", MB_OK | MB_ICONWARNING);
			continue;
		}

		SaveMonsterData data = InData.data[key];
		value->GetMonster()->SetReplaceHp(data.monster_Hp);
		value->GetMonster()->SetClear(data.monster_IsClear);
		value->SetIsClear(data.isClear);
		value->SetIsRun(data.isRun);
	}
}

void MonsterMapManager::LoadData(SaveMonsterTileInfo InData)
{
	if (_monsterTileInfo.size() != 0)
	{
		for (const auto& [key, value] : _monsterTileInfo) {
			delete value;
		}
		_monsterTileInfo.clear();
	}
	for (const auto& [key, value] : InData.data) {
		_monsterTileInfo.insert({ key, new MonsterTile(key._posX, key._posY, value.type)});
		_monsterTileInfo[key]->GetMonster()->SetReplaceHp(value.monster_Hp);
		_monsterTileInfo[key]->GetMonster()->SetClear(value.monster_IsClear);
		_monsterTileInfo[key]->SetIsClear(value.isClear);
		_monsterTileInfo[key]->SetIsRun(value.isRun);
	}
	
}


MonsterType MonsterMapManager::GenerateRandomMonsterType()
{
	std::uniform_int_distribution<int> distribution(static_cast<int>(MonsterType::Skeleton), static_cast<int>(MonsterType::ParasiticBat));
	__int32 random_type_number = distribution(generator);
	return static_cast<MonsterType>(random_type_number);
}

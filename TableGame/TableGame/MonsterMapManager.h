#pragma once
#include "TableGame.h"
#include "MonsterTile.h"

class MonsterTile;
class MonsterMapManager
{
public:

	struct Sector
	{
		__int32 _startCoordinateX;
		__int32 _startCoordinateY;
		__int32 _endCoordinateX;
		__int32 _endCoordinateY;
		MapSector sector;
		__int32 _maxGeneratingNum;
		__int32 generatingNum;
		__int32 generatingLevelNum;
		__int32 _maxLevelGeneratingNum;
		std::vector<TileCoordinate> _generatePosX;
	};
	MonsterMapManager(__int32 InTableSizeX, __int32 InTableSizeY, __int32 InDifficult);
	~MonsterMapManager();
	bool IsMonstetTile(const __int32 x, const __int32 y);
	const wchar_t GetShape() const;
	void Awake();
	void Start();
	void Update();
	void Render();
	void Initialize();
	SaveMonsterTileInfo GetUnDoData();
	void SetUndoData(SaveMonsterTileInfo InData);
	void LoadData(SaveMonsterTileInfo InData);
private:
	std::map<TileCoordinate, MonsterTile*> _monsterTileInfo;
	__int32 _tableSizeX;
	__int32 _tableSizeY;
	__int32 _difficult;
	const wchar_t _shape;
	Sector sector1;
	Sector sector2;
	Sector sector3;
	Sector sector4;
	MapSector _targetSector;
	MapSector SetTargetSector(const __int32 x, const __int32 y);
	void GenerateRandomXPos(MapSector InSector, __int32 InLevel);
	void InitializeRandomMapPos();
	bool hasDuplicatedSectorPos(std::vector<TileCoordinate>& vec, TileCoordinate value);
	void ReverseSectorPos();
	MonsterType GenerateRandomMonsterType();
	std::default_random_engine generator;
};

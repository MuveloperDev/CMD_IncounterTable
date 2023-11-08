#pragma once
#include "TableGame.h"
#include "Shop.h"

class ShopManager
{
public:
	ShopManager(__int32 InTableSizeX, __int32 InTableSizeY, __int32 InDifficult);
	~ShopManager();
	void Awake();
	void Start();
	void Update();
	void Render();
	void Initialize();
	const wchar_t GetShape() const;
	bool IsShop(__int32 InX, __int32 InY);
	void SetTargetShop(Shop* InShop);
	void IsPlayerOnShop();
	Shop* GetTargetShop();
public :
	struct Sector
	{
		__int32 _startCoordinateX;
		__int32 _startCoordinateY;
		__int32 _endCoordinateX;
		__int32 _endCoordinateY;
		MapSector sector;
		__int32 _maxGeneratingNum;
		__int32 generatingNum;
	}; 
private:
	__int32 _tableSizeX;
	__int32 _tableSizeY;
	__int32 _difficult;
	const wchar_t _shape;
	Sector sector1;
	Sector sector2;
	Sector sector3;
	Sector sector4;
	Shop* _currentTargetShop;
	std::map<MapSector, std::vector<TileCoordinate>> _possibleCoord;
	std::map<MapSector, Shop*> ShopList;
	std::default_random_engine generator;
private:
	void SetPossibleGeneratePos();
	void ShopGenerator();
	MapSector SetTargetSector(const __int32 x, const __int32 y);
	TileCoordinate RandomCoordToSector(MapSector InSector);
};


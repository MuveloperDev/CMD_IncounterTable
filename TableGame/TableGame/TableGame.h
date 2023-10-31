#pragma once
#include <memory>
#include <mutex>
#include <cstdlib> // for system
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <windows.h>
#include <iostream>
#include <locale>
#include <clocale>
#include <algorithm>
#include <chrono>
#include <map>
#include <functional>
#include "Utility.h"
#include "Enum.h"
#include "GameManager.h"
#include "BattleManager.h"
#include "MonsterMapManager.h"
#include "Player.h"
#include "TableBoard.h"
#include "EscapeTile.h"
#include "InventoryManager.h"
#include "ShopManager.h"

struct TileCooridnate
{
	__int32 _posX;
	__int32 _posY;

	bool operator<(const TileCooridnate& other) const {
		if (_posX == other._posX) {
			return _posY < other._posY;
		}
		else {
			return _posX < other._posX;
		}
	}
};
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
	std::vector<TileCooridnate> _generatePosX;
};
class TableGame
{
};


#pragma once
#include <vector>
#include <map>
#include "ItemBase.h"
#include "Enum.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>

struct TileCoordinate
{
	__int32 _posX;
	__int32 _posY;

	bool operator<(const TileCoordinate& other) const {
		if (_posX == other._posX) {
			return _posY < other._posY;
		}
		else {
			return _posX < other._posX;
		}
	}
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& _posX;
		ar& _posY;
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
	std::vector<TileCoordinate> _generatePosX;
};

struct InventoryItem
{
	__int32 _count;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& _count;
	}
};

struct SavePlayerData
{
	__int32 playerPosX;
	__int32 playerPosY;
	__int32 hp;
	__int32 attackDamge;
	__int32 gold;
	std::map<ItemType, InventoryItem> _itemList;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& playerPosX;
		ar& playerPosY;
		ar& hp;
		ar& attackDamge;
		ar& gold;
		std::map<int, InventoryItem> _int_itemList;
		if (Archive::is_saving::value) {
			for (auto& pair : _itemList) {
				_int_itemList[static_cast<int>(pair.first)] = pair.second;
			}
		}
		ar& _int_itemList;
		if (Archive::is_loading::value) {
			for (auto& pair : _int_itemList) {
				_itemList[static_cast<ItemType>(pair.first)] = pair.second;
			}
		}
	}
};
struct SaveMonsterData
{
	__int32 monster_Hp;
	bool monster_IsClear;
	bool isClear;
	bool isRun;
	MonsterType type;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& monster_Hp;
		ar& monster_IsClear;
		ar& isClear;
		ar& isRun;
		__int32 int_type;
		if (Archive::is_saving::value) {
			int_type = static_cast<__int32> (type);
		}
		ar& int_type;

		if (Archive::is_loading::value) {
			type = static_cast<MonsterType> (int_type);
		}
	}
};
struct SaveMonsterTileInfo
{
	std::map<TileCoordinate, SaveMonsterData> data;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& data;
	}
};
struct SaveData
{
	SavePlayerData playerData;
	SaveMonsterTileInfo monsterData;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& playerData;
		ar& monsterData;
	}

};

struct SaveFileData
{
	std::string fileInfo;
	Difficult difficult;
	SaveData data;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& fileInfo;
		ar& data;

		__int32 int_type;
		if (Archive::is_saving::value) {
			int_type = static_cast<__int32> (difficult);
		}
		ar& int_type;

		if (Archive::is_loading::value) {
			difficult = static_cast<Difficult> (int_type);
		}
	}


};
class Structs
{

};


#pragma once

enum class GameMode
{
	None,
	TableMode,
	BattleMode,
	InventoryMode,
	ShopMode
};
enum class Scene
{
	None,
	Title,
	Game,
	Lose,
	Escape
};
enum class Difficult
{
	Easy = 1,
	Normal = 3,
	Hard = 5,
};
enum class MonsterType
{
	Skeleton = 0,
	Devil,
	BigFoot,
	Cyclops,
	ParasiticBat
};
enum class MapSector
{
	None = -1,
	Sector1 = 0,
	Sector2,
	Sector3,
	Sector4
};
enum class PlayerInputBattleMode
{
	None,
	Up,
	Down,
	Enter
};

enum class PlayerChoiceListBattleMode
{
	None =0,
	Attack,
	Inventory,
	Run
};
enum class BattlePage
{
	None,
	Player,
	Monster
};

enum class MonsterAction
{
	None,
	Attack,
	Magic,
	Gaurd
};

enum class ItemType
{
	None = -1,
	HPPotion = 0,
	PowerUp,
	Exit,
	Max,
};
class Enum
{
};


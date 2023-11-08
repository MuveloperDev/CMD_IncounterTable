#pragma once

enum class GameMode
{
	None,
	TableMode,
	BattleMode,
	InventoryMode,
	ShopMode,
	OptionMode,
	UnReDoMode,
	SaveLoadMode,
};
enum class Scene
{
	None,
	Intro,
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
	ParasiticBat,
	Dragon,
};
enum class MapSector
{
	None = -1,
	Sector1 = 0,
	Sector2,
	Sector3,
	Sector4
};
enum class PlayerInputSelectMode
{
	None,
	Up,
	Down,
	Enter,
	ESC,
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
	MaxHPPotion,
	Exit,
	Max,
};

enum class TextColors
{
	None,
	Red,
	Green,
	Blue,
	Intensity
};
enum class PlayerInputTableMode
{
	None,
	Right,
	Left,
	Up,
	Down,
	ESC,
	Enter
};

enum class UIHorizontalInput
{
	None,
	Left,
	Right
};

enum class Options
{
	UndoRedo = 0,
	SaveLoad,
	Inventory,
	Exit,
	Max
};

enum class UnReDo
{
	Undo = 0,
	Redo,
	Exit,
	Max
};

enum class SaveLoadList
{
	Select1 = 0,
	Select2,
	Select3,
	Select4,
	Select5,
	Select6,
	Select7,
	Select8,
	Select9,
	Select10,
	Exit,
	Max,
};

enum class SaveLoadPopup
{
	Save = 0,
	Load,
	Exit,
	Max
};

enum class TitleMode
{
	Title = 0,
	Difficult,
	Max
};
class Enum
{
};


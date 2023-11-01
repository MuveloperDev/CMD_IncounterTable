#include "Shop.h"
#include "GameManager.h"
#include "Player.h"
#include "ShopManager.h"
#include "Utility.h"
#include "ItemBase.h"


Shop::Shop(__int32 InPosX, __int32 InPosY) :
	_posX(InPosX), _posY(InPosY), _shopMasterShape(R"(
    |`.             /
    | \`.          / |
    |  \ \.------./ '|
    |  .'          / |
    |  |             |
    \  |  ___ ' __  /
     \  \ `0 ) /0 //
      `--\    v  /-
         /\ -  /
      .--. '---'_
     /      ./ //-
    (`-.    .-'/- \
    /`- `--'    \__|
   /  ,          )_|
  /    Y        -  ( BP 
)"),
	_PLAYER_INPUT(PlayerInputSelectMode::None), _CURRENT_CHOICE_ITEM(0),
	_pointShape("▷"), _isLackOfMoney(false), _isExit(false), _isBuy(false),
	_tableShape(R"(
                                               /\      /\
                                               ||______||
                                               || ^  ^ ||
                                               \| |  | |/
                                                |______|
              __                                |  __  |
             /  \       ________________________|_/  \_|__
            / ^^ \     /=========================/ ^^ \===|
           /  []  \   /=========================/  []  \==|
          /________\ /=========================/________\=|
       *  |        |/==========================|        |=|
      *** | ^^  ^^ |---------------------------| ^^  ^^ |--
     *****| []  [] |           _____           | []  [] | |
    *******        |          /_____\          |      * | |
   *********^^  ^^ |  ^^  ^^  |  |  |  ^^  ^^  |     ***| |
  ***********]  [] |  []  []  |  |  |  []  []  | ===***** |
 *************     |         @|__|__|@         |/ |*******|
***************   ***********--=====--**********| *********
***************___*********** |=====| **********|***********
 *************     ********* /=======\ ******** | *********
)")
{
}

Shop::~Shop()
{
	if (_itemList.size() != 0)
	{
		for (const auto& [key, value] : _itemList) {
			delete value;
		}
		_itemList.clear();
	}
}

void Shop::Awake()
{
	Initialize();
}

void Shop::Start()
{
}

void Shop::Update()
{
	if (this != GameManager::GetInstance().GetShopManager().GetTargetShop())
		return;

	_PLAYER_INPUT = GameManager::GetInstance().GetPlayer().GetCurrentInputBattleMode();
	switch (_PLAYER_INPUT)
	{
	case PlayerInputSelectMode::None:
		break;
	case PlayerInputSelectMode::Up:
		_CURRENT_CHOICE_ITEM--;
		if (static_cast<int>(ItemType::None) >= _CURRENT_CHOICE_ITEM)
			_CURRENT_CHOICE_ITEM++;
		break;
	case PlayerInputSelectMode::Down:
		_CURRENT_CHOICE_ITEM++;
		if (static_cast<int>(ItemType::Max) <= _CURRENT_CHOICE_ITEM)
			_CURRENT_CHOICE_ITEM--;
		break;
	case PlayerInputSelectMode::Enter:
		ChoiceProcess();
		break;
	default:
		break;
	}
}

void Shop::Render()
{
	if (this != GameManager::GetInstance().GetShopManager().GetTargetShop())
		return;

	Utility::GetInstance().SetCursorPosition(0, 0);
	std::cout << "▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤" << std::endl;
	Utility::GetInstance().SetCursorPosition(48, 1);
	std::cout << "[ S H O P ]" << std::endl;
	GameManager::GetInstance().GetPlayer().PrintPlayerStatus(false);
	Utility::GetInstance().SetCursorPosition(48, 3);
	PrintItemList();
	PrintLine(20);
	PrintLine(85);
	Utility::GetInstance().ChangeTextColor(TextColors::Intensity, true);
	Utility::GetInstance().PrintShape(24, 7, _tableShape);
	Utility::GetInstance().ResetTextColor();
	Utility::GetInstance().PrintShape(90, 8, _shopMasterShape);
	Utility::GetInstance().SetCursorPosition(105, 27);
	std::cout << "  USE - ENTER" << std::endl;
	std::cout << "▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤" << std::endl;
	PrintComment(_isLackOfMoney, "You low on gold......");
	PrintComment(_isBuy, "Thank you....");
	
}

void Shop::Initialize()
{
	if (_itemList.size() != 0)
	{
		for (const auto& [key, value] : _itemList) {
			delete value;
		}
		_itemList.clear();
	}

	for (__int32 i = 0; i < static_cast<int>(ItemType::Max); i++)
	{
		ItemType type = static_cast<ItemType>(i);
		switch (type)
		{
		case ItemType::None:
			break;
		case ItemType::HPPotion:
			_itemList.insert({ ItemType::HPPotion,  static_cast<ItemBase*>(new ItemHpPotion()) });
			break;
		case ItemType::PowerUp:
			_itemList.insert({ ItemType::PowerUp,   static_cast<ItemBase*>(new ItemPowerUp()) });
			break;
		case ItemType::Max:
			break;
		default:
			break;
		}

	}
}

void Shop::IsPlayerOnShop()
{
	__int32 playerPosX = GameManager::GetInstance().GetPlayer().GetPosX();
	__int32 playerPosY = GameManager::GetInstance().GetPlayer().GetPosY();
	if (playerPosX == _posX && playerPosY == _posY)
	{
		if (true == _isExit)
			return;

		if (GameMode::ShopMode != GameManager::GetInstance().GetCurrentGameMode())
		{
			GameManager::GetInstance().ChangeGameMode(GameMode::ShopMode, nullptr);
			GameManager::GetInstance().GetShopManager().SetTargetShop(this);
		}
	}
	else
	{
		if (true == _isExit)
		{
			_isExit = false;
		}
	}
}

void Shop::PrintItemList()
{
	for (__int32 i = 0; i < static_cast<int>(ItemType::Max); i++)
	{
		Utility::GetInstance().SetCursorPosition(42, 4 + i);
		ItemType key = static_cast<ItemType>(i);
		ItemBase* base = _itemList[key];
		switch (key)
		{
		case ItemType::None:
			break;
		case ItemType::HPPotion:
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout << "  HP Potion - [ " << base->GetPrice() << " G ]" << std::endl;
				break;
			}
			Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape << "HP Potion - [ " << base->GetPrice() << " G ]" << std::endl;
			Utility::GetInstance().ResetTextColor();
			break;
		case ItemType::PowerUp:
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout << "  Power Up - [ " << base->GetPrice() << " G ]" << std::endl;
				break;
			}
			Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape << "Power Up - [ " << base->GetPrice() << " G ]" << std::endl;
			Utility::GetInstance().ResetTextColor();
			break;
		case ItemType::Exit:
			Utility::GetInstance().SetCursorPosition(105, 26);
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout << "  EXIT" << std::endl;
				break;
			}
			Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape << "EXIT" << std::endl;
			Utility::GetInstance().ResetTextColor();
			break;
		case ItemType::Max:
			break;
		default:
			break;
		}
	}
}

void Shop::ChoiceProcess()
{
	ItemType type = static_cast<ItemType>(_CURRENT_CHOICE_ITEM);
	switch (type)
	{
	case ItemType::None:
		break;
	case ItemType::HPPotion:
	{
		ItemBase* base = _itemList[type];
		if (0 > GameManager::GetInstance().GetPlayer().GetGold() - base->GetPrice())
		{
			_isLackOfMoney = true;
			break;
		}
		GameManager::GetInstance().GetPlayer().SetGold(-base->GetPrice());
		GameManager::GetInstance().GetInventoryManager().GetItem(ItemType::HPPotion)->SetCount(1);
		_isBuy = true;
		break;
	}
	case ItemType::PowerUp:
	{
		ItemBase* base = _itemList[type];
		if (0 > GameManager::GetInstance().GetPlayer().GetGold() - base->GetPrice())
		{
			_isLackOfMoney = true;
			break;
		}
		GameManager::GetInstance().GetPlayer().SetGold(-base->GetPrice());
		GameManager::GetInstance().GetInventoryManager().GetItem(ItemType::PowerUp)->SetCount(1);
		_isBuy = true;
		break;
	}
	case ItemType::Exit:
	{
		_isExit = true;
		GameMode prevMode = GameManager::GetInstance().GetPrevGameMode();
		GameManager::GetInstance().ChangeGameMode(prevMode, nullptr);
		GameManager::GetInstance().GetShopManager().SetTargetShop(nullptr);
		break;
	}
	case ItemType::Max:
		break;
	default:
		break;
	}
}

__int32 Shop::GetPosX() const
{
	return _posX;
}

__int32 Shop::GetPosY() const
{
	return _posY;
}

void Shop::PrintComment(bool& InFlag,  std::string InComment)
{
	if (true == InFlag)
	{
		Utility::GetInstance().SetCursorPosition(88, 4);
		std::cout << "================================" << std::endl;
		Utility::GetInstance().SetCursorPosition(90, 5);
		std::cout << "\"" << InComment << "\"" << std::endl;
		Utility::GetInstance().SetCursorPosition(88, 6);
		std::cout << "================================" << std::endl;
		Sleep(1000);
		Utility::GetInstance().ClearCmd();
	}
	InFlag = false;
}

void Shop::PrintLine(__int32 InX)
{
	for (__int32 i = 1; i < 28; i++)
	{
		Utility::GetInstance().SetCursorPosition(InX, i);
		std::cout << "▥" << std::endl;
	}
}

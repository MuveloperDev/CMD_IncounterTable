#include "InventoryManager.h"

InventoryManager::InventoryManager() : 
	_PLAYER_INPUT(PlayerInputSelectMode::None), _CURRENT_CHOICE_ITEM(0),
	_pointShape("¢¹"), _CURRENT_TEXT_COLOR(TextColors::None),
	_hConsole(GetStdHandle(STD_OUTPUT_HANDLE)),
	_inventoryShape(R"(
_________              _______    _         _________   _______    _______            
\__   __/  |\     /|  (  ____ \  ( (    /|  \__   __/  (  ___  )  (  ____ )  |\     /|
   ) (     | )   ( |  | (    \/  |  \  ( |     ) (     | (   ) |  | (    )|  ( \   / )
   | |     | |   | |  | (__      |   \ | |     | |     | |   | |  | (____)|   \ (_) / 
   | |     ( (   ) )  |  __)     | (\ \) |     | |     | |   | |  |     __)    \   /  
   | |      \ \_/ /   | (        | | \   |     | |     | |   | |  | (\ (        ) (   
___) (___    \   /    | (____/\  | )  \  |     | |     | (___) |  | ) \ \__     | |   
\_______/     \_/     (_______/  |/    )_)     )_(     (_______)  |/   \__/     \_/ 
)"),
	_inventorySimpleShape(R"(
   _....._
  ';-.--';'
    }===={       _.---.._
  .'      '.    ';-..--';
 /::        \    `}===={
|::          :   '      '.
\::.        _.---_        \
 '::_     _`---..-';       |
     `````  }====={        /
          .'       '.   _.'
         /::         \ `
        |::           |
        \::.          /
         '::_      _.'
             ``````
)")
{

}

InventoryManager::~InventoryManager()
{
	if (_itemList.size() != 0)
	{
		for (const auto& [key, value] : _itemList) {
			delete value;
		}
		_itemList.clear();
	}
}

void InventoryManager::Awake()
{
	Initialize();
}

void InventoryManager::Start()
{
}

void InventoryManager::Update()
{
	if (TextColors::None != _CURRENT_TEXT_COLOR)
	{
		Sleep(1000);
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		_CURRENT_TEXT_COLOR = TextColors::None;
	}
	_PLAYER_INPUT = GameManager::GetInstance().GetPlayer().GetCurrentInputBattleMode();
	switch (_PLAYER_INPUT)
	{
	case PlayerInputSelectMode::None:
		break;
	case PlayerInputSelectMode::Up:
		_CURRENT_CHOICE_ITEM--;
		if (static_cast<int>(ItemType::None) >=_CURRENT_CHOICE_ITEM)
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

void InventoryManager::Render()
{
	Utility::GetInstance().PrintTopLine();
	GameManager::GetInstance().GetPlayer().PrintPlayerStatus(false);
	Utility::GetInstance().PrintVerticalLine(20);
	Utility::GetInstance().SetCursorPosition(22, 27);
	std::cout << "  USE - ENTER" << std::endl;
	Utility::GetInstance().PrintBottomLine();
	PrintItemList();
	Utility::GetInstance().ChangeTextColor(TextColors::Intensity, true);
	Utility::GetInstance().PrintShape(29, 16, _inventoryShape);
	Utility::GetInstance().ResetTextColor();
}

void InventoryManager::SimpleUI()
{
	Utility::GetInstance().SetCursorPosition(94, 1);
	std::cout << "[ I N V E N T O R Y ]" << std::endl;
	for (__int32 i = 0; i < static_cast<int>(ItemType::Max); i++)
	{
		Utility::GetInstance().SetCursorPosition(94, 2 + i);
		ItemType key = static_cast<ItemType>(i);
		ItemBase* base = _itemList[key];
		switch (key)
		{
		case ItemType::None:
			break;
		case ItemType::HPPotion:
			std::cout << "  HP Potion - [ " << base->GetCount() << " ]" << std::endl;
			break;
		case ItemType::PowerUp:
			std::cout << "  Power Up - [ " << base->GetCount() << " ]" << std::endl;
			break;
		case ItemType::Exit:
		case ItemType::Max:
			break;
		default:
			break;
		}
	}

	Utility::GetInstance().PrintShape(91,12, _inventorySimpleShape);
}

ItemBase* InventoryManager::GetItem(ItemType InType)
{
	if (_itemList.find(InType) != _itemList.end())
		return _itemList[InType];
	return nullptr;
}

void InventoryManager::Initialize()
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

void InventoryManager::PrintItemList()
{
	Utility::GetInstance().SetCursorPosition(60,1);
	std::cout << "[ I N V E N T O R Y ]" << std::endl;
	for (__int32 i = 0; i < static_cast<int>(ItemType::Max); i++)
	{
		Utility::GetInstance().SetCursorPosition(60, 2+i);
		ItemType key = static_cast<ItemType>(i);
		ItemBase* base = _itemList[key];
		switch (key)
		{
		case ItemType::None:
			break;
		case ItemType::HPPotion:
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout <<"  HP Potion - [ " << base->GetCount() << " ]" << std::endl;
				break;
			}
			if(PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape <<"HP Potion - [ " << base->GetCount() << " ]" << std::endl;
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ResetTextColor();
			break;
		case ItemType::PowerUp:
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout << "  Power Up - [ " << base->GetCount() << " ]" << std::endl;
				break;
			}
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape << "Power Up - [ " << base->GetCount() << " ]" << std::endl;
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ResetTextColor();
			break;
		case ItemType::Exit:
			Utility::GetInstance().SetCursorPosition(22, 26);
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout << "  EXIT" << std::endl;
				break;
			}
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape << "EXIT" << std::endl;
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ResetTextColor();
			break;
		case ItemType::Max:
			break;
		default:
			break;
		}
	}
}

void InventoryManager::ChoiceProcess()
{
	ItemType type = static_cast<ItemType>(_CURRENT_CHOICE_ITEM);
	switch (type)
	{
	case ItemType::None:
		break;
	case ItemType::HPPotion:
	{
		ItemBase* base = _itemList[type];
		SetConsoleTextAttribute(_hConsole, FOREGROUND_GREEN);
		_CURRENT_TEXT_COLOR = TextColors::Green;
		base->Use();
		break;
	}
	case ItemType::PowerUp:
	{
		ItemBase* base = _itemList[type];

		SetConsoleTextAttribute(_hConsole, FOREGROUND_BLUE);
		_CURRENT_TEXT_COLOR = TextColors::Blue;
		base->Use();
		break;
	}
	case ItemType::Exit:
	{
		GameMode prevMode = GameManager::GetInstance().GetPrevGameMode();
		GameManager::GetInstance().ChangeGameMode(prevMode, nullptr);
		break;
	}
	case ItemType::Max:
		break;
	default:
		break;
	}
}

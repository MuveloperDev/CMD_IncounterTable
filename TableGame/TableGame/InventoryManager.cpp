#include "InventoryManager.h"
#include "ItemMaxHpPotion.h"

InventoryManager::InventoryManager() : 
	InputBase(),
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
	_PLAYER_INPUT = GameManager::GetInstance().GetPlayer().GetCurrentInputSelectMode();
	switch (_PLAYER_INPUT)
	{
	case PlayerInputSelectMode::None:
		break;
	case PlayerInputSelectMode::Up:
		if (static_cast<int>(ItemType::HPPotion) == _CURRENT_CHOICE_ITEM)
		{
			_CURRENT_CHOICE_ITEM = static_cast<int>(ItemType::Max) - 1;
			break;
		}
		_CURRENT_CHOICE_ITEM--;
		_CURRENT_CHOICE_ITEM_SELECT_CNT = 0;
		Utility::GetInstance().ClearCmd();
		break;
	case PlayerInputSelectMode::Down:
		if (static_cast<int>(ItemType::Max) - 1 == _CURRENT_CHOICE_ITEM)
		{
			_CURRENT_CHOICE_ITEM = 0;
			break;
		}
		_CURRENT_CHOICE_ITEM++;
		_CURRENT_CHOICE_ITEM_SELECT_CNT = 0;
		Utility::GetInstance().ClearCmd();
		break;
	case PlayerInputSelectMode::Enter:
		ChoiceProcess();
		break;
	default:
		break;
	}

	UIHorizontalInputUpdate();
	HorizontalInputProcess();
}

void InventoryManager::Render()
{
	GameManager::GetInstance().GetPlayer().PrintPlayerStatus(false);
	PrintItemList();
	Utility::GetInstance().ChangeTextColor(TextColors::Intensity, true);
	Utility::GetInstance().PrintShape(29, 16, _inventoryShape);
	Utility::GetInstance().ResetTextColor();
	Utility::GetInstance().SetCursorPosition(22, 27);
	std::cout << "  USE - ENTER" << std::endl;
	Utility::GetInstance().PrintVerticalLine(20, 1, 27);
	RenderDescription();
	Utility::GetInstance().PrintFrame();
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
		case ItemType::MaxHPPotion:
			std::cout << "  Max HP Potion - [ " << base->GetCount() << " ]" << std::endl;
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

std::map<ItemType, InventoryItem> InventoryManager::GetItemList()
{
	std::map<ItemType, InventoryItem> map;
	for (const auto& [key, value] : _itemList) {
		if (ItemType::Exit == key)
			continue;

		InventoryItem data;
		data._count = value->GetCount();
		map.insert({key, data});
	}
	return map;
}

void InventoryManager::SetItemList(std::map<ItemType, InventoryItem> InMap)
{
	for (const auto& [key, value] : InMap) {
		if (_itemList.find(key) == _itemList.end())
		{
			MessageBox(NULL, (LPCWSTR)L"MonsterMapManager.SetUnDoData() : can't found key...",
				(LPCWSTR)L"Key Not Found... ", MB_OK | MB_ICONWARNING);
			continue;
		}
		_itemList[key]->ReplaceCount(value._count);
	}
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
		case ItemType::MaxHPPotion:
			_itemList.insert({ ItemType::MaxHPPotion,   static_cast<ItemBase*>(new ItemMaxHpPotion()) });
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
	Utility::GetInstance().SetCursorPosition(30,2);
	std::cout << "[ I N V E N T O R Y ]" << std::endl;
	__int32 adjust = 0;
	for (__int32 i = 0; i < static_cast<int>(ItemType::Max); i++)
	{
		Utility::GetInstance().SetCursorPosition(25, 4+i+ adjust);
		ItemType key = static_cast<ItemType>(i);
		ItemBase* base = _itemList[key];
		switch (key)
		{
		case ItemType::None:
			break;
		case ItemType::HPPotion:
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout <<"  HP Potion - [ " << base->GetCount() << " ] [ - 0 + ]" << std::endl;
				break;
			}
			if(PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape <<"HP Potion - [ " << base->GetCount() << " ] " << "[ - " << _CURRENT_CHOICE_ITEM_SELECT_CNT << " + ]" << std::endl;
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ResetTextColor();
			break;
		case ItemType::PowerUp:
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout << "  Power Up - [ " << base->GetCount() << " ] [ - 0 + ]" << std::endl;
				break;
			}
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape << "Power Up - [ " << base->GetCount() << " ] " << "[ - " << _CURRENT_CHOICE_ITEM_SELECT_CNT << " + ]" << std::endl;
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ResetTextColor();
			break;
		case ItemType::MaxHPPotion:
			if (key != static_cast<ItemType>(_CURRENT_CHOICE_ITEM))
			{
				std::cout << "  Max HP Potion - [ " << base->GetCount() << " ] [ - 0 + ]" << std::endl;
				break;
			}
			if (PlayerInputSelectMode::Enter != _PLAYER_INPUT)
				Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
			std::cout << _pointShape << "Max HP Potion - [ " << base->GetCount() << " ] " << "[ - " << _CURRENT_CHOICE_ITEM_SELECT_CNT << " + ]" << std::endl;
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
		adjust++;
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
		if (base->GetCount() <= _CURRENT_CHOICE_ITEM_SELECT_CNT)
		{
			_CURRENT_CHOICE_ITEM_SELECT_CNT = base->GetCount();
		}
		base->Use(_CURRENT_CHOICE_ITEM_SELECT_CNT);
		break;
	}
	case ItemType::PowerUp:
	{
		ItemBase* base = _itemList[type];

		SetConsoleTextAttribute(_hConsole, FOREGROUND_BLUE);
		_CURRENT_TEXT_COLOR = TextColors::Blue;
		if (base->GetCount() <= _CURRENT_CHOICE_ITEM_SELECT_CNT)
		{
			_CURRENT_CHOICE_ITEM_SELECT_CNT = base->GetCount();
		}
		base->Use(_CURRENT_CHOICE_ITEM_SELECT_CNT);
		break;
	}
	case ItemType::MaxHPPotion:
	{
		ItemBase* base = _itemList[type];

		SetConsoleTextAttribute(_hConsole, FOREGROUND_GREEN);
		_CURRENT_TEXT_COLOR = TextColors::Green;
		if (base->GetCount() <= _CURRENT_CHOICE_ITEM_SELECT_CNT)
		{
			_CURRENT_CHOICE_ITEM_SELECT_CNT = base->GetCount();
		}
		base->Use(_CURRENT_CHOICE_ITEM_SELECT_CNT);
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
	Utility::GetInstance().ClearCmd();
}

void InventoryManager::HorizontalInputProcess()
{
	UIHorizontalInput input = GetCurrentHInput();
	switch (input)
	{
	case UIHorizontalInput::None:
		break;
	case UIHorizontalInput::Left:
		if (0 >= _CURRENT_CHOICE_ITEM_SELECT_CNT)
		{
			_CURRENT_CHOICE_ITEM_SELECT_CNT = 0;
		}
		else _CURRENT_CHOICE_ITEM_SELECT_CNT--;
		break;
	case UIHorizontalInput::Right:
	{
		ItemType type = static_cast<ItemType>(_CURRENT_CHOICE_ITEM);
		switch (type)
		{
		case ItemType::HPPotion:
		case ItemType::PowerUp:
		case ItemType::MaxHPPotion:
		{
			ItemBase* base = _itemList[type];
			if (base->GetCount() <= _CURRENT_CHOICE_ITEM_SELECT_CNT)
			{
				_CURRENT_CHOICE_ITEM_SELECT_CNT = base->GetCount();
			}
			else _CURRENT_CHOICE_ITEM_SELECT_CNT++;
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}

void InventoryManager::RenderDescription()
{
	ItemType type = static_cast<ItemType>(_CURRENT_CHOICE_ITEM);
	switch (type)
	{
	case ItemType::HPPotion:
	case ItemType::PowerUp:
	case ItemType::MaxHPPotion:
	{
		ItemBase* base = _itemList[type];
		Utility::GetInstance().SetCursorPosition(80,5);
		std::cout << base->GetDescription();
		break;
	}
	default:
		break;

	}
}

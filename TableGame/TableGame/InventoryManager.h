#pragma once
#include "TableGame.h"
#include "ItemBase.h"
#include "ItemHpPotion.h"
#include "ItemPowerUp.h"

class InventoryManager
{
public:
	InventoryManager();
	~InventoryManager();
	void Awake();
	void Start();
	void Update();
	void Render();
	void SimpleUI();
	ItemBase* GetItem(ItemType InType);
private:
	__int32 _CURRENT_CHOICE_ITEM;
	HANDLE _hConsole;
	PlayerInputSelectMode _PLAYER_INPUT;
	std::map<ItemType, ItemBase*> _itemList;
	std::string _pointShape;
	std::string _inventoryShape;
	std::string _inventorySimpleShape;
	TextColors _CURRENT_TEXT_COLOR;
private:
	void Initialize();
	void PrintItemList();
	void ChoiceProcess();
};


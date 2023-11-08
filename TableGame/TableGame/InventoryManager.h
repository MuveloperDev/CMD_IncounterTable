#pragma once
#include "TableGame.h"
#include "ItemBase.h"
#include "ItemHpPotion.h"
#include "ItemPowerUp.h"
#include "InputBase.h"

class InventoryManager : public InputBase
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
	std::map<ItemType, InventoryItem> GetItemList();
	void SetItemList(std::map<ItemType, InventoryItem> InMap);
private:
	__int32 _CURRENT_CHOICE_ITEM;
	__int32 _CURRENT_CHOICE_ITEM_SELECT_CNT;
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
	void HorizontalInputProcess();
	void RenderDescription();
};


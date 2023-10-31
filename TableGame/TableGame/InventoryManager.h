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
private:
	__int32 _CURRENT_CHOICE_ITEM;
	PlayerInputBattleMode _PLAYER_INPUT;
	std::map<ItemType, ItemBase*> _itemList;
	std::string _pointShape;
private:
	void Initialize();
	void PrintItemList();
	void ChoiceProcess();
};


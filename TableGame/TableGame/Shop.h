#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include "Enum.h"
#include "ItemBase.h"
#include "ItemHpPotion.h"
#include "ItemPowerUp.h"
class Shop
{
public:
	Shop(__int32 InPosX, __int32 InPosY);
	~Shop();
	void Awake();
	void Start();
	void Update();
	void Render();
	void Initialize();
	void IsPlayerOnShop();
	void PrintItemList();
	void ChoiceProcess();
	__int32 GetPosX() const;
	__int32 GetPosY() const;
private:
	__int32 _posX;
	__int32 _posY;
	__int32 _CURRENT_CHOICE_ITEM;
	bool _isLackOfMoney;
	bool _isBuy;
	bool _isExit;
	PlayerInputBattleMode _PLAYER_INPUT;
	std::map<ItemType, ItemBase*> _itemList;
	std::string _pointShape;
	std::string _shopMasterShape;
	
private:
	void PrintComment(bool& InFlag, std::string InComment);
	void PrintLine(__int32 InX);
};


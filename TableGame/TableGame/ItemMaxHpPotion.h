#pragma once
#include "ItemBase.h"
class ItemMaxHpPotion : public ItemBase
{
public:
	ItemMaxHpPotion();
	~ItemMaxHpPotion();
	virtual void Use(__int32 InCnt) override;

private:
	__int32 increaseMaxHp;
};

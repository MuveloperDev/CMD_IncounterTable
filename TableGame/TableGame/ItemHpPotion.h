#pragma once
#include "ItemBase.h"

class ItemHpPotion : public ItemBase
{
public:
	ItemHpPotion();
	~ItemHpPotion();
	virtual void Use(__int32 InCnt) override;

private:
	__int32 increaseHp;
};


#pragma once
#include "ItemBase.h"
class ItemPowerUp : public ItemBase
{
public:
	ItemPowerUp();
	~ItemPowerUp();
	virtual void Use(__int32 InCnt) override;

private:
	__int32 increasePower;
};

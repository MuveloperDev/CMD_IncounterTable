#pragma once
#include "ItemBase.h"
class ItemPowerUp : public ItemBase
{
public:
	ItemPowerUp();
	~ItemPowerUp();
	virtual void Use() override;

private:
	__int32 increasePower;
};

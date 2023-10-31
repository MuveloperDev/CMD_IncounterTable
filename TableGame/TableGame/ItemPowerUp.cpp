#include "ItemPowerUp.h"
#include "GameManager.h"
ItemPowerUp::ItemPowerUp() :
	ItemBase(ItemType::PowerUp, 10), increasePower(10)
{
}

ItemPowerUp::~ItemPowerUp()
{
}

void ItemPowerUp::Use()
{
	GameManager::GetInstance().GetPlayer().SetAttackDamage(increasePower);
	_count--;
}

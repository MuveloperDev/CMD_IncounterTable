#include "ItemPowerUp.h"
#include "GameManager.h"
ItemPowerUp::ItemPowerUp() :
	ItemBase(ItemType::PowerUp, 10), increasePower(10)
{
	std::string description;
	description += std::to_string(increasePower) + " Increase attack damage potion.";
	SetDescription(description);
}

ItemPowerUp::~ItemPowerUp()
{
}

void ItemPowerUp::Use(__int32 InCnt)
{
	if (0 >= _count)
		return;

	GameManager::GetInstance().GetPlayer().SetAttackDamage(increasePower * InCnt);
	_count -= InCnt;
}

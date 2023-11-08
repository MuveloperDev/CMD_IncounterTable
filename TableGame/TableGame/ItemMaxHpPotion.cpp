#include "ItemMaxHpPotion.h"
#include "GameManager.h"
ItemMaxHpPotion::ItemMaxHpPotion() :
	ItemBase(ItemType::MaxHPPotion, 10), increaseMaxHp(20)
{
	std::string description;
	description += std::to_string(increaseMaxHp) + " Increase max hp potion.";
	SetDescription(description);
}

ItemMaxHpPotion::~ItemMaxHpPotion()
{
}

void ItemMaxHpPotion::Use(__int32 InCnt)
{
	if (0 >= _count)
		return;

	GameManager::GetInstance().GetPlayer().SetMaxHP(increaseMaxHp * InCnt);
	_count -= InCnt;
}

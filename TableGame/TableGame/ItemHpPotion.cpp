#include "ItemHpPotion.h"
#include "GameManager.h"

ItemHpPotion::ItemHpPotion():
	ItemBase(ItemType::HPPotion, 10), increaseHp(30)
{
	std::string description;
	description += std::to_string(increaseHp) + " HP recover potion.";
	SetDescription(description);
}

ItemHpPotion::~ItemHpPotion()
{
}

void ItemHpPotion::Use(__int32 InCnt)
{
	if (_count <= 0)
	{
		return;
	}
	GameManager::GetInstance().GetPlayer().SetHp(increaseHp * InCnt);
	_count -= InCnt;
}

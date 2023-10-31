#include "ItemHpPotion.h"
#include "GameManager.h"

ItemHpPotion::ItemHpPotion():
	ItemBase(ItemType::HPPotion, 10), increaseHp(30)
{
	
}

ItemHpPotion::~ItemHpPotion()
{
}

void ItemHpPotion::Use()
{
	if (_count <= 0)
	{
		return;
	}
	GameManager::GetInstance().GetPlayer().SetHp(increaseHp);
	_count--;
}

#include "Monster.h"

Monster::Monster(__int32 InMaxHp, __int32 InHp, __int32 InAttackDamage, __int32 InGoldDamage, std::string InMonsterShape) :
	MonsterBase(InMaxHp, InHp, InAttackDamage, InGoldDamage, InMonsterShape)
{
}

Monster::~Monster()
{
}

#pragma once

#include "MonsterBase.h"

class Monster: public MonsterBase
{
public:
	Monster(__int32 InMaxHp, __int32 InHp, __int32 InAttackDamage, __int32 InGoldDamage, std::string InMonsterShape);
	~Monster();
private:
};


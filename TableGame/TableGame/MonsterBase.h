#pragma once

//#include "TableGame.h"

#include <stdio.h>
#include <iostream>
#include "Enum.h"
class Player;
class MonsterBase
{
public:
	MonsterBase(__int32 InMaxHp, __int32 InHp, __int32 InAttackDamage, __int32 InGoldReward, bool InClear, std::string InMonsterShape, MonsterType InType, std::string InMonsterName);
	~MonsterBase();

	 __int32 GetHp() const;
	 __int32 GetMaxHp() const;
	 __int32 GetAttackDamage() const;
	 __int32 GetGoldReward() const;
	 bool GetIsClear() const;
	 std::string GetMonsterShpae() const;
	 std::string GetMonsterName() const;
	 MonsterType GetMonsterType() const;
	 MonsterAction GetMonsterAction() const;

	 void SetHp(__int32 InDamage);
	 void SetClear(bool InClear);
	 void SetMonsterAction(MonsterAction InMonsterAction);
	 void Attack(Player& InPlayer);
protected:
	__int32 _maxHp;
	__int32 _hp;
	__int32 _attackDamge;
	__int32 _goldReward;
	bool _isClear;
	std::string _monsterName;
	std::string _monsterShpae;
	MonsterType _type;
	MonsterAction _CURRENT_MONSTER_ACTION;
};


#include "MonsterBase.h"
#include "Player.h"
MonsterBase::MonsterBase(__int32 InMaxHp, __int32 InHp, __int32 InAttackDamage, __int32 InGoldReward, bool InClear, std::string InMonsterShape, MonsterType InType, std::string InMonsterName) :
	_maxHp(InMaxHp), _hp(InHp), _attackDamge(InAttackDamage), _goldReward(InGoldReward), _isClear(InClear),
	_monsterShpae(InMonsterShape), _type(InType), _monsterName(InMonsterName),
	_CURRENT_MONSTER_ACTION(MonsterAction::None)
{
}

MonsterBase::~MonsterBase()
{
}

__int32 MonsterBase::GetHp() const
{
	return _hp;
}

__int32 MonsterBase::GetMaxHp() const
{
	return _maxHp;
}

__int32 MonsterBase::GetAttackDamage() const
{
	return _attackDamge;
}

__int32 MonsterBase::GetGoldReward() const
{ 
	return _goldReward;
}

bool MonsterBase::GetIsClear() const
{
	return _isClear;
}

std::string MonsterBase::GetMonsterShpae() const
{
	return _monsterShpae;
}

std::string MonsterBase::GetMonsterName() const
{
	return _monsterName;
}
 
MonsterType MonsterBase::GetMonsterType() const
{
	return _type;
}

MonsterAction MonsterBase::GetMonsterAction() const
{
	return _CURRENT_MONSTER_ACTION;
}

void MonsterBase::SetHp(__int32 InDamage)
{
	_hp += InDamage;
	if (0 >= _hp)
	{
		_hp = 0;
	}
	else if (_hp >= _maxHp)
	{
		_hp = _maxHp;
	}
}

void MonsterBase::SetReplaceHp(__int32 InHp)
{
	_hp = InHp;
}

void MonsterBase::SetClear(bool InClear)
{
	_isClear = InClear;
}

void MonsterBase::SetMonsterAction(MonsterAction InMonsterAction)
{
	_CURRENT_MONSTER_ACTION = InMonsterAction;
}

void MonsterBase::Attack(Player& InPlayer)
{
	InPlayer.SetHp(-_attackDamge);
	_CURRENT_MONSTER_ACTION = MonsterAction::Attack;
}




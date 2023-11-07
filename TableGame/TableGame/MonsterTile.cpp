#include "MonsterTile.h"
#include "MonsterSkeleton.h"
#include "MonsterBigFoot.h"
#include "MonsterCyclops.h"
#include "MonsterParasiticBat.h"

MonsterTile::MonsterTile(__int32 InPosX, __int32 InPosY, MonsterType InMonsterType):
	_posX(InPosX), _posY(InPosY), _monsterType(InMonsterType), _monster(nullptr), _isClear(false)
{
	if (nullptr == _monster)
		Initialize();
}

MonsterTile::~MonsterTile()
{
	delete _monster;
}

void MonsterTile::Initialize()
{
	if (nullptr != _monster)
		delete _monster;

	switch (_monsterType)
	{
	case MonsterType::Skeleton:
		_monster = static_cast<MonsterBase*>(new MonsterSkeleton(MonsterType::Skeleton));
		break;
	case MonsterType::Devil:
		_monster = static_cast<MonsterBase*>(new MonsterDevil(MonsterType::Devil));
		break;
	case MonsterType::BigFoot:
		_monster = static_cast<MonsterBase*>(new MonsterBigFoot(MonsterType::BigFoot));
		break;
	case MonsterType::Cyclops:
		_monster = static_cast<MonsterBase*>(new MonsterCyclops(MonsterType::Cyclops));
		break;
	case MonsterType::ParasiticBat:
		_monster = static_cast<MonsterBase*>(new MonsterParasiticBat(MonsterType::ParasiticBat));
		break;
	}
	_isClear = false;
}

void MonsterTile::Awake()
{

}

void MonsterTile::Start()
{
}

void MonsterTile::Update()
{
	__int32 playerPosX = GameManager::GetInstance().GetPlayer().GetPosX();
	__int32 playerPosY = GameManager::GetInstance().GetPlayer().GetPosY();
	if (playerPosX == _posX && playerPosY == _posY )
	{
		if (true == _isClear)
			return;
		if (true == _isRun)
			return;

		GameManager::GetInstance().ChangeGameMode(GameMode::BattleMode, this);
	}
	else
	{
		if (true == _isRun)
			_isRun = false;
	}
}

bool MonsterTile::GetIsClear() const
{
	return _isClear;
}

bool MonsterTile::GetIsRun() const
{
	return _isRun;
}

void MonsterTile::SetIsClear(bool InIsClear)
{
	_isClear = InIsClear;
}

void MonsterTile::SetIsRun(bool InIsRun)
{
	_isRun = InIsRun;
}

MonsterBase* MonsterTile::GetMonster() const
{
	return _monster;
}

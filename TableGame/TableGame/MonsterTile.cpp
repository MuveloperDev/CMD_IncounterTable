#include "MonsterTile.h"
#include "MonsterSkeleton.h"
#include "MonsterBigFoot.h"
#include "MonsterCyclops.h"
#include "MonsterParasiticBat.h"

MonsterTile::MonsterTile(__int32 InPosX, __int32 InPosY, MonsterType InMonsterType):
	_posX(InPosX), _posY(InPosY), _monsterType(InMonsterType), _monster(nullptr), _isClear(false)
{}

MonsterTile::~MonsterTile()
{
	delete _monster;
}

void MonsterTile::Initialize()
{
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
	Initialize();
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
		//Utility::GetInstance().SetCursorPosition(0, 4);
		//std::cout << "BattleMode";
	}
	else
	{
		if (true == _isRun)
			_isRun = false;
	}
	//switch (_monsterType)
	//{
	//case MonsterType::Skeleton:
	//	Utility::GetInstance().SetCursorPosition(0, 0);
	//	std::cout << "Sekeleton";
	//	break;
	//case MonsterType::Devil:
	//	Utility::GetInstance().SetCursorPosition(0, 1);
	//	std::cout << "Devil";
	//	break;
	//case MonsterType::Skull:
	//	Utility::GetInstance().SetCursorPosition(0, 2);
	//	std::cout << "Skull";
	//	break;
	//case MonsterType::ParasiticBat:
	//	Utility::GetInstance().SetCursorPosition(0, 3);
	//	std::cout << "Bat";
	//	break;
	//default:
	//	break;
	//}
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

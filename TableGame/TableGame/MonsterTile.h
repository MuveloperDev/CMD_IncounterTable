#pragma once

#include "TableGame.h"
#include "MonsterBase.h"
#include "MonsterDevil.h"

class MonsterBase;
class MonsterDevil;
class MonsterTile
{
public:
	MonsterTile(__int32 InPosX, __int32 InPosY, MonsterType InMonsterType);
	~MonsterTile();
	void Initialize();
	void Awake();
	void Start();
	void Update();
	bool GetIsClear() const;
	bool GetIsRun() const;
	void SetIsClear(bool InIsClear);
	void SetIsRun(bool InIsRun);
	MonsterBase* GetMonster() const;
private:
	__int32 _posX;
	__int32 _posY;
	bool _isClear;
	bool _isRun;
	MonsterType _monsterType;
	MonsterBase* _monster;
};


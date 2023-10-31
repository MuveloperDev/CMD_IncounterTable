#pragma once
#include "TableGame.h"
#include "MonsterTile.h"
#include "MonsterBase.h"
class BattleManager
{
public:
	BattleManager();
	~BattleManager();
	void Awake();
	void Start();
	void Update();
	void Render();
	void LateUpdateAfterRender();
	void SetTargetMonster(MonsterTile* InTargetTile);
	MonsterTile& GetTargetTile();
	MonsterBase& GetTargetMonster();
	void SetBattlePage(BattlePage InBattlePage);
private:

	bool _isRun;
	std::string _pointShape;
	MonsterTile* _targetTile;
	MonsterBase* _targetMonster;
	BattlePage _CURRENT_BATTLEPAGE;
	PlayerChoiceListBattleMode _CURRENT_CHOICE_LIST;
	std::default_random_engine generator;
	PlayerInputBattleMode _PLAYER_INPUT;
	HANDLE _hConsole;

private:
	void Initialize();
	void PrintMonsterShape();
	void PrintSelectList();
	void PrintMonsterStatus();
	
	void PrintCurrentBattlePage();
	void PrintChoiceList();
	void PrintMonsterAction();
	void PrintPlayerAction();
	void CheckClear();
	void PlayerChoiceProcess();
	void PlayerLateUpdate();
};


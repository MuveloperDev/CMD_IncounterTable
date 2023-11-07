#pragma once
#include "TableGame.h"
#include <thread>
#include <future>
#include "UnReDoManager.h"
class Player;
class TableBoard;
class EscapeTile;
class MonsterMapManager;
class BattleManager;
class MonsterTile;
class InventoryManager;
class ShopManager;
class UnReDoManager;
class OptionManager;
class SaveLoadManager;
class GameManager
{

public:

	static GameManager& GetInstance();
	void Awake();
	void Start();
	void Update();
	void Render();
	//void AfterRender
	void ChangeScene(Scene InScene);
	void ChangeGameMode(GameMode InGameMode, MonsterTile* _targetTile);
	void PuaseMusic();
	void StartMusic();
	void SetDifficult(Difficult InDifficult);
	bool IsPuaseMusic() const;
	__int32 GetTableSizeX() const;
	__int32 GetTableSizeY() const;
	GameMode GetCurrentGameMode() const;
	GameMode GetPrevGameMode() const;
	Scene GetCurrentScene() const;
	Player& GetPlayer() const;
	EscapeTile& GetEscapeTile() const;
	BattleManager& GetBattleManager() const;
	MonsterMapManager& GetMonsterMapManager() const;
	InventoryManager& GetInventoryManager() const;
	ShopManager & GetShopManager() const;
	UnReDoManager & GetUnReDoManager() const;
	OptionManager & GetOptionManager() const;
	SaveLoadManager& GetSaveLoadManager() const;
	std::default_random_engine GetRandomGenerator();
	Difficult GetDifficult();
private:
	GameManager();
	~GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	static void customDeleter(GameManager* gm);
	// decltype(&customDeleter)는 uniqueptr이 해제될때 자동으로 소멸자에 접근하는데 
	// 이때 소멸자가 private이라 에러가 발생하게된다.
	// 이때 customdeleter로 접근을 막고 별도로 customdeleter에서 동적으로 할당된 객체들의 메모리 해제처리를 한다.
	static std::unique_ptr<GameManager, decltype(&customDeleter)> _instance;
	static std::once_flag initInstanceFlag;
	static void InitSingleton();

	const __int32 _TABLE_SIZE_X;
	const __int32 _TABLE_SIZE_Y;
	bool _isPuaseMusic;
	Difficult _difficult;
	Player* _player;
	TableBoard* _tableBoard;
	EscapeTile* _escapeTile;
	MonsterMapManager* _monsterMapManager;
	BattleManager* _battleManager;
	InventoryManager* _inventoryManager;
	ShopManager* _shopManager;
	UnReDoManager* _unReDoManager;
	OptionManager* _optionManager;
	SaveLoadManager* _saveLoadManager;
	GameMode _CURRENT_GAME_MODE;
	GameMode _PREV_GAME_MODE;
	Scene _CURRENT_SCENE;
	std::default_random_engine generator;
	std::map<GameMode, std::vector<int>> freqsMap;
	std::future<void> asyncMusic;
	std::mutex mtx;
	void PrintCurrentMode();
	void Music();
};


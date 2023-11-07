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
	// decltype(&customDeleter)�� uniqueptr�� �����ɶ� �ڵ����� �Ҹ��ڿ� �����ϴµ� 
	// �̶� �Ҹ��ڰ� private�̶� ������ �߻��ϰԵȴ�.
	// �̶� customdeleter�� ������ ���� ������ customdeleter���� �������� �Ҵ�� ��ü���� �޸� ����ó���� �Ѵ�.
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


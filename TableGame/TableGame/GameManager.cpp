#include "GameManager.h"

// �̱��� Ŭ���� �ν��Ͻ��� ���������� ���� ������ �Ѵ�.
// C++���� ���������� ���α׷� ���� ������ �ʱ�ȭ�Ǹ�, �� �ʱ�ȭ �ڵ�� ���� �ҽ������� ���������� �ۼ��ȴ�.
//�ݸ鿡 �����ڴ� ��ü�� ������ �� ȣ��ǹǷ�, 
//�� ��ġ���� std::unique_ptr�� �ʱ�ȭ�Ϸ��� ���� GameManager ��ü�� �����ؾ� �մϴ�.
//�׷��� �̱��� ���Ͽ����� ��ü ������ �����ϱ� ���� �����ڸ� private���� ����� �ܺο��� ���� ȣ���� �� ���� �մϴ�.
//���� �� ��쿡�� std::unique_ptr�� ������ ���ο��� �ʱ�ȭ�� �� �����ϴ�.
//���� �� �κ��� ���α׷� ���� ������ ����ǵ��� �ҽ� ������ ���� ������ �ۼ��ϴ� ���� ���� �����ϴ�.

std::unique_ptr<GameManager, decltype(&GameManager::customDeleter)>
GameManager::_instance(nullptr, &GameManager::customDeleter);
std::once_flag GameManager::initInstanceFlag;

GameManager::GameManager() : 
	_difficult(Difficult::Normal),
	_player(new Player(_TABLE_SIZE_X, _TABLE_SIZE_Y)),
	_tableBoard(new TableBoard(_TABLE_SIZE_X, _TABLE_SIZE_Y)),
	_escapeTile(new EscapeTile(_TABLE_SIZE_X, _TABLE_SIZE_Y)),
	_inventoryManager(new InventoryManager()),
	_monsterMapManager(new MonsterMapManager(_TABLE_SIZE_X, _TABLE_SIZE_Y, static_cast<int>(_difficult))),
	_shopManager(new ShopManager(_TABLE_SIZE_X, _TABLE_SIZE_Y, static_cast<int>(_difficult))),
	_TABLE_SIZE_X(20), _TABLE_SIZE_Y(20), _CURRENT_GAME_MODE(GameMode::None),
	_CURRENT_SCENE(Scene::None), _battleManager(new BattleManager()),_PREV_GAME_MODE(GameMode::None)
{
	// ���α׷��� ������� ȯ�� �������� ������ �������� ���
	//�� �������� ���ڿ� ��, ��ҹ��� ��ȯ �� �پ��� �۾��� ������ ��ġ��, ���⿡�� wide character ��µ� ���Եȴ�.
	//std::locale::global(std::locale(""));
	setlocale(LC_ALL, "");
	Utility::GetInstance().SetCursorInvisible();

}

GameManager::~GameManager(){}

void GameManager::customDeleter(GameManager* gm)
{
	delete gm->_player;
	delete gm->_tableBoard;
}

void GameManager::InitSingleton()
{
	_instance.reset(new GameManager);
}

void GameManager::PrintCurrentMode()
{
	switch (_CURRENT_GAME_MODE)
	{
	case GameMode::None:
		std::cout << "GAME MODE : NONE";
		break;
	case GameMode::TableMode:
		std::cout << "GAME MODE : TABLE MODE";
		break;
	case GameMode::BattleMode:
		std::cout << "GAME MODE : BATTLE MODE";
		break;
	}
}


GameManager& GameManager::GetInstance()
{
	std::call_once(initInstanceFlag, &GameManager::InitSingleton);
	return *_instance;
}

void GameManager::Awake()
{
	_CURRENT_GAME_MODE = GameMode::TableMode;
	_monsterMapManager->Awake();
	_tableBoard -> Awake();
	_player -> Awake();
	_inventoryManager->Awake();
	_shopManager->Awake();
}

void GameManager::Start()
{
	_monsterMapManager->Start();
	_tableBoard->Start();
	_player->Start();
	_inventoryManager->Start();
	_shopManager->Start();
}

void GameManager::Update()
{
	switch (_CURRENT_GAME_MODE)
	{
	case GameMode::None:
		break;
	case GameMode::TableMode:
		_player->Update();
		_monsterMapManager->Update();
		_tableBoard->Update();
		_shopManager->IsPlayerOnShop();
		_escapeTile->Update();
		break;
	case GameMode::BattleMode:
		_player->InitCurrentBattleInput();
		_player->Update();
		_battleManager->Update();
		break;
	case GameMode::InventoryMode:
		_player->InitCurrentBattleInput();
		_player->Update();
		_inventoryManager->Update();
		break;
	case GameMode::ShopMode:
		_player->InitCurrentBattleInput();
		_player->Update();
		_shopManager->Update();
		break;
	}

}

void GameManager::Render()
{
	switch (_CURRENT_GAME_MODE)
	{
	case GameMode::None:
		break;
	case GameMode::TableMode:
		Utility::GetInstance().PrintTopLine();
		Utility::GetInstance().PrintVerticalLine(30);
		GameManager::GetInstance().GetPlayer().PrintPlayerStatus(false);
		_tableBoard->Render();
		Utility::GetInstance().PrintVerticalLine(88);
		Utility::GetInstance().PrintBottomLine();
		_inventoryManager->SimpleUI();
		break;
	case GameMode::BattleMode:
		_battleManager->Render();
		Utility::GetInstance().SetCursorPosition(80,26);
		break;
	case GameMode::InventoryMode:
		_inventoryManager->Render();
		break;
	case GameMode::ShopMode:
		_shopManager->Render();
		break;
	}

	
}

GameMode GameManager::GetCurrentGameMode() const
{
	return _CURRENT_GAME_MODE;
}

GameMode GameManager::GetPrevGameMode() const
{
	return _PREV_GAME_MODE;
}

Scene GameManager::GetCurrentScene() const
{
	return _CURRENT_SCENE;
}

void GameManager::ChangeScene(Scene InScene)
{
	_CURRENT_SCENE = InScene;
}

void GameManager::ChangeGameMode(GameMode InGameMode, MonsterTile* _targetTile)
{
	_PREV_GAME_MODE = _CURRENT_GAME_MODE;
	_CURRENT_GAME_MODE = InGameMode;
	Utility::GetInstance().ClearCmd();
	switch (InGameMode)
	{
	case GameMode::None:
		break;
	case GameMode::TableMode:
		_battleManager->SetBattlePage(BattlePage::None);
		break;
	case GameMode::BattleMode:
		if (nullptr != _targetTile)
		{
			_battleManager->SetTargetMonster(_targetTile);
		}
		_battleManager->SetBattlePage(BattlePage::Player);
		break;
	case GameMode::InventoryMode:
		break;
	case GameMode::ShopMode:
		break;
	}
}

__int32 GameManager::GetTableSizeX() const
{
	return _TABLE_SIZE_X;
}

__int32 GameManager::GetTableSizeY() const
{
	return _TABLE_SIZE_Y;
}

Player& GameManager::GetPlayer() const
{
	return *_player;
}

EscapeTile& GameManager::GetEscapeTile() const
{
	return *_escapeTile;
}

BattleManager& GameManager::GetBattleManager() const
{
	return *_battleManager;
}

MonsterMapManager& GameManager::GetMonsterMapManager() const
{
	return *_monsterMapManager;
}

ShopManager& GameManager::GetShopManager() const
{
	return *_shopManager;
}

std::default_random_engine GameManager::GetRandomGenerator()
{
	return generator;
}

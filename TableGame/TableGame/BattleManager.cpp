#include "BattleManager.h"

BattleManager::BattleManager() :
	_targetMonster(nullptr), _targetTile(nullptr),
	_CURRENT_BATTLEPAGE(BattlePage::None), _CURRENT_CHOICE_LIST(PlayerChoiceListBattleMode::None),
	_pointShape("¢¹"), _PLAYER_INPUT(PlayerInputBattleMode::None), _isRun(false),
	_hConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{
}

BattleManager::~BattleManager()
{
}

void BattleManager::Awake()
{
}

void BattleManager::Start()
{
}

void BattleManager::Update()
{
	switch (_CURRENT_BATTLEPAGE)
	{
	case BattlePage::None:
		break;
	case BattlePage::Player:
	{
		_PLAYER_INPUT = GameManager::GetInstance().GetPlayer().GetCurrentInputBattleMode();
		switch (_PLAYER_INPUT)
		{
		case PlayerInputBattleMode::None:
			break;
		case PlayerInputBattleMode::Up:
		{
			if (PlayerChoiceListBattleMode::Attack == _CURRENT_CHOICE_LIST)
				return;
			__int32 ChoiceNum = static_cast<__int32> (_CURRENT_CHOICE_LIST);
			ChoiceNum -= 1;
			_CURRENT_CHOICE_LIST = static_cast<PlayerChoiceListBattleMode>(ChoiceNum);
			break;
		}
		case PlayerInputBattleMode::Down:
		{
			if (PlayerChoiceListBattleMode::Run == _CURRENT_CHOICE_LIST)
				return;
			__int32 ChoiceNum = static_cast<__int32> (_CURRENT_CHOICE_LIST);
			ChoiceNum += 1;
			_CURRENT_CHOICE_LIST = static_cast<PlayerChoiceListBattleMode>(ChoiceNum);
			break;
		}
		case PlayerInputBattleMode::Enter:
			PlayerChoiceProcess();
			break;
		}
		break;
	}
	case BattlePage::Monster:
		_targetMonster->Attack(GameManager::GetInstance().GetPlayer());
		break;
	default:
		break;
	}


}

void BattleManager::Render()
{

	Utility::GetInstance().PrintTopLine();
	Utility::GetInstance().PrintHirizontalLine(5);
	PrintMonsterShape();
	PrintMonsterStatus();
	
	GameManager::GetInstance().GetPlayer().PrintPlayerStatus(false);
	Utility::GetInstance().PrintHirizontalLine(24);
	PrintCurrentBattlePage();
	PrintChoiceList();
	switch (_CURRENT_BATTLEPAGE)
	{
	case BattlePage::None:
		break;
	case BattlePage::Player:
		PrintPlayerAction();
		break;
	case BattlePage::Monster:
		PrintMonsterAction();
		break;
	}
	Utility::GetInstance().PrintBottomLine();
	
	//__int32 playerPosX = GameManager::GetInstance().GetPlayer().GetPosX();
	//__int32 playerPosY = GameManager::GetInstance().GetPlayer().GetPosY();
	//Utility::GetInstance().SetCursorPosition(0, 25);
	//std::cout << "Player Pos X : " << playerPosX << " / " << playerPosY;
	LateUpdateAfterRender();
}

void BattleManager::LateUpdateAfterRender()
{
	switch (_CURRENT_BATTLEPAGE)
	{
	case BattlePage::None:
		break;
	case BattlePage::Player:
		PlayerLateUpdate();
		break;
	case BattlePage::Monster:
		
		Sleep(1000);
		_targetMonster->SetMonsterAction(MonsterAction::None);
		SetBattlePage(BattlePage::Player);
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		Utility::GetInstance().ClearCmd();
		break;
	}
}

void BattleManager::SetTargetMonster(MonsterTile* InTargetTile)
{
	_targetTile = InTargetTile;
	_targetMonster = InTargetTile->GetMonster();
}

MonsterTile& BattleManager::GetTargetTile()
{
	return *_targetTile;
}

MonsterBase& BattleManager::GetTargetMonster()
{
	return *_targetMonster;
}

void BattleManager::SetBattlePage(BattlePage InBattlePage)
{
	_CURRENT_BATTLEPAGE = InBattlePage;
	switch (InBattlePage)
	{
	case BattlePage::None:
		Initialize();
		break;
	case BattlePage::Player:
		break;
	case BattlePage::Monster:
		break;
	}
}

void BattleManager::PrintMonsterShape()
{
	Utility::GetInstance().SetCursorPosition(43, 2);
	std::cout << _targetMonster->GetMonsterShpae() << std::endl;

}

void BattleManager::PrintSelectList()
{
}

void BattleManager::PrintMonsterStatus()
{
	Utility::GetInstance().SetCursorPosition(95, 0);
	//std::cout << "================================" << std::endl;
	Utility::GetInstance().SetCursorPosition(95, 1);
	std::cout << "   [ " << _targetMonster->GetMonsterName() << " ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(95, 2);
	std::cout << "HP [ " << _targetMonster->GetHp() << "/" << _targetMonster->GetMaxHp() << " ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(95, 3);
	//std::cout << "================================" << std::endl;
}



void BattleManager::PrintCurrentBattlePage()
{
	Utility::GetInstance().SetCursorPosition(0, 26);
	switch (_CURRENT_BATTLEPAGE)
	{
	case BattlePage::None:
		std::cout << "BATTLE PAGE =[ NONE ]";
		break;
	case BattlePage::Player:
		std::cout << "BATTLE PAGE =[ PLAYER  ]";
		break;
	case BattlePage::Monster:
		std::cout << "BATTLE PAGE =[ MONSTER ]";
		break;
	}
}

void BattleManager::PrintChoiceList()
{
	Utility::GetInstance().SetCursorPosition(0, 25);
	switch (_CURRENT_CHOICE_LIST)
	{
	case PlayerChoiceListBattleMode::None:
		std::cout << "						      " << "[ ATTACK ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 26);
		std::cout << "						      " << "[ INVENTORY ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 27);
		std::cout << "						      " << "[ RUN ]" << std::endl;
		break;
	case PlayerChoiceListBattleMode::Attack:
		std::cout << "						    " << _pointShape << "[ ATTACK ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 26);
		std::cout << "						      " << "[ INVENTORY ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 27);
		std::cout << "						      " << "[ RUN ]" << std::endl;
		break;
	case PlayerChoiceListBattleMode::Inventory:
		std::cout << "						      " << "[ ATTACK ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 26);
		std::cout << "						    " << _pointShape << "[ INVENTORY ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 27);
		std::cout << "						      " << "[ RUN ]" << std::endl;
		break;
	case PlayerChoiceListBattleMode::Run:
		std::cout << "						      " << "[ ATTACK ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 26);
		std::cout << "						      " << "[ INVENTORY ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 27);
		std::cout << "						    " << _pointShape << "[ RUN ]" << std::endl;
		break;
	default:
		break;
	}
}

void BattleManager::CheckClear()
{
	__int32 hp = _targetMonster->GetHp();
	if (0 < hp)
		return;
	_targetTile->SetIsClear(true);
	_targetMonster->SetClear(true);
	GameManager::GetInstance().GetPlayer().SetGold(_targetMonster->GetGoldReward());
	GameManager::GetInstance().ChangeGameMode(GameMode::TableMode, nullptr);

}

void BattleManager::PlayerChoiceProcess()
{
	switch (_CURRENT_CHOICE_LIST)
	{
	case PlayerChoiceListBattleMode::None:
		break;
	case PlayerChoiceListBattleMode::Attack:
	{
		__int32 _playerAttackDamage = GameManager::GetInstance().GetPlayer().GetAttackDamage();
		_targetMonster->SetHp(-_playerAttackDamage);
		break;
	}
	case PlayerChoiceListBattleMode::Inventory:
		GameManager::GetInstance().ChangeGameMode(GameMode::InventoryMode, nullptr);
		break;
	case PlayerChoiceListBattleMode::Run:
	{
		std::uniform_int_distribution<int> distribution(1,3);
		__int32 random_number = distribution(generator);
		if (0 == random_number % 3)
		{
			_targetTile->SetIsRun(true);
			_isRun = true;
		}
		break;
	}
	}
}

void BattleManager::Initialize()
{
	_targetMonster = nullptr;
	_targetTile = nullptr;
	_CURRENT_CHOICE_LIST = PlayerChoiceListBattleMode::None;
	_PLAYER_INPUT = PlayerInputBattleMode::None;
	_isRun = false;
}

void BattleManager::PrintMonsterAction()
{
	Utility::GetInstance().SetCursorPosition(40, 2);
	MonsterAction action = _targetMonster->GetMonsterAction();
	switch (action)
	{
	case MonsterAction::None:
		Utility::GetInstance().ClearCmd();
		break;
	case MonsterAction::Attack:
		std::cout << _targetMonster->GetMonsterName()<< "is Attacked. - [ DAMAGE : " << _targetMonster->GetAttackDamage()<<" ]";
		break;
	case MonsterAction::Magic:
		break;
	case MonsterAction::Gaurd:
		break;
	}
	
}

void BattleManager::PrintPlayerAction()
{
	Utility::GetInstance().SetCursorPosition(40, 2);
	switch (_PLAYER_INPUT)
	{
	case PlayerInputBattleMode::None:
		break;
	case PlayerInputBattleMode::Up:
		break;
	case PlayerInputBattleMode::Down:
		break;
	case PlayerInputBattleMode::Enter:
		switch (_CURRENT_CHOICE_LIST)
		{
		case PlayerChoiceListBattleMode::None:
			break;
		case PlayerChoiceListBattleMode::Attack:
			std::cout << "PLAYER ATTACKED " << _targetMonster->GetMonsterName() << " - [ DAMAGE : " << GameManager::GetInstance().GetPlayer().GetAttackDamage() << " ]";
			break;
		case PlayerChoiceListBattleMode::Inventory:
			break;
		case PlayerChoiceListBattleMode::Run:
			if (true == _isRun)
			{
				Utility::GetInstance().SetCursorPosition(46, 2);
				std::cout << "< R U N - S U C C E S S E D >";
			}
			else
			{
				Utility::GetInstance().SetCursorPosition(47, 2);
				std::cout << "< R U N - F A I L E D >";
			}
			break;
		}
		break;
	default:
		break;
	}

}

void BattleManager::PlayerLateUpdate()
{
	switch (_PLAYER_INPUT)
	{
	case PlayerInputBattleMode::None:
		break;
	case PlayerInputBattleMode::Up:
		break;
	case PlayerInputBattleMode::Down:
		break;
	case PlayerInputBattleMode::Enter:
		Sleep(1000);
		if (true == _isRun)
		{
			GameManager::GetInstance().ChangeGameMode(GameMode::TableMode, nullptr);
			break;
		}
		Utility::GetInstance().ClearCmd();
		CheckClear();
		SetBattlePage(BattlePage::Monster);
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
		break;
	default:
		break;
	}
}

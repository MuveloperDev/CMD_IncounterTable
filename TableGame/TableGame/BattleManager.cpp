#include "BattleManager.h"

BattleManager::BattleManager() :
	_targetMonster(nullptr), _targetTile(nullptr),
	_CURRENT_BATTLEPAGE(BattlePage::None), _CURRENT_CHOICE_LIST(PlayerChoiceListBattleMode::Attack),
	_pointShape("¢¹"), _PLAYER_INPUT(PlayerInputSelectMode::None), _isRun(false),
	_hConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{
}

BattleManager::~BattleManager()
{
}

void BattleManager::Awake()
{
	Initialize();
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
		_PLAYER_INPUT = GameManager::GetInstance().GetPlayer().GetCurrentInputSelectMode();
		switch (_PLAYER_INPUT)
		{
		case PlayerInputSelectMode::None:
			break;
		case PlayerInputSelectMode::Up:
		{
			if (PlayerChoiceListBattleMode::Attack == _CURRENT_CHOICE_LIST)
			{
				_CURRENT_CHOICE_LIST = PlayerChoiceListBattleMode::Run;
				return;
			}
			__int32 ChoiceNum = static_cast<__int32> (_CURRENT_CHOICE_LIST);
			ChoiceNum -= 1;
			_CURRENT_CHOICE_LIST = static_cast<PlayerChoiceListBattleMode>(ChoiceNum);
			break;
		}
		case PlayerInputSelectMode::Down:
		{
			if (PlayerChoiceListBattleMode::Run == _CURRENT_CHOICE_LIST)
			{
				_CURRENT_CHOICE_LIST = PlayerChoiceListBattleMode::Attack;
				return;
			}
			__int32 ChoiceNum = static_cast<__int32> (_CURRENT_CHOICE_LIST);
			ChoiceNum += 1;
			_CURRENT_CHOICE_LIST = static_cast<PlayerChoiceListBattleMode>(ChoiceNum);
			break;
		}
		case PlayerInputSelectMode::Enter:
			PlayerChoiceProcess();
			break;
		}
		break;
	}
	case BattlePage::Monster:
		GameManager::GetInstance().PuaseMusic();
		_targetMonster->Attack(GameManager::GetInstance().GetPlayer());
		break;
	default:
		break;
	}


}

void BattleManager::Render()
{

	Utility::GetInstance().PrintHorizontalLine(2, 116, 5);
	switch (_PLAYER_INPUT)
	{
	case PlayerInputSelectMode::None:
	case PlayerInputSelectMode::Up:
	case PlayerInputSelectMode::Down:
		break;
	case PlayerInputSelectMode::Enter:
		switch (_CURRENT_CHOICE_LIST)
		{
		case PlayerChoiceListBattleMode::None:
			break;
		case PlayerChoiceListBattleMode::Attack:
			SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
			break;
		case PlayerChoiceListBattleMode::Inventory:
			break;
		case PlayerChoiceListBattleMode::Run:
			break;
		}
		break;
	}

	PrintMonsterShape();
	if (BattlePage::Player == _CURRENT_BATTLEPAGE)
	{
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	
	PrintMonsterStatus();
	GameManager::GetInstance().GetPlayer().PrintPlayerStatus(false);
	Utility::GetInstance().PrintHorizontalLine(2, 116, 24);
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
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		PrintMonsterAction();
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
		break;
	}

	Utility::GetInstance().PrintComment(_isSelectInventory, 82, 8, "Monsters don't wait for you to act");
	Utility::GetInstance().PrintFrame();
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
		if (true == GameManager::GetInstance().IsPuaseMusic())
		{
			Beep(100, 500);
		}
		Sleep(1000);
		if (true == GameManager::GetInstance().IsPuaseMusic())
		{
			GameManager::GetInstance().StartMusic();
		}
		_targetMonster->SetMonsterAction(MonsterAction::None);
		SetBattlePage(BattlePage::Player);
		
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
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case BattlePage::Monster:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
		break;
	}
}

void BattleManager::PrintMonsterShape()
{
	MonsterType type = _targetMonster->GetMonsterType();
	switch (type)
	{
	case MonsterType::Skeleton:
	case MonsterType::Devil:
	case MonsterType::BigFoot:
	case MonsterType::Cyclops:
	case MonsterType::ParasiticBat:
		Utility::GetInstance().PrintShape(43, 2, _targetMonster->GetMonsterShpae());
		break;
	case MonsterType::Dragon:
		Utility::GetInstance().PrintShape(21, 2, _targetMonster->GetMonsterShpae());
		break;
	}

}

void BattleManager::PrintSelectList()
{
}

void BattleManager::PrintMonsterStatus()
{
	Utility::GetInstance().PrintVerticalLine(91, 1, 4);
	switch (_CURRENT_BATTLEPAGE)
	{
	case BattlePage::None:
		break;
	case BattlePage::Player:
		switch (_PLAYER_INPUT)
		{
		case PlayerInputSelectMode::None:
		case PlayerInputSelectMode::Up:
		case PlayerInputSelectMode::Down:
			break;
		case PlayerInputSelectMode::Enter:
			SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
			break;
		}
		break;
	case BattlePage::Monster:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
		
	Utility::GetInstance().SetCursorPosition(95, 0);
	//std::cout << "================================" << std::endl;
	Utility::GetInstance().SetCursorPosition(100, 1);
	std::cout << "[ " << _targetMonster->GetMonsterName() << " ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(99, 2);
	std::cout << "HP [ " << _targetMonster->GetHp() << "/" << _targetMonster->GetMaxHp() << " ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(95, 3);
	//std::cout << "================================" << std::endl;
	switch (_CURRENT_BATTLEPAGE)
	{
	case BattlePage::None:
		break;
	case BattlePage::Player:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case BattlePage::Monster:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
		break;
	}	
}



void BattleManager::PrintCurrentBattlePage()
{
	Utility::GetInstance().PrintVerticalLine(26, 25, 27);
	Utility::GetInstance().SetCursorPosition(2, 26);
	switch (_CURRENT_BATTLEPAGE)
	{
	case BattlePage::None:
		std::cout << "BATTLE PAGE =[ NONE ]";
		break;
	case BattlePage::Player:
		std::cout << "BATTLE PAGE =[ PLAYER  ]";
		break;
	case BattlePage::Monster:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "BATTLE PAGE =[ MONSTER ]";
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED);
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
		if (BattlePage::Player == _CURRENT_BATTLEPAGE)
		{
			Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
		}
		std::cout << "						    " << _pointShape << "[ ATTACK ]" << std::endl;
		if (BattlePage::Player == _CURRENT_BATTLEPAGE)
		{
			Utility::GetInstance().ResetTextColor();
		}
		Utility::GetInstance().SetCursorPosition(0, 26);
		std::cout << "						      " << "[ INVENTORY ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 27);
		std::cout << "						      " << "[ RUN ]" << std::endl;
		break;
	case PlayerChoiceListBattleMode::Inventory:
		std::cout << "						      " << "[ ATTACK ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 26);
		if (BattlePage::Player == _CURRENT_BATTLEPAGE)
		{
			Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
		}
		std::cout << "						    " << _pointShape << "[ INVENTORY ]" << std::endl;
		if (BattlePage::Player == _CURRENT_BATTLEPAGE)
		{
			Utility::GetInstance().ResetTextColor();
		}
		Utility::GetInstance().SetCursorPosition(0, 27);
		std::cout << "						      " << "[ RUN ]" << std::endl;
		break;
	case PlayerChoiceListBattleMode::Run:
		std::cout << "						      " << "[ ATTACK ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 26);
		std::cout << "						      " << "[ INVENTORY ]" << std::endl;
		Utility::GetInstance().SetCursorPosition(0, 27);
		if (BattlePage::Player == _CURRENT_BATTLEPAGE)
		{
			Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
		}
		std::cout << "						    " << _pointShape << "[ RUN ]" << std::endl;
		if (BattlePage::Player == _CURRENT_BATTLEPAGE)
		{
			Utility::GetInstance().ResetTextColor();
		}
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
	SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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
		GameManager::GetInstance().PuaseMusic();
		__int32 _playerAttackDamage = GameManager::GetInstance().GetPlayer().GetAttackDamage();
		_targetMonster->SetHp(-_playerAttackDamage);
		Utility::GetInstance().ClearCmd();
		break;
	}
	case PlayerChoiceListBattleMode::Inventory:
		GameManager::GetInstance().ChangeGameMode(GameMode::InventoryMode, nullptr);
		_isSelectInventory = true;
		break;
	case PlayerChoiceListBattleMode::Run:
	{
		MonsterType type = _targetMonster->GetMonsterType();
		switch (type)
		{
		case MonsterType::Skeleton:
		case MonsterType::Devil:
		case MonsterType::BigFoot:
		case MonsterType::Cyclops:
		case MonsterType::ParasiticBat:
		{
			std::uniform_int_distribution<int> distribution(1, 3);
			__int32 random_number = distribution(generator);
			if (0 == random_number % 3)
			{
				_targetTile->SetIsRun(true);
				_isRun = true;
			}
			break;
		}
		case MonsterType::Dragon: 
		{
			_isRun = false;
			break;
		}
		}
		break;
	}
	}
}

void BattleManager::Initialize()
{
	_targetMonster = nullptr;
	_targetTile = nullptr;
	_CURRENT_CHOICE_LIST = PlayerChoiceListBattleMode::Attack;
	_PLAYER_INPUT = PlayerInputSelectMode::None;
	_CURRENT_BATTLEPAGE = BattlePage::None;
	_isRun = false;
	SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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
	case PlayerInputSelectMode::None:
		break;
	case PlayerInputSelectMode::Up:
		break;
	case PlayerInputSelectMode::Down:
		break;
	case PlayerInputSelectMode::Enter:
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
				Utility::GetInstance().ChangeTextColor(TextColors::Green, true);
				std::cout << "< R U N - S U C C E S S E D >";
				Utility::GetInstance().ResetTextColor();
			}
			else
			{
				Utility::GetInstance().SetCursorPosition(47, 2);
				Utility::GetInstance().ChangeTextColor(TextColors::Red, true);
				std::cout << "< R U N - F A I L E D >";
				Utility::GetInstance().ResetTextColor();
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
	case PlayerInputSelectMode::None:
		if (true == _isSelectInventory)
		{
			_isSelectInventory = false;
		}
		break;
	case PlayerInputSelectMode::Up:
		break;
	case PlayerInputSelectMode::Down:
		break;
	case PlayerInputSelectMode::Enter:
		if (true == GameManager::GetInstance().IsPuaseMusic())
		{
			Beep(100, 500);
		}
		Sleep(1000);
		if (true == GameManager::GetInstance().IsPuaseMusic())
		{
			GameManager::GetInstance().StartMusic();
		}
		if (true == _isRun)
		{
			GameManager::GetInstance().ChangeGameMode(GameMode::TableMode, nullptr);
			break;
		}
		Utility::GetInstance().ClearCmd();
		SetBattlePage(BattlePage::Monster);
		CheckClear();
		break;
	default:
		break;
	}
}

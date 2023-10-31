#include "Player.h"

Player::Player(__int32 InTableSizeX, __int32 InTableSizeY) :
	_shape(L'◎'), 
	_posX(0), _posY(0), 
	isKeyDown(false),
	_TABLE_SIZE_X(InTableSizeX), _TABLE_SIZE_Y(InTableSizeY),
	_maxHp(100), _hp(_maxHp), _attackDamge(10), _gold(0),
	_CURRENTINPUT(PlayerInputBattleMode::None)
{
	std::cout << "_Player Init \n";
}

Player::~Player()
{
}

void Player::Awake()
{
	Initialize();
}

void Player::Start()
{
}

void Player::Update()
{ 
	GameMode _currentGameMode = GameManager::GetInstance().GetCurrentGameMode();
	switch (_currentGameMode)
	{
	case GameMode::None:
		break;
	case GameMode::TableMode:
		Move();
		break;
	case GameMode::BattleMode:
	case GameMode::InventoryMode:
	case GameMode::ShopMode:
		BattleInput();
		break;
	default:
		break;
	}

}

void Player::Render()
{
	std::wcout << GetShape();
}

__int32 Player::GetPosX()
{
	return _posX;
}

__int32 Player::GetPosY()
{
	return _posY;
}

const wchar_t Player::GetShape() const
{
	return _shape;
}

void Player::Test()
{
	std::cout<<"_Player Create \n";
}

void Player::InitCurrentBattleInput()
{
	_CURRENTINPUT = PlayerInputBattleMode::None;
}

PlayerInputBattleMode Player::GetCurrentInputBattleMode()
{
	return _CURRENTINPUT;
}

__int32 Player::GetHp() const
{
	return _hp;
}

__int32 Player::GetMaxHp() const
{
	return _maxHp;
}

__int32 Player::GetAttackDamage() const
{
	return _attackDamge;
}

__int32 Player::GetGold() const
{
	return _gold;
}

void Player::SetHp(__int32 InDamage)
{
	_hp += InDamage;
	if (0 > _hp)
	{
		_hp = 0;
	}
	else if (_hp > _maxHp)
	{
		_hp = _maxHp;
	}
}

void Player::SetAttackDamage(__int32 InAddDamage)
{
	_attackDamge += InAddDamage;
}

void Player::SetGold(__int32 InAddGold)
{
	_gold += InAddGold;
}

void Player::SetPosX(__int32 InX)
{
	_posX += InX;
}

void Player::SetPosY(__int32 InY)
{
	_posY += InY;
}

void Player::Initialize()
{
	_posX = 0; 
	_posY = 0;
	_maxHp = 100;
	_hp = _maxHp;
	_attackDamge = 10;
	_gold = 0;
}

void Player::Move()
{
	SHORT rightState = GetAsyncKeyState(VK_RIGHT);
	SHORT leftState = GetAsyncKeyState(VK_LEFT);
	SHORT uptState = GetAsyncKeyState(VK_UP);
	SHORT downState = GetAsyncKeyState(VK_DOWN);
	bool isRight = (rightState & 0x8000) != 0;
	bool isLeft = (leftState & 0x8000) != 0;
	bool isUp = (uptState & 0x8000) != 0;
	bool isDown = (downState & 0x8000) != 0;

	if (isRight || isLeft || isUp || isDown)
	{
		if (isKeyDown == false)
		{
			if (isRight)
			{
				if (_TABLE_SIZE_X <= _posX +1)
					return;

				_posX++;
			}
			if (isLeft)
			{
				if (0 > _posX -1)
					return;

				_posX--;
			}
			if (isUp)
			{
				if (0 > _posY -1)
					return;

				_posY--;
			}
			if (isDown)
			{
				if (_TABLE_SIZE_Y <= _posY +1)
					return;

				_posY++;
			}
		}
		isKeyDown = true;
	}
	else
	{
		isKeyDown = false;
	}
}

void Player::BattleInput()
{
	SHORT uptState = GetAsyncKeyState(VK_UP);
	SHORT downState = GetAsyncKeyState(VK_DOWN);
	SHORT enterState = GetAsyncKeyState(VK_RETURN);

	bool isUp = (uptState & 0x8000) != 0;
	bool isDown = (downState & 0x8000) != 0;
	bool isEnter = (enterState & 0x8000) != 0;

	if (isUp || isDown || isEnter)
	{
		if (isKeyDown == false)
		{
			if (isUp)
			{
				_CURRENTINPUT = PlayerInputBattleMode::Up;
			}
			if (isDown)
			{
				_CURRENTINPUT = PlayerInputBattleMode::Down;
			}
			if (isEnter)
			{
				_CURRENTINPUT = PlayerInputBattleMode::Enter;
				//GameManager::GetInstance().ChangeGameMode(GameMode::TableMode, nullptr);
				//GameManager::GetInstance().GetBattleManager().GetTargetTile().SetIsClear(true);
			}
		}
		isKeyDown = true;
	}
	else
	{
		isKeyDown = false;
	}
}
void Player::PrintPlayerStatus(bool InisFrame)
{
	if (true == InisFrame)
	{
		Utility::GetInstance().SetCursorPosition(1, 0);
		std::cout << "================================" << std::endl;
	}
	Utility::GetInstance().SetCursorPosition(1, 1);
	std::cout << "[ S T A T U S ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(1, 2);
	std::cout << "HP [ " << GameManager::GetInstance().GetPlayer().GetHp() << "/" << GameManager::GetInstance().GetPlayer().GetMaxHp() << " ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(1, 3);
	std::cout << "POWER [ " << GameManager::GetInstance().GetPlayer().GetAttackDamage() << " ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(1, 4);
	std::cout << "GOLD [ " << GameManager::GetInstance().GetPlayer().GetGold() << " ]" << std::endl;
	if (true == InisFrame)
	{
		Utility::GetInstance().SetCursorPosition(1, 5);
		std::cout << "================================";
	}
}
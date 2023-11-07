#include "Player.h"

Player::Player(__int32 InTableSizeX, __int32 InTableSizeY) :
	_shape(L'◎'), 
	_posX(0), _posY(0), 
	isKeyDown(false),
	_TABLE_SIZE_X(InTableSizeX), _TABLE_SIZE_Y(InTableSizeY),
	_maxHp(100), _hp(_maxHp), _attackDamge(10), _gold(0),
	_CURRENTINPUT(PlayerInputSelectMode::None),
	_playerDefaultShape(R"(
      _,.
    ,` -.)
   ( _/-\\-._
  /,|`--._,-^|            ,
  \_| |`-._/||          ,'|
    |  `-, / |         /  /
    |     || |        /  /
     `r-._||/   __   /  /
 __,-<_     )`-/  `./  /
'  \   `---'   \   /  /
    |           |./  /
    /           //  /
\_/' \         |/  /
 |    |   _,^-'/  /
 |    , ``  (\/  /_
  \,.->._    \X-=/^
  (  /   `-._//^`
   `Y-.____(__}
    |     {__)
          ()
)"),
_playerShopShape(R"(
        {}
       .--.
      /.--.\
      |====|
      |`::`|
  .-;`\..../`;-.
 /  |...::...|  \
|   /'''::'''\   |
;--'\   ::   /\--;
<__>,>._::_.<,<__>
|  |/   ^^   \|  |
\::/|        |\::/
|||\|        |/|||
''' |___/\___| '''
     \_ || _/
     <_ >< _>
     |  ||  |
     |  ||  |
    _\.:||:./_
   /____/\____\
)")
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
	case GameMode::OptionMode:
	case GameMode::UnReDoMode:
	case GameMode::SaveLoadMode:
		SelectInput();
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
	_CURRENTINPUT = PlayerInputSelectMode::None;
}

void Player::InitCurrentTableInput()
{
	_CURRENT_TABLE_INPUT = PlayerInputTableMode::None;
}

PlayerInputSelectMode Player::GetCurrentInputSelectMode()
{
	return _CURRENTINPUT;
}

PlayerInputTableMode Player::GetCurrentInputTableMode()
{
	return _CURRENT_TABLE_INPUT;
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
	if (0 >= _hp)
	{
		_hp = 0;
		GameManager::GetInstance().ChangeScene(Scene::Lose);
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
	SHORT escapeState = GetAsyncKeyState(VK_ESCAPE);
	SHORT enterState = GetAsyncKeyState(VK_RETURN);
	bool isRight = (rightState & 0x8000) != 0;
	bool isLeft = (leftState & 0x8000) != 0;
	bool isUp = (uptState & 0x8000) != 0;
	bool isDown = (downState & 0x8000) != 0;
	bool isESC = (escapeState & 0x8000) != 0;
	bool isEnter = (enterState & 0x8000) != 0;

	if (isRight || isLeft || isUp || isDown || isESC || isEnter)
	{
		if (isKeyDown == false)
		{
			GameManager::GetInstance().GetUnReDoManager().SetUnDo();
			if (isRight)
			{
				if (_TABLE_SIZE_X <= _posX +1)
					return;
				_CURRENT_TABLE_INPUT = PlayerInputTableMode::Right;
				_posX++;
			}
			if (isLeft)
			{
				if (0 > _posX -1)
					return;
				_CURRENT_TABLE_INPUT = PlayerInputTableMode::Left;
				_posX--;
			}
			if (isUp)
			{
				if (0 > _posY -1)
					return;
				_CURRENT_TABLE_INPUT = PlayerInputTableMode::Up;
				_posY--;
			}
			if (isDown)
			{
				if (_TABLE_SIZE_Y <= _posY +1)
					return;
				_CURRENT_TABLE_INPUT = PlayerInputTableMode::Down;
				_posY++;
			}
			if (isESC)
			{
				_CURRENT_TABLE_INPUT = PlayerInputTableMode::ESC;
				GameManager::GetInstance().ChangeGameMode(GameMode::OptionMode, nullptr);
			}
			if (isEnter)
			{
				_CURRENT_TABLE_INPUT = PlayerInputTableMode::Enter;
			}
		}
		isKeyDown = true;
	}
	else
	{
		_CURRENT_TABLE_INPUT = PlayerInputTableMode::None;
		isKeyDown = false;
	}
}

void Player::SelectInput()
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
				_CURRENTINPUT = PlayerInputSelectMode::Up;
			}
			if (isDown)
			{
				_CURRENTINPUT = PlayerInputSelectMode::Down;
			}
			if (isEnter)
			{
				_CURRENTINPUT = PlayerInputSelectMode::Enter;
				//GameManager::GetInstance().ChangeGameMode(GameMode::TableMode, nullptr);
				//GameManager::GetInstance().GetBattleManager().GetTargetTile().SetIsClear(true);
			}
		}
		isKeyDown = true;
	}
	else
	{
		_CURRENTINPUT = PlayerInputSelectMode::None;
		isKeyDown = false;
	}
}
SavePlayerData Player::GetUnDoData()
{
	SavePlayerData data;
	data.hp = _hp;
	data.gold = _gold;
	data.attackDamge = _attackDamge;
	data.playerPosX = _posX;
	data.playerPosY = _posY;
	data._itemList = GameManager::GetInstance().GetInventoryManager().GetItemList();
	return data;
}

void Player::SetUnDoData(SavePlayerData InData)
{
	_hp = InData.hp;
	_gold = InData.gold;
	_attackDamge = InData.attackDamge;
	_posX = InData.playerPosX;
	_posY = InData.playerPosY;
	GameManager::GetInstance().GetInventoryManager().SetItemList(InData._itemList);
}

void Player::PrintPlayerStatus(bool InisFrame)
{
	if (true == InisFrame)
	{
		Utility::GetInstance().SetCursorPosition(3, 0);
		std::cout << "================================" << std::endl;
	}

	Utility::GetInstance().SetCursorPosition(3, 1);
	std::cout << "[ S T A T U S ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(3, 2);
	std::cout << "HP [ " << GameManager::GetInstance().GetPlayer().GetHp() << "/" << GameManager::GetInstance().GetPlayer().GetMaxHp() << " ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(3, 3);
	std::cout << "POWER [ " << GameManager::GetInstance().GetPlayer().GetAttackDamage() << " ]" << std::endl;
	Utility::GetInstance().SetCursorPosition(3, 4);
	std::cout << "GOLD [ " << GameManager::GetInstance().GetPlayer().GetGold() << " ]" << std::endl;
	if (true == InisFrame)
	{
		Utility::GetInstance().SetCursorPosition(3, 5);
		std::cout << "================================";
	}
	GameMode currentMode = GameManager::GetInstance().GetCurrentGameMode();
	switch (currentMode)
	{
	case GameMode::None:
		break;
	case GameMode::TableMode:
		Utility::GetInstance().PrintShape(1, 7, _playerDefaultShape);
		break;
	case GameMode::BattleMode:
		Utility::GetInstance().PrintVerticalLine(22, 1, 4);
		break;
	case GameMode::InventoryMode:
	case GameMode::ShopMode:
		Utility::GetInstance().PrintShape(2, 5, _playerShopShape);
		break;
	}

	


}
#include "OptionManager.h"

OptionManager::OptionManager():
	_titleShape(R"(
 _______    _______   _________  _________   _______    _       
(  ___  )  (  ____ )  \__   __/  \__   __/  (  ___  )  ( (    /|
| (   ) |  | (    )|     ) (        ) (     | (   ) |  |  \  ( |
| |   | |  | (____)|     | |        | |     | |   | |  |   \ | |
| |   | |  |  _____)     | |        | |     | |   | |  | (\ \) |
| |   | |  | (           | |        | |     | |   | |  | | \   |
| (___) |  | )           | |     ___) (___  | (___) |  | )  \  |
(_______)  |/            )_(     \_______/  (_______)  |/    )_)
                                                                
)"), _CURRENT_TARGET_OPTION(0), _pointShape("¢¹")
{
	for (__int32 i = 0; i < static_cast<int>(Options::Max); i++)
	{
		Options option = static_cast<Options>(i);
		_optionList.push_back(option);
	}
}

OptionManager::~OptionManager()
{
}

void OptionManager::Awake()
{
}

void OptionManager::Start()
{
}

void OptionManager::Update()
{
	UpdateCursor();
}

void OptionManager::Render()
{

	Utility::GetInstance().PrintShape(30, 1, _titleShape);
	PrintOptionList();
	Utility::GetInstance().PrintFrame();

}

void OptionManager::UpdateCursor()
{
	PlayerInputSelectMode playerInput = GameManager::GetInstance().GetPlayer().GetCurrentInputSelectMode();
	switch (playerInput)
	{
	case PlayerInputSelectMode::None:
		break;
	case PlayerInputSelectMode::Up:
	{
		if (-1 == _CURRENT_TARGET_OPTION - 1)
		{
			_CURRENT_TARGET_OPTION = _optionList.size() - 1;
			break;
		}
		_CURRENT_TARGET_OPTION--;
		break;
	}
	case PlayerInputSelectMode::Down:
	{
		if (_optionList.size() == _CURRENT_TARGET_OPTION + 1)
		{
			_CURRENT_TARGET_OPTION = 0;
			break;
		}
		_CURRENT_TARGET_OPTION++;
		break;
	}
	case PlayerInputSelectMode::Enter:
		ChoiceProcess();
		break;
	}
}

void OptionManager::ChoiceProcess()
{
	Options target = static_cast<Options>(_CURRENT_TARGET_OPTION);
	switch (target)
	{
	case Options::UndoRedo:
		GameManager::GetInstance().ChangeGameMode(GameMode::UnReDoMode, nullptr);
		break;
	case Options::SaveLoad:
		GameManager::GetInstance().ChangeGameMode(GameMode::SaveLoadMode, nullptr);
		break;
	case Options::Exit:
		GameManager::GetInstance().ChangeGameMode(GameMode::TableMode, nullptr);
		break;
	}
}

void OptionManager::PrintOptionList()
{
	__int32 adjust = 0;
	for (__int32 i = 0; i < _optionList.size(); i++)
	{
		Options option = static_cast<Options>(i);
		Utility::GetInstance().SetCursorPosition(50, 17 + i + adjust);
		switch (option)
		{
		case Options::UndoRedo:
			if (i == _CURRENT_TARGET_OPTION)
			{
				std::cout << _pointShape <<" [ UNDO & REDO ]" << std::endl;
				break;
			}
			std::cout << "   [ UNDO & REDO ]" << std::endl;
			break;
		case Options::SaveLoad:
			if (i == _CURRENT_TARGET_OPTION)
			{
				std::cout << _pointShape << " [ SAVE & LOAD ]" << std::endl;
				break;
			}
			std::cout << "   [ SAVE & LOAD ]" << std::endl;
			break;
		case Options::Exit:
			if (i == _CURRENT_TARGET_OPTION)
			{
				std::cout << _pointShape << " [ EXIT ]" << std::endl;
				break;
			}
			std::cout << "   [ EXIT ]" << std::endl;
			break;
		}
		adjust++;
	}
}

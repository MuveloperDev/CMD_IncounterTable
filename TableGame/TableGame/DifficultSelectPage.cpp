#include "DifficultSelectPage.h"
#include "GameManager.h"
#include "Player.h"

DifficultSelectPage::DifficultSelectPage(TitleScene* InTitleScene) :
	_CURRENT_TARGET_OPTION(0),
	_CURRENT_SELECTED_OPTION(GameManager::GetInstance().GetDifficult()),
	_pointShape("¢¹ "), isKeyDown(false),
	_titleShape(R"(
 ______  _________ _______  _______ _________ _______           _    _________
(  __  \ \__   __/(  ____ \(  ____ \\__   __/(  ____ \|\     /|( \   \__   __/
| (  \  )   ) (   | (    \/| (    \/   ) (   | (    \/| )   ( || (      ) (   
| |   ) |   | |   | (__    | (__       | |   | |      | |   | || |      | |   
| |   | |   | |   |  __)   |  __)      | |   | |      | |   | || |      | |   
| |   ) |   | |   | (      | (         | |   | |      | |   | || |      | |   
| (__/  )___) (___| )      | )      ___) (___| (____/\| (___) || (____/\| |   
(______/ \_______/|/       |/       \_______/(_______/(_______)(_______/)_(   
                                                                              
)"),
	_titleScene(InTitleScene)
{
	_optionList.push_back(Difficult::Easy);
	_optionList.push_back(Difficult::Normal);
	_optionList.push_back(Difficult::Hard);

	_CURRENT_SELECTED_OPTION = GameManager::GetInstance().GetDifficult();
}

DifficultSelectPage::~DifficultSelectPage()
{
}

void DifficultSelectPage::Update()
{
	UpdateCursor();
}

void DifficultSelectPage::Render()
{
	if (TitleMode::Difficult != _titleScene->GetMode())
		return;

	PrintSelectedOption();
	Utility::GetInstance().PrintShape(23, 4, _titleShape);
	Utility::GetInstance().SetCursorPosition(4, 27);
	std::cout << "[ ESC : CLOSE ]";
	PrintOptionList();
	Utility::GetInstance().PrintFrame();
}

void DifficultSelectPage::UpdateCursor()
{
	SHORT uptState = GetAsyncKeyState(VK_UP);
	SHORT downState = GetAsyncKeyState(VK_DOWN);
	SHORT enterState = GetAsyncKeyState(VK_RETURN);
	SHORT escapeState = GetAsyncKeyState(VK_ESCAPE);
	bool isUp = (uptState & 0x8000) != 0;
	bool isDown = (downState & 0x8000) != 0;
	bool isEnter = (enterState & 0x8000) != 0;
	bool isESC = (escapeState & 0x8000) != 0;
	if (isUp || isDown || isEnter || isESC)
	{
		if (isKeyDown == false)
		{
			if (isUp)
			{
				if (0 == _CURRENT_TARGET_OPTION)
				{
					_CURRENT_TARGET_OPTION = _optionList.size() - 1;
				}
				else _CURRENT_TARGET_OPTION--;
			}
			if (isDown)
			{
				if (_optionList.size() - 1 == _CURRENT_TARGET_OPTION)
				{
					_CURRENT_TARGET_OPTION = 0;
				}
				else _CURRENT_TARGET_OPTION++;
			}
			if (isEnter)
			{
				//GameManager::GetInstance().ChangeGameMode(GameMode::TableMode, nullptr);
				//GameManager::GetInstance().GetBattleManager().GetTargetTile().SetIsClear(true);
				ChoiceProcess();
			}
			if (isESC)
			{
				_titleScene->SetMode(TitleMode::Title);
			}
		}
		isKeyDown = true;
	}
	else
	{
		isKeyDown = false;
	}
}


void DifficultSelectPage::ChoiceProcess()
{
	Difficult target = _optionList[_CURRENT_TARGET_OPTION];
	switch (target)
	{
	case Difficult::Easy:
		GameManager::GetInstance().SetDifficult(Difficult::Easy);
		_CURRENT_SELECTED_OPTION = Difficult::Easy;
		break;
	case Difficult::Normal:
		GameManager::GetInstance().SetDifficult(Difficult::Normal);
		_CURRENT_SELECTED_OPTION = Difficult::Normal;
		break;
	case Difficult::Hard:
		GameManager::GetInstance().SetDifficult(Difficult::Hard);
		_CURRENT_SELECTED_OPTION = Difficult::Hard;
		break;
	}
	Utility::GetInstance().ClearCmd();
}

void DifficultSelectPage::PrintOptionList()
{
	__int32 adjust = 0;
	for (__int32 i = 0; i < _optionList.size(); i++)
	{
		Difficult target = _optionList[i];
		Utility::GetInstance().SetCursorPosition(50, 17 + i + adjust);
		switch (target)
		{
		case Difficult::Easy:
			if (i == _CURRENT_TARGET_OPTION)
			{
				Utility::GetInstance().ChangeTextColor(TextColors::Green, true, [this]() {
					std::cout << _pointShape << " [ EASY ]" << std::endl;
					});
				break;
			}
			std::cout << "    [ EASY ]" << std::endl;
			break;
		case Difficult::Normal:
			if (i == _CURRENT_TARGET_OPTION)
			{
				Utility::GetInstance().ChangeTextColor(TextColors::Green, true, [this]() {
					std::cout << _pointShape << " [ NORMAL ]" << std::endl;
					});
				break;
			}
			std::cout << "    [ NORMAL ]" << std::endl;
			break;
		case Difficult::Hard:
			if (i == _CURRENT_TARGET_OPTION)
			{
				Utility::GetInstance().ChangeTextColor(TextColors::Green, true, [this](){
					std::cout << _pointShape << " [ HARD ]" << std::endl;
					});
				break;
			}
			std::cout << "    [ HARD ]" << std::endl;
			break;
		}
		adjust++;
	}
}

void DifficultSelectPage::PrintSelectedOption()
{
	Utility::GetInstance().SetCursorPosition(70, 27);
	std::cout << "CURRENT_SELECTED_DIFFICULT : [ ";
	switch (_CURRENT_SELECTED_OPTION)
	{
	case Difficult::Easy:
		Utility::GetInstance().ChangeTextColor(TextColors::Green, true, [this]() {
			std::cout << "EASY";
			});
		break;
	case Difficult::Normal:
		Utility::GetInstance().ChangeTextColor(TextColors::Green, true, [this]() {
			std::cout << "NORMAL";
			});
		break;
	case Difficult::Hard:
		Utility::GetInstance().ChangeTextColor(TextColors::Green, true, [this]() {
			std::cout << "HARD";
			});
		break;
	}
	std::cout << " ]";
}

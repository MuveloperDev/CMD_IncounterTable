#include "SaveLoadManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Utility.h"
#include <iostream>
#include <chrono>
#include <ctime>

SaveLoadManager::SaveLoadManager():
	_CURRENT_SELECT_IDX(0), _pointerShape("¢¹"), _CURRENT_POPUP_SELECT_IDX(0),
	_CURRENT_SELECTED_IDX(0), _isOpenPopup(false),
	_titleShape(R"(
 _______    _______               _______           
(  ____ \  (  ___  )  |\     /|  (  ____ \          
| (    \/  | (   ) |  | )   ( |  | (    \/          
| (_____   | (___) |  | |   | |  | (__              
(_____  )  |  ___  |  ( (   ) )  |  __)             
      ) |  | (   ) |   \ \_/ /   | (                
/\____) |  | )   ( |    \   /    | (____/\          
\_______)  |/     \|     \_/     (_______/          
                                                    
   __      _          _______    _______    ______  
  /__\    ( \        (  ___  )  (  ___  )  (  __  \ 
 ( \/ )   | (        | (   ) |  | (   ) |  | (  \  )
  \  /    | |        | |   | |  | (___) |  | |   ) |
  /  \/\  | |        | |   | |  |  ___  |  | |   | |
 / /\  /  | |        | |   | |  | (   ) |  | |   ) |
(  \/  \  | (____/\  | (___) |  | )   ( |  | (__/  )
 \___/\/  (_______/  (_______)  |/     \|  (______/ 
                                                    
)")
{


}

SaveLoadManager::~SaveLoadManager()
{
}

void SaveLoadManager::Awake()
{
	Initialize();
}

void SaveLoadManager::Update()
{
	PlayerInputSelectMode playerInput = GameManager::GetInstance().GetPlayer().GetCurrentInputSelectMode();
	switch (playerInput)
	{
	case PlayerInputSelectMode::None:
		break;
	case PlayerInputSelectMode::Up:
	{
		if (true == _isOpenPopup)
		{
			if (-1 == _CURRENT_POPUP_SELECT_IDX - 1)
			{
				_CURRENT_POPUP_SELECT_IDX = static_cast<__int32> (SaveLoadPopup::Max) - 1;
				break;
			}
			_CURRENT_POPUP_SELECT_IDX--;
			break;
		}
		if (-1 == _CURRENT_SELECT_IDX - 1)
		{
			_CURRENT_SELECT_IDX = static_cast<__int32> (SaveLoadList::Max) - 1;
			break;
		}
		_CURRENT_SELECT_IDX--;
		break;
	}
	case PlayerInputSelectMode::Down:
	{
		if (true == _isOpenPopup)
		{
			if (_buttonList.size() == _CURRENT_POPUP_SELECT_IDX + 1)
			{
				_CURRENT_POPUP_SELECT_IDX = 0;
				break;
			}
			_CURRENT_POPUP_SELECT_IDX++;
			break;
		}
		if (static_cast<__int32> (SaveLoadList::Max) == _CURRENT_SELECT_IDX + 1)
		{
			_CURRENT_SELECT_IDX = 0;
			break;
		}
		_CURRENT_SELECT_IDX++;
		break;
	}
	case PlayerInputSelectMode::Enter:
		if (true == _isOpenPopup)
		{
			PopupChoiceProcess();
			break;
		}
		ChoiceProcess();
		break;
	}
}

void SaveLoadManager::Render()
{

	if (true == _isOpenPopup)
	{
		Utility::GetInstance().PrintVerticalLine(98, 3, 24);
		Utility::GetInstance().PrintVerticalLine(20, 3, 24);
		Utility::GetInstance().PrintHorizontalLine(22, 96, 3);
		Utility::GetInstance().PrintHorizontalLine(22, 96, 24);
		PopupRender();
		Utility::GetInstance().PrintFrame();
		return;
	}
	Utility::GetInstance().PrintShape(65, 5, _titleShape);
	__int32 adjust = 0;
	for (__int32 i = 0; i < static_cast<__int32> (SaveLoadList::Max); i++)
	{
		SaveLoadList target = static_cast<SaveLoadList>(i);
		Utility::GetInstance().SetCursorPosition(3, 5 + i + adjust);
		switch (target)
		{
		case SaveLoadList::Exit:
		{
			if (i == _CURRENT_SELECT_IDX)
			{
				std::cout << _pointerShape << " [ EXIT ]" << std::endl;
				break;
			}
			std::cout << "   [ EXIT ]" << std::endl;
			break;
		}
		default:
		{
			if (i == _CURRENT_SELECT_IDX)
			{
				std::cout << _pointerShape << " [ SAVE DATA SLOT "<< i +1 << ": " << _saveLoadList[i].fileInfo << " ]";
				break;
			}
			std::cout << "  " << " [ SAVE DATA SLOT " << i + 1 << ": " << _saveLoadList[i].fileInfo << " ]";
			break;
		}
		}
		adjust++;
	}

	Utility::GetInstance().PrintFrame();
}

void SaveLoadManager::Save(__int32 idx)
{
	SaveFileData data;
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	char buffer[26];
	ctime_s(buffer, sizeof(buffer), &currentTime);

	data.difficult = GameManager::GetInstance().GetDifficult();
	std::string fileInfoStr;
	data.fileInfo.append(ToStringFromDifficult());
	data.fileInfo += buffer;
	data.fileInfo.pop_back();
	data.data.playerData = GameManager::GetInstance().GetPlayer().GetUnDoData();
	data.data.monsterData = GameManager::GetInstance().GetMonsterMapManager().GetUnDoData();
	
	std::string key = "SaveFile" + std::to_string(idx) + ".txt";
	std::ofstream ofs(key);
	boost::archive::text_oarchive oa(ofs);
	oa << data;
	_saveLoadList[idx] = data;
	ClosePopup();
}

void SaveLoadManager::Load(__int32 idx)
{
	if ("Empty" != _saveLoadList[idx].fileInfo)
	{
		SaveFileData data = _saveLoadList[idx];
		GameManager::GetInstance().GetPlayer().SetUnDoData(data.data.playerData);
		GameManager::GetInstance().GetMonsterMapManager().LoadData(data.data.monsterData);
		ClosePopup();
		return;
	}
	SaveFileData data;
	std::string key = "SaveFile" + std::to_string(idx) + ".txt";
	std::ifstream ifs(key);
	boost::archive::text_iarchive ia(ifs);
	ia >> data;

	_saveLoadList[idx] = data;
	GameManager::GetInstance().SetDifficult(data.difficult);
	GameManager::GetInstance().GetPlayer().SetUnDoData(data.data.playerData);
	GameManager::GetInstance().GetMonsterMapManager().LoadData(data.data.monsterData);
	ClosePopup();
}

void SaveLoadManager::Initialize()
{
	_saveLoadList.clear();
	for (__int32 i = 0; i < 10; i++)
	{
		std::string key = "SaveFile" + std::to_string(i) + ".txt";
		if (false == std::filesystem::exists(key))
		{
			SaveFileData data;
			data.fileInfo = "Empty";
			_saveLoadList.insert({ i, data });
		}
		else
		{
			std::ifstream ifs(key);
			boost::archive::text_iarchive ia(ifs);
			SaveFileData data;
			ia >> data;
			_saveLoadList.insert({ i, data });
		}
	}

}

void SaveLoadManager::ChoiceProcess()
{
	SaveLoadList target = static_cast<SaveLoadList>(_CURRENT_SELECT_IDX);
	switch (target)
	{
	case SaveLoadList::Exit:
	{
		GameManager::GetInstance().ChangeGameMode(GameManager::GetInstance().GetPrevGameMode(), nullptr);
		break;
	}
	default:
	{
		_isOpenPopup = true;
		_CURRENT_SELECTED_IDX = _CURRENT_SELECT_IDX;
		Utility::GetInstance().ClearCmd();
		SetPopupButtonList();
		break;
	}
	}

}

void SaveLoadManager::PopupChoiceProcess()
{
	SaveLoadPopup target = _buttonList[_CURRENT_POPUP_SELECT_IDX];
	switch (target)
	{
	case SaveLoadPopup::Save:
		Save(_CURRENT_SELECTED_IDX);
		break;
	case SaveLoadPopup::Load:
		Load(_CURRENT_SELECTED_IDX);
		break;
	case SaveLoadPopup::Exit:
		ClosePopup();
		break;
	}
}

void SaveLoadManager::SetPopupButtonList()
{
	_buttonList.clear();
	bool _isEmpty = false;
	if ("Empty" == _saveLoadList[_CURRENT_SELECTED_IDX].fileInfo)
		_isEmpty = true;

	for (__int32 i = 0; i < static_cast<__int32> (SaveLoadPopup::Max); i++)
	{
		if (true == _isEmpty && SaveLoadPopup::Load == static_cast<SaveLoadPopup> (i))
			continue;

		_buttonList.push_back(static_cast<SaveLoadPopup>(i));
	}
}

void SaveLoadManager::ClosePopup()
{
	_isOpenPopup = false;
	_CURRENT_POPUP_SELECT_IDX = 0;
	Utility::GetInstance().ClearCmd();
}

void SaveLoadManager::PopupRender()
{
	Utility::GetInstance().SetCursorPosition(50, 5);
	std::cout << "[ SAVE FILE SLOT : " << _CURRENT_SELECTED_IDX + 1<< " ]";

	for (__int32 i = 0; i < _buttonList.size(); i++)
	{
		SaveLoadPopup target = _buttonList[i];
		Utility::GetInstance().SetCursorPosition(50, 10 + i);
		switch (target)
		{
		case SaveLoadPopup::Save:
			if (i == _CURRENT_POPUP_SELECT_IDX)
			{
				std::cout << _pointerShape << " [ SAVE ]" << std::endl;
				break;
			}
			std::cout << "   [ SAVE ]" << std::endl;
			break;
		case SaveLoadPopup::Load:
			if (i == _CURRENT_POPUP_SELECT_IDX)
			{
				std::cout << _pointerShape << " [ LOAD ]" << std::endl;
				break;
			}
			std::cout << "   [ LOAD ]" << std::endl;
			break;
		case SaveLoadPopup::Exit:
			if (i == _CURRENT_POPUP_SELECT_IDX)
			{
				std::cout << _pointerShape << " [ EXIT ]" << std::endl;
				break;
			}
			std::cout << "   [ EXIT ]" << std::endl;
			break;
		}
	}
}

std::string SaveLoadManager::ToStringFromDifficult()
{
	std::string difficultStr;
	Difficult difficult = GameManager::GetInstance().GetDifficult();
	switch (difficult)
	{
	case Difficult::Easy:
		difficultStr = "EASY";
		break;
	case Difficult::Normal:
		difficultStr = "NOLMAL";
		break;
	case Difficult::Hard:
		difficultStr = "HARD";
		break;
	}
	std::string str;
	str.append("[ ");
	str.append(difficultStr);
	str.append(" ] : ");
	return str;
}

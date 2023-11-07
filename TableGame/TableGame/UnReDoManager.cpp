#include "UnReDoManager.h"

UnReDoManager::UnReDoManager():
	_CURRENT_TARGET_OPTION(0), _pointShape("¢¹"),
	_titleShape("[ UNDO & REDO ]")
{
	for (__int32 i = 0; i < static_cast<int>(UnReDo::Max); i++)
	{
		UnReDo value = static_cast<UnReDo>(i);
		_selectList.push_back(value);
	}
}

UnReDoManager::~UnReDoManager()
{
}

void UnReDoManager::Update()
{
	UpdateCursor();
}

void UnReDoManager::SetUnDo()
{
	SetUnDoData();
	//PlayerInputTableMode playerInput = GameManager::GetInstance().GetPlayer().GetCurrentInputTableMode();
	//switch (playerInput)
	//{
	//case PlayerInputTableMode::None:
	//case PlayerInputTableMode::Right:
	//case PlayerInputTableMode::Left:
	//case PlayerInputTableMode::Up:
	//case PlayerInputTableMode::Down:
	//	break;
	//case PlayerInputTableMode::ESC:
	//	break;
	//case PlayerInputTableMode::Enter:
	//	break;
	//default:
	//	break;
	//}
}

void UnReDoManager::Render()
{
	PrintSelectList();
}

void UnReDoManager::SetUnDoData()
{
	if (0 < _redoStack.size()) 
	{
		while (!_redoStack.empty())
			_redoStack.pop();
	}
	SaveData data;
	data.playerData = GameManager::GetInstance().GetPlayer().GetUnDoData();
	data.monsterData = GameManager::GetInstance().GetMonsterMapManager().GetUnDoData();
	_undoStack.push(data);
}

void UnReDoManager::UpdateCursor()
{
	PlayerInputSelectMode playerInput = GameManager::GetInstance().GetPlayer().GetCurrentInputSelectMode();
	switch (playerInput)
	{
	case PlayerInputSelectMode::None:
		break;
	case PlayerInputSelectMode::Up:
	{
		if (-1 == _CURRENT_TARGET_OPTION - 1)
			break;
		_CURRENT_TARGET_OPTION--;
		break;
	}
	case PlayerInputSelectMode::Down:
	{
		if (_selectList.size() == _CURRENT_TARGET_OPTION + 1)
			break;
		_CURRENT_TARGET_OPTION++;
		break;
	}
	case PlayerInputSelectMode::Enter:
		ChoiceProcess();
		break;
	}
}

void UnReDoManager::ChoiceProcess()
{
	UnReDo target = static_cast<UnReDo>(_CURRENT_TARGET_OPTION);
	switch (target)
	{
	case UnReDo::Undo:
	{
		Undo();
		break;
	}
	case UnReDo::Redo:
		Redo();
		break;
	case UnReDo::Exit:
		GameManager::GetInstance().ChangeGameMode(GameMode::TableMode, nullptr);
		break;
	}
}

void UnReDoManager::PrintSelectList()
{
	Utility::GetInstance().SetCursorPosition(98, 2);
	std::cout << _titleShape << std::endl;

	for (__int32 i = 0; i < _selectList.size(); i++)
	{
		UnReDo option = static_cast<UnReDo>(i);
		Utility::GetInstance().SetCursorPosition(98, 15 + i);
		switch (option)
		{
		case UnReDo::Undo:
			if (i == _CURRENT_TARGET_OPTION)
			{
				std::cout << _pointShape << " [ UNDO ]" << std::endl;
				break;
			}
			std::cout << "   [ UNDO ]" << std::endl;
			break;
		case UnReDo::Redo:
			if (i == _CURRENT_TARGET_OPTION)
			{
				std::cout << _pointShape << " [ REDO ]" << std::endl;
				break;
			}
			std::cout << "   [ REDO ]" << std::endl;
			break;
		case UnReDo::Exit:
			if (i == _CURRENT_TARGET_OPTION)
			{
				std::cout << _pointShape << " [ EXIT ]" << std::endl;
				break;
			}
			std::cout << "   [ EXIT ]" << std::endl;
			break;
		}
	}
}

void UnReDoManager::Undo()
{
	if (0 >= _undoStack.size())
		return; 

	SaveData data = _undoStack.top();
	_undoStack.pop();
	GameManager::GetInstance().GetPlayer().SetUnDoData(data.playerData);
	GameManager::GetInstance().GetMonsterMapManager().SetUndoData(data.monsterData);
	_redoStack.push(data);
}

void UnReDoManager::Redo()
{
	if (0 >= _redoStack.size())
		return;

	SaveData data = _redoStack.top();
	_redoStack.pop();
	GameManager::GetInstance().GetPlayer().SetUnDoData(data.playerData);
	GameManager::GetInstance().GetMonsterMapManager().SetUndoData(data.monsterData);
	_undoStack.push(data);
}


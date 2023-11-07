#pragma once
#include "Structs.h"
#include "TableGame.h"


class UnReDoManager
{
public:

	UnReDoManager();
	~UnReDoManager();
 
	void Update();
	void SetUnDo();
	void Render();
	void SetUnDoData();

private:
	__int32 _CURRENT_TARGET_OPTION;
	std::string _titleShape;
	std::string _pointShape;
	std::vector<UnReDo> _selectList;
	std::stack<SaveData> _undoStack;
	std::stack<SaveData> _redoStack;
private:
	void UpdateCursor();
	void ChoiceProcess();
	void PrintSelectList();
	void Undo();
	void Redo();
};


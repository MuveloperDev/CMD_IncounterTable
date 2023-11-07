#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <string>
#include <filesystem> 
#include "Structs.h"
#include "Enum.h"


#include <fstream>
class SaveLoadManager
{
public:
	SaveLoadManager();
	~SaveLoadManager();
	void Update();
	void Render();
public:
	void Save(__int32 idx);
	void Load(__int32 idx);

private:
	__int32 _CURRENT_SELECT_IDX;
	__int32 _CURRENT_POPUP_SELECT_IDX;
	__int32 _CURRENT_SELECTED_IDX;
	bool _isOpenPopup;
	std::string _pointerShape;
	std::string _titleShape;
	std::map<int, SaveFileData> _saveLoadList;
	std::vector<SaveLoadPopup> _buttonList;
private:
	void ChoiceProcess();
	void PopupChoiceProcess();
	void SetPopupButtonList();
	void ClosePopup();
	void PopupRender();
	std::string ToStringFromDifficult();
};


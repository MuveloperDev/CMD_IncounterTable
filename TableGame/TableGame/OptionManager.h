#pragma once
#include "TableGame.h"
class OptionManager
{
public:
	OptionManager();
	~OptionManager();
	void Awake();
	void Start();
	void Update();
	void Render();
private:
	__int32 _CURRENT_TARGET_OPTION;
	std::string _titleShape;
	std::string _pointShape;
	std::vector<Options> _optionList;
	
private:
	void UpdateCursor();
	void ChoiceProcess();
	void PrintOptionList();
};


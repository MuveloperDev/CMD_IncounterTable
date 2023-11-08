#pragma once
#include "Utility.h"
#include "TitleScene.h"
#include "Enum.h"
#include <stdint.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

class TitleScene;
class DifficultSelectPage
{
public: 
	DifficultSelectPage(TitleScene* InTitleScene);
	~DifficultSelectPage();

	void Update();
	void Render();

private:
	__int32 _CURRENT_TARGET_OPTION;
	bool isKeyDown;
	Difficult _CURRENT_SELECTED_OPTION;
	std::string _titleShape;
	std::string _pointShape;
	std::vector<Difficult> _optionList;
	TitleScene* _titleScene;
private:
	void UpdateCursor();
	void ChoiceProcess();
	void PrintOptionList();
	void PrintSelectedOption();
};


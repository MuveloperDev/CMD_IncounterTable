#pragma once
#include "Utility.h"
#include "Enum.h"
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <vector>
#include "GameManager.h"
#include <thread>
#include <future>
class Intro
{
public:
	Intro();
	~Intro();

	void Start();
	void PrintScript();
	void Music();
private:
	bool _isKeyDown;
	Scene _CURRENT_SCENE;
	std::vector<std::string> lines;
	std::string _script;
	std::string _backgroundPaint1;
	std::string _backgroundPaint2;
	std::vector<int> freqs;
	std::future<void> asyncMusic;
	std::future<void> updateESC;

private:
	void UpdateESC();
};


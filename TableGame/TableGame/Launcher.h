#pragma once
class GameManager;

class Launcher
{
public:
	Launcher();
	~Launcher();
	bool IsUpdate();
	void ProcessGame();
private:
	unsigned long _startTickCount;
	unsigned long _currentTickCount;
	const unsigned long _targetFrame;
};


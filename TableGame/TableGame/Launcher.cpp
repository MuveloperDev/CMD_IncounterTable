#include "Launcher.h"
#include "TitleScene.h"
#include "TableGame.h"
#include "EscapeScene.h"
#include "DeadScene.h"
#include "Intro.h"

Launcher::Launcher() :
	_startTickCount(0), 
	_currentTickCount(0), 
	_targetFrame(1000/60)
{
}

Launcher::~Launcher()
{
}



bool Launcher::IsUpdate()
{
	_startTickCount = GetTickCount64();
	if (_startTickCount - _currentTickCount >= _targetFrame)
	{
		_currentTickCount = _startTickCount;
		return true;
	}
	return false;
}

void Launcher::ProcessGame()
{
	GameManager::GetInstance().Awake();
	GameManager::GetInstance().Start();
	while (true)
	{
		if (true == IsUpdate())
			continue;
		if (Scene::Game != GameManager::GetInstance().GetCurrentScene())
			break;

		GameManager::GetInstance().Update();
		GameManager::GetInstance().Render();
	}
}


int main()
{
	Launcher* launcher = new Launcher();
	TitleScene* titleScene = new TitleScene();
	EscapeScene* escapeScene = new EscapeScene();
	DeadScene* deadScene = new DeadScene();
	Intro* intro = new Intro();
	while (true)
	{
		Utility::GetInstance().ClearCmd();
		Scene curScene = GameManager::GetInstance().GetCurrentScene();
		switch (curScene)
		{
		case Scene::None:
			GameManager::GetInstance().ChangeScene(Scene::Title);
			break;
		case Scene::Title:
			titleScene->Run();
			break;
		case Scene::Intro:
			intro->Start();
			break;
		case Scene::Game:
			launcher-> ProcessGame();
			break;
		case Scene::Lose:
			deadScene->Run();
			break;
		case Scene::Escape:
			escapeScene->Run();
			break;
		default:
			break;
		}
	}
	delete titleScene;
	delete launcher;
	delete escapeScene;
	delete deadScene;
}
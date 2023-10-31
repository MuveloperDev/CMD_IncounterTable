#include <windows.h>
#include "TitleScene.h"
#include "GameManager.h"
#include <cstdlib> // for system
TitleScene::TitleScene() : isKeyDown(false), _pointer("¢¹ "),
	_startBtnText("START"), _exitBtnText("EXIT"),
	_currentTargetBtn(Buttons::Start),
	hStdout(GetStdHandle(STD_OUTPUT_HANDLE))
{
	srWindowRect.Right = 80; // Window width
	srWindowRect.Bottom = 25; // Window height
	srWindowRect.Left = csbiInfo.srWindow.Left;
	srWindowRect.Top = csbiInfo.srWindow.Top;
	coordScreen.X = 80; // Buffer width
	coordScreen.Y = 500; // Buffer height
	Utility::GetInstance().SetCursorInvisible();
	asciiTitle = R"(
		_________ _        _______  _______           _       _________ _______  _______   
		\__   __/( (    /|(  ____ \(  ___  )|\     /|( (    /|\__   __/(  ____ \(  ____ )  
		   ) (   |  \  ( || (    \/| (   ) || )   ( ||  \  ( |   ) (   | (    \/| (    )|  
		   | |   |   \ | || |      | |   | || |   | ||   \ | |   | |   | (__    | (____)|  
		   | |   | (\ \) || |      | |   | || |   | || (\ \) |   | |   |  __)   |     __)  
		   | |   | | \   || |      | |   | || |   | || | \   |   | |   | (      | (\ (     
		___) (___| )  \  || (____/\| (___) || (___) || )  \  |   | |   | (____/\| ) \ \__  
		\_______/|/    )_)(_______/(_______)(_______)|/    )_)   )_(   (_______/|/   \__/  
                                                                                   
						_________ _______  ______   _        _______                       
						\__   __/(  ___  )(  ___ \ ( \      (  ____ \                      
						   ) (   | (   ) || (   ) )| (      | (    \/                      
						   | |   | (___) || (__/ / | |      | (__                          
						   | |   |  ___  ||  __ (  | |      |  __)                         
						   | |   | (   ) || (  \ \ | |      | (                            
						   | |   | )   ( || )___) )| (____/\| (____/\                      
						   )_(   |/     \||/ \___/ (_______/(_______/   
)";
}

TitleScene::~TitleScene()
{
}

void TitleScene::Run()
{
	while (true)
	{
		Update();
		if (true == CheckEnter())
			break;
		Render();
	}
}

void TitleScene::Update()
{
	UpdateCursor();
	Music();
}

void TitleScene::Render()
{
	Utility::GetInstance().PrintTopLine();
	Utility::GetInstance().SetCursorPosition(0, 1);
	std::cout << "							           " << asciiTitle << std::endl;
	std::cout << "\n\n\n\n\n";
	switch (_currentTargetBtn)
	{
	case TitleScene::Start:
		std::cout << "						    " << _pointer << " " << _startBtnText << std::endl;
		std::cout << "						        " << _exitBtnText << std::endl;
		break;
	case TitleScene::Exit:
		std::cout << "						        "  << _startBtnText << std::endl;
		std::cout << "					            " << _pointer << " " << _exitBtnText << std::endl;
		break;
	}
	Utility::GetInstance().PrintHirizontalLine(23);
	Utility::GetInstance().PrintBottomLine();
}


void TitleScene::UpdateCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SHORT uptState = GetAsyncKeyState(VK_UP);
	SHORT downState = GetAsyncKeyState(VK_DOWN);
	
	bool isUp = (uptState & 0x8000) != 0;
	bool isDown = (downState & 0x8000) != 0;
	


	if (isUp || isDown)
	{
		if (isKeyDown == false)
		{
			if (isUp)
			{
				//Beep(750, 300);
				//Beep(250, 200);
				if (Buttons::Start == _currentTargetBtn)
					return;
				Utility::GetInstance().ClearCmd();
				_currentTargetBtn = Buttons::Start;
			}
			if (isDown)
			{
				if (Buttons::Exit == _currentTargetBtn)
					return;
				Utility::GetInstance().ClearCmd();
				_currentTargetBtn = Buttons::Exit;
			}
		}
		isKeyDown = true;
	}
	else
	{
		isKeyDown = false;
	}
}

bool TitleScene::CheckEnter()
{
	SHORT enterState = GetAsyncKeyState(VK_RETURN);
	bool onEnter = (enterState & 0x8000) != 0;
	bool isStart = Buttons::Start == _currentTargetBtn;
	if (true == onEnter)
	{
		switch (_currentTargetBtn)
		{
		case TitleScene::Start:
			Utility::GetInstance().ClearCmd();
			GameManager::GetInstance().ChangeScene(Scene::Game);
			return true;
		case TitleScene::Exit:
			Utility::GetInstance().ClearCmd();
			ExitProcess(0);
			return true;
		}
	}
	return false;
}

void TitleScene::Music()
{
	Beep(750, 10);
	Beep(500, 10);
	Beep(250, 10);
}

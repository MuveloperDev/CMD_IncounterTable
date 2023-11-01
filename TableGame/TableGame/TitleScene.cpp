#include <windows.h>
#include "TitleScene.h"
#include "GameManager.h"
#include <cstdlib> // for system
TitleScene::TitleScene() : 
	_startBtnText("START"), _exitBtnText("EXIT"),
	SceneBase(R"(
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
)")
{
	srWindowRect.Right = 80; // Window width
	srWindowRect.Bottom = 25; // Window height
	srWindowRect.Left = csbiInfo.srWindow.Left;
	srWindowRect.Top = csbiInfo.srWindow.Top;
	coordScreen.X = 80; // Buffer width
	coordScreen.Y = 500; // Buffer height
	Utility::GetInstance().SetCursorInvisible();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Run()
{
	Initialize();
	while (true)
	{
		Update();
		if (true == SelectProcess())
			break;
		Render();
	}
}

void TitleScene::Initialize()
{
	SceneBase::Initialize();

	_buttons.push_back(Buttons::Start);
	_buttons.push_back(Buttons::Exit);
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
	std::cout << "							           " << _asciiTitle << std::endl;
	std::cout << "\n\n\n\n\n";
	switch (_buttons[_CURRENT_BTN_IDX])
	{
	case Buttons::Start:
		std::cout << "						    " << _pointer << " " << _startBtnText << std::endl;
		std::cout << "						        " << _exitBtnText << std::endl;
		break;
	case Buttons::Exit:
		std::cout << "						        "  << _startBtnText << std::endl;
		std::cout << "					            " << _pointer << " " << _exitBtnText << std::endl;
		break;
	}
	Utility::GetInstance().PrintHirizontalLine(23);
	Utility::GetInstance().PrintBottomLine();
}


bool TitleScene::SelectProcess()
{
	switch (_CURRENTINPUT)
	{
	case PlayerInputSelectMode::None:
	case PlayerInputSelectMode::Up:
	case PlayerInputSelectMode::Down:
		return false;
	case PlayerInputSelectMode::Enter:
		switch (_buttons[_CURRENT_BTN_IDX])
		{
		case Buttons::Start:
			Utility::GetInstance().ClearCmd();
			GameManager::GetInstance().ChangeScene(Scene::Game);
			break;
		case Buttons::Exit:
			Utility::GetInstance().ClearCmd();
			ExitProcess(0);
			break;
		}
		return true;
	}
}

void TitleScene::Music()
{
	Beep(750, 10);
	Beep(500, 10);
	Beep(250, 10);
}

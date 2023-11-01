#include "EscapeScene.h"
#include "GameManager.h"

EscapeScene::EscapeScene() :
	_restartBtnText("RESTART"), _exitBtnText("EXIT"),
	SceneBase(R"(
       _______  _______  _        _______  _______  _______ _________          _        _______ _________ _______ 
      (  ____ \(  ___  )( (    /|(  ____ \(  ____ )(  ___  )\__   __/|\     /|( \      (  ___  )\__   __/(  ____ \
      | (    \/| (   ) ||  \  ( || (    \/| (    )|| (   ) |   ) (   | )   ( || (      | (   ) |   ) (   | (    \/
      | |      | |   | ||   \ | || |      | (____)|| (___) |   | |   | |   | || |      | (___) |   | |   | (__    
      | |      | |   | || (\ \) || | ____ |     __)|  ___  |   | |   | |   | || |      |  ___  |   | |   |  __)   
      | |      | |   | || | \   || | \_  )| (\ (   | (   ) |   | |   | |   | || |      | (   ) |   | |   | (      
      | (____/\| (___) || )  \  || (___) || ) \ \__| )   ( |   | |   | (___) || (____/\| )   ( |   | |   | (____/\
      (_______/(_______)|/    )_)(_______)|/   \__/|/     \|   )_(   (_______)(_______/|/     \|   )_(   (_______/
                                                                                                                  
                _______    _______    _______    _______      _______  _        _______  _______  _______            
               (  ____ \  (  ___  )  (       )  (  ____ \    (  ____ \( \      (  ____ \(  ___  )(  ____ )           
               | (    \/  | (   ) |  | () () |  | (    \/    | (    \/| (      | (    \/| (   ) || (    )|           
               | |        | (___) |  | || || |  | (__        | |      | |      | (__    | (___) || (____)|           
               | | ____   |  ___  |  | |(_)| |  |  __)       | |      | |      |  __)   |  ___  ||     __)           
               | | \_  )  | (   ) |  | |   | |  | (          | |      | |      | (      | (   ) || (\ (              
               | (___) |  | )   ( |  | )   ( |  | (____/\    | (____/\| (____/\| (____/\| )   ( || ) \ \__           
               (_______)  |/     \|  |/     \|  (_______/    (_______/(_______/(_______/|/     \||/   \__/                                                                                                                      
)") 
{
}

EscapeScene::~EscapeScene()
{
}

void EscapeScene::Run()
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

void EscapeScene::Initialize()
{
	SceneBase::Initialize();
	_buttons.push_back(Buttons::Restart);
	_buttons.push_back(Buttons::Exit);
}

void EscapeScene::Update()
{
	UpdateCursor();
	Music();
}

void EscapeScene::Render()
{
	Utility::GetInstance().PrintTopLine();
	Utility::GetInstance().SetCursorPosition(0, 1);
	std::cout << "							           " << _asciiTitle << std::endl;
	std::cout << "\n\n\n\n\n";
	switch (_buttons[_CURRENT_BTN_IDX])
	{
	case Buttons::Restart:
		std::cout << "						    " << _pointer << " " << _restartBtnText << std::endl;
		std::cout << "						        " << _exitBtnText << std::endl;
		break;
	case Buttons::Exit:
		std::cout << "						        " << _restartBtnText << std::endl;
		std::cout << "					            " << _pointer << " " << _exitBtnText << std::endl;
		break;
	}
	Utility::GetInstance().PrintHirizontalLine(23);
	Utility::GetInstance().PrintBottomLine();
}

void EscapeScene::Music()
{
}

bool EscapeScene::SelectProcess()
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
		case Buttons::Restart:
			Utility::GetInstance().ClearCmd();
			GameManager::GetInstance().ChangeScene(Scene::Title);
			break;
		case Buttons::Exit:
			Utility::GetInstance().ClearCmd();
			ExitProcess(0);
			break;
		}
		return true;
	}
}

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
         (_______)  |/     \|  |/     \|  (_______/    (_______/(_______/(_______/|/     \||/   \__/ )"),
	_CURRENT_SCENE(Scene::None)
{
	freqs = { 392, 440, 392, 261*2 };
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
	_CURRENT_SCENE = GameManager::GetInstance().GetCurrentScene();
	if (asyncMusic.valid()) {
		asyncMusic.get();  // 이전에 생성한 비동기 작업이 완료될 때까지 대기
	}
	asyncMusic = std::async(std::launch::async, &EscapeScene::Music, this);
	_buttons.push_back(Buttons::Restart);
	_buttons.push_back(Buttons::Exit);
}

void EscapeScene::Update()
{
	UpdateCursor();
}

void EscapeScene::Render()
{
	Utility::GetInstance().PrintShape(6, 1, _asciiTitle);
	switch (_buttons[_CURRENT_BTN_IDX])
	{
	case Buttons::Restart:
		Utility::GetInstance().SetCursorPosition(55, 25);
		Utility::GetInstance().ChangeTextColor(TextColors::Green, false, [this]() {
			std::cout << _pointer << " " << _restartBtnText << std::endl;
			});
		Utility::GetInstance().SetCursorPosition(55, 26);
		std::cout << "    " << _exitBtnText << std::endl;
		break;
	case Buttons::Exit:
		Utility::GetInstance().SetCursorPosition(55, 25);
		std::cout << "    " << _restartBtnText << std::endl;
		Utility::GetInstance().SetCursorPosition(55, 26);
		Utility::GetInstance().ChangeTextColor(TextColors::Green, false, [this]() {
			std::cout << _pointer << " " << _exitBtnText << std::endl;
			});
		break;
	}
	Utility::GetInstance().PrintHorizontalLine(2, 116, 23);
	Utility::GetInstance().PrintFrame();
}

void EscapeScene::Music()
{
	std::lock_guard<std::mutex> lock(mtx);
	while (Scene::Escape == _CURRENT_SCENE)
	{
		for (int freq : freqs)
		{
			Beep(freq, 500);
			if (Scene::Escape != _CURRENT_SCENE)
				break;
		}
	}
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
			_CURRENT_SCENE = GameManager::GetInstance().GetCurrentScene();
			break;
		case Buttons::Exit:
			Utility::GetInstance().ClearCmd();
			ExitProcess(0);
			break;
		}
		return true;
	}
}

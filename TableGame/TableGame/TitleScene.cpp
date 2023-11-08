#include <windows.h>
#include "TitleScene.h"
#include "GameManager.h"
#include <cstdlib> // for system



TitleScene::TitleScene() : 
	_startBtnText("START"), _exitBtnText("EXIT"), _difficultBtnText("DIFFICULT"),
	_CURRENT_MODE(TitleMode::Title), _difficultSelectPage(new DifficultSelectPage(this)),
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
	_CURRENT_SCENE = Scene::Title;
	freqs = { 261, 329, 392, 329, 293, 349, 440 , 392, 349, 293};
}

TitleScene::~TitleScene()
{
	delete _difficultSelectPage;
}

void TitleScene::Run()
{
	Initialize();
	if (asyncMusic.valid()) {
		asyncMusic.get();  // 이전에 생성한 비동기 작업이 완료될 때까지 대기
	}
	asyncMusic = std::async(std::launch::async, &TitleScene::Music, this);

	while (Scene::Title == _CURRENT_SCENE)
	{
		switch (_CURRENT_MODE)
		{
		case TitleMode::Title:
			Update();
			if (true == SelectProcess())
				break;
			Render();
			break;
		case TitleMode::Difficult:
			_difficultSelectPage->Update();
			_difficultSelectPage->Render();
			break;
		}

	}
}

void TitleScene::SetMode(TitleMode InMode)
{
	_CURRENT_MODE = InMode;
	Utility::GetInstance().ClearCmd();
}

TitleMode TitleScene::GetMode()
{
	return _CURRENT_MODE;
}

void TitleScene::Initialize()
{
	SceneBase::Initialize();
	
	_buttons.push_back(Buttons::Start);
	_buttons.push_back(Buttons::Difficult);
	_buttons.push_back(Buttons::Exit);
}

void TitleScene::Update()
{
	UpdateCursor();
	
}

void TitleScene::Render()
{
	Utility::GetInstance().PrintShape(20, 1, _asciiTitle);
	
	switch (_buttons[_CURRENT_BTN_IDX])
	{
	case Buttons::Start:
		Utility::GetInstance().SetCursorPosition(55, 25);
		Utility::GetInstance().ChangeTextColor(TextColors::Green, false, [this]() {
			std::cout << _pointer << " " << _startBtnText << std::endl;
			});

		Utility::GetInstance().SetCursorPosition(55, 26);
		std::cout << "    " << _difficultBtnText << std::endl;
		Utility::GetInstance().SetCursorPosition(55, 27);
		std::cout << "    " << _exitBtnText << std::endl;
		break;
	case Buttons::Difficult:
		Utility::GetInstance().SetCursorPosition(55, 25);
			std::cout << "    " << _startBtnText << std::endl;
		Utility::GetInstance().SetCursorPosition(55, 26);
		Utility::GetInstance().ChangeTextColor(TextColors::Green, false, [this]() {
			std::cout << _pointer << " " << _difficultBtnText << std::endl;
			});
		Utility::GetInstance().SetCursorPosition(55, 27);
		std::cout << "    " << _exitBtnText << std::endl;
		break;
	case Buttons::Exit:
		Utility::GetInstance().SetCursorPosition(55, 25);
		std::cout << "    "  << _startBtnText << std::endl;
		Utility::GetInstance().SetCursorPosition(55, 26);
		std::cout << "    "  << _difficultBtnText << std::endl;
		Utility::GetInstance().SetCursorPosition(55, 27);
		Utility::GetInstance().ChangeTextColor(TextColors::Green, false, [this]() {
			std::cout << _pointer << " " << _exitBtnText << std::endl;
			});

		break;
	}
	Utility::GetInstance().PrintHorizontalLine(2, 116, 23);
	Utility::GetInstance().PrintFrame();
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

			GameManager::GetInstance().ChangeScene(Scene::Intro);
			_CURRENT_SCENE = GameManager::GetInstance().GetCurrentScene();
			break;
		case Buttons::Difficult:
			SetMode(TitleMode::Difficult);
			_CURRENTINPUT = PlayerInputSelectMode::None;
			break;
		case Buttons::Exit:
			Utility::GetInstance().ClearCmd();
			ExitProcess(0);
			break;
		}
		return true;
	}
}

//도(C) : 261.63 Hz
//	레(D) : 293.66 Hz
//	미(E) : 329.63 Hz
//	파(F) : 349.23 Hz
//	솔(G) : 392.00 Hz
//	라(A) : 440.00 Hz
//	시(B) : 493.88 Hz
void TitleScene::Music()
{
	// 뮤텍스를 잠그고, 함수가 끝나면 자동으로 뮤텍스를 해제
	// 함수가 예외를 발생시켜도 std::lock_guard 객체가 소멸되면서 뮤텍스를 안전하게 해제하므로, 
	// 데드락을 방지할 수 있습니다.
	// std::lock_guard 객체는 생성될 때 뮤텍스를 자동으로 잠그고 (lock), 
	// 소멸될 때 뮤텍스를 자동으로 해제 (unlock) 합니다.
	std::lock_guard<std::mutex> lock(mtx);  

	while (Scene::Title == _CURRENT_SCENE)
	{
		for (int freq : freqs)
		{
			Beep(freq, 500);
			if (Scene::Title != _CURRENT_SCENE)
				break;
		}
		if (Scene::Title != _CURRENT_SCENE)
			break;
	}

}

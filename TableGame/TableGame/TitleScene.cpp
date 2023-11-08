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
		asyncMusic.get();  // ������ ������ �񵿱� �۾��� �Ϸ�� ������ ���
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

//��(C) : 261.63 Hz
//	��(D) : 293.66 Hz
//	��(E) : 329.63 Hz
//	��(F) : 349.23 Hz
//	��(G) : 392.00 Hz
//	��(A) : 440.00 Hz
//	��(B) : 493.88 Hz
void TitleScene::Music()
{
	// ���ؽ��� ��װ�, �Լ��� ������ �ڵ����� ���ؽ��� ����
	// �Լ��� ���ܸ� �߻����ѵ� std::lock_guard ��ü�� �Ҹ�Ǹ鼭 ���ؽ��� �����ϰ� �����ϹǷ�, 
	// ������� ������ �� �ֽ��ϴ�.
	// std::lock_guard ��ü�� ������ �� ���ؽ��� �ڵ����� ��װ� (lock), 
	// �Ҹ�� �� ���ؽ��� �ڵ����� ���� (unlock) �մϴ�.
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

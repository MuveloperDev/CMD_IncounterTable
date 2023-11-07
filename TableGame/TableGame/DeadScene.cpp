#include "DeadScene.h"
#include "GameManager.h"

DeadScene::DeadScene() :
	_restartBtnText("RESTART"), _exitBtnText("EXIT"),
	SceneBase(R"(
              .,od88888888888bo,.
          .d88888888888888888888888b.
       .d88888888888888888888888888888b.
     .d888888888888888888888888888888888b.
   .d8888888888888888888888888888888888888b.
  d88888888888888888888888888888888888888888b
 d8888888888888888888888888888888888888888888b
d888888888888888888888888888888888888888888888
8888888888888888888888888888888888888888888888
8888888888888888888888888888888888888888888888
8888888888888888888888888888888888888888888888
Y88888888888888888888888888888888888888888888P
"8888888888P'   "Y8888888888P"    "Y888888888"
 88888888P        Y88888888P        Y88888888
 Y8888888          ]888888P          8888888P
  Y888888          d888888b          888888P
   Y88888b        d88888888b        d88888P
    Y888888b.   .d88888888888b.   .d888888
     Y8888888888888888P Y8888888888888888
      888888888888888P   Y88888888888888
      "8888888888888[     ]888888888888"
)")
{
	freqs = { 329, 329, 329, 261, 293, 293, 293 , 493 / 2};
}

DeadScene::~DeadScene()
{
}

void DeadScene::Run()
{
	Initialize();
	if (asyncMusic.valid()) {
		asyncMusic.get();  // 이전에 생성한 비동기 작업이 완료될 때까지 대기
	}
	asyncMusic = std::async(std::launch::async, &DeadScene::Music, this);
	while (true)
	{
		Update();
		if (true == SelectProcess())
			break;
		Render();
	}
}

void DeadScene::Initialize()
{
	SceneBase::Initialize();
	_buttons.push_back(Buttons::Restart);
	_buttons.push_back(Buttons::Exit);
}

void DeadScene::Update()
{
	UpdateCursor();
}

void DeadScene::Render()
{
	Utility::GetInstance().PrintShape(38, 1, _asciiTitle);
	switch (_buttons[_CURRENT_BTN_IDX])
	{
	case Buttons::Restart:
		Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
		std::cout << "						    " << _pointer << " " << _restartBtnText << std::endl;
		Utility::GetInstance().ResetTextColor();
		std::cout << "						        " << _exitBtnText << std::endl;
		break;
	case Buttons::Exit:
		Utility::GetInstance().ChangeTextColor(TextColors::Green, false);
		std::cout << "						        " << _restartBtnText << std::endl;
		Utility::GetInstance().ResetTextColor();
		std::cout << "					            " << _pointer << " " << _exitBtnText << std::endl;
		break;
	}
	Utility::GetInstance().PrintFrame();
}

void DeadScene::Music()
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

bool DeadScene::SelectProcess()
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

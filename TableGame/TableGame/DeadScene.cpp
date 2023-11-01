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
}

DeadScene::~DeadScene()
{
}

void DeadScene::Run()
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

void DeadScene::Initialize()
{
	SceneBase::Initialize();
	_buttons.push_back(Buttons::Restart);
	_buttons.push_back(Buttons::Exit);
}

void DeadScene::Update()
{
	UpdateCursor();
	Music();
}

void DeadScene::Render()
{
	Utility::GetInstance().PrintTopLine();
	Utility::GetInstance().SetCursorPosition(0, 1);
	std::cout << "							           " << _asciiTitle << std::endl;
	std::cout << "\n";
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

void DeadScene::Music()
{
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

#include "Intro.h"
#include "GameManager.h"


// 미 라 시 라
Intro::Intro():
	_backgroundPaint1(R"(
________.   ._____________________________.
(///(////\  ///(///(///(///(///(///(///(////\
///(///(  \///(///(///(///(///(///(///(///(  \
//(///(   ///(///(///(///(///(///(///(///(   |
/(///(  .///(///(///(///(///(///(///(///(  . |
    | .' |  ___    ___    ___   _____  | .'| |
    | |.'| |_|_|  |_|_|  |_|_| |__|__| | |.' |
    | '  | |_|_|  |_|_|  |_|_| |__|__| | ' . ||'--:|
__  |  .'|    __   _____    _ %%%____  | .'| |  .|
__| | |.'|   |  | |__|__|  |_%%%%%___| ||.' .'.|   .'         .'
__| | '.'|   | .| |__|__|  |%%%:%%___| |' .'.|   .'         .'
____|.'  |___|__|___________%%::%______|.'.|   .'         .'
       .|   '-=-.'            :'       .|    .'         .'
     .|   '   .               :      .|    .'         .'
   .|   '   .                       .|   .'         .'
  |'--'|==||'--'|'--'|'--'|'--'|'-'|   .'         .'
===jim================================'         .'
.    ...   ...   ...   ...   ...              .'

================================.
                              .'         .'
                            .'         .'
)"), 
	_backgroundPaint2(R"(
                   _.--.    .--._
                 ."  ."      ".  ".
                ;  ."    /\    ".  ;
                ;  '._,-/  \-,_.`  ;
                \  ,`  / /\ \  `,  /
                 \/    \/  \/    \/
                 ,=_    \/\/    _=,
                 |  "_   \/   _"  |
                 |_   '"-..-"'   _|
                 | "-.        .-" |
                 |    "\    /"    |
                 |      |  |      |
         ___     |      |  |      |     ___
     _,-",  ",   '_     |  |     _'   ,"  ,"-,_
   _(  \  \   \"=--"-.  |  |  .-"--="/   /  /  )_
 ,"  \  \  \   \      "-'--'-"      /   /  /  /  ".
!     \  \  \   \                  /   /  /  /     !
:      \  \  \   \                /   /  /  /      
)"), 
	_script(R"(
"Once a peaceful world, 
now on the brink of envelopment by an ominous silence. 
Storms are brewing, dragons darken the sky, 
and an evil force is threatening all life.
Yet, hope remains. 
That hope is a 'hero'. 
A knight from the legends we've all been waiting for. 
His name is yet unknown, 
but his courage and determination are already ablaze 
with the power to save the world.
Today, he steps out of 
his humble abode to rescue the world.
 His sword shines bright, his eyes glow with hope. 
With his every stride, 
we draw courage and follow along.
This is just the beginning. 
His journey is long and perilous, 
but he carries his destiny and moves forward. 
O Hero, we honor your bravery, 
and believe in your ability to save the world. 
This is the beginning of our epic saga."
)"), _CURRENT_SCENE(Scene::Intro)
{
	freqs = { 329 /2 , 440 / 2, 493 / 2, 440 / 2 };
	std::istringstream stream(_script);
	for (std::string line; std::getline(stream, line); )
	{
		lines.push_back(line);
	}
}

Intro::~Intro()
{
}



void Intro::Start()
{
	_CURRENT_SCENE = GameManager::GetInstance().GetCurrentScene();
	if (asyncMusic.valid()) {
		asyncMusic.get();  // 이전에 생성한 비동기 작업이 완료될 때까지 대기
	}
	asyncMusic = std::async(std::launch::async, &Intro::Music, this);
	updateESC = std::async(std::launch::async, &Intro::UpdateESC, this);
	PrintScript();
}

void Intro::PrintScript()
{
	std::istringstream stream(_script);

	for (__int32 i = 0; i < lines.size(); i++)
	{
		if (Scene::Intro != _CURRENT_SCENE)
			break;

		Utility::GetInstance().ChangeTextColor(TextColors::Intensity, true);
		if (i < lines.size() / 2)
		{
			Utility::GetInstance().PrintShape(0, 0, _backgroundPaint1);
		}
		else
		{
			Utility::GetInstance().PrintShape(0, 0, _backgroundPaint2);
		}
		Utility::GetInstance().ResetTextColor();
		for (__int32 idx = 0; idx <= i; idx++)
		{
			Utility::GetInstance().SetCursorPosition(60, 25 - i +idx);
			std::cout << lines[idx];
		}
		Utility::GetInstance().PrintFrame();
		Utility::GetInstance().SetCursorPosition(3, 27);
		std::cout << "[ ESC : SKIP ] ";
		
		if (Scene::Intro != _CURRENT_SCENE)
			break;
		Sleep(1000);
		if (Scene::Intro != _CURRENT_SCENE)
			break;
		Utility::GetInstance().ClearCmd();
	}
	Sleep(1000);
	_CURRENT_SCENE = Scene::Game;
	GameManager::GetInstance().ChangeScene(Scene::Game);


}
void Intro::Music()
{
	while (Scene::Intro == _CURRENT_SCENE)
	{
		for (int freq : freqs)
		{
			if (Scene::Intro != _CURRENT_SCENE)
				break;
			Beep(freq, 500);
		}
	}

}

void Intro::UpdateESC()
{
	while (true)
	{
		SHORT escState = GetAsyncKeyState(VK_ESCAPE);
		bool isESC = (escState & 0x8000) != 0;
		if (true == isESC)
		{
			if (_isKeyDown == false)
			{
				Utility::GetInstance().SetCursorPosition(100, 27);
				std::cout << "LOADING..... ";
				_CURRENT_SCENE = Scene::Game;
				GameManager::GetInstance().ChangeScene(Scene::Game);
				break;
			}
			_isKeyDown = true;
		}
		else
		{
			_isKeyDown = false;
		}
	}
}

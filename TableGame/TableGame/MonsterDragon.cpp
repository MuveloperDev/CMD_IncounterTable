#include "MonsterDragon.h"
#include "GameManager.h"

MonsterDragon::MonsterDragon(MonsterType InType) :
    MonsterBase(0, 0, 0, 0, false, R"(



              /|                                           |\                 
             /||             ^               ^             ||\                
            / \\__          //               \\          __// \               
           /  |_  \         | \   /     \   / |         /  _|  \              
          /  /  \  \         \  \/ \---/ \/  /         /  /     \             
         /  /    |  \         \  \/\   /\/  /         /  |       \            
        /  /     \   \__       \ ( 0\ /0 ) /       __/   /        \           
       /  /       \     \___    \ \_/|\_/ /    ___/     /\         \          
      /  /         \_)      \___ \/-\|/-\/ ___/      (_/\ \      `  \         
     /  /           /\__)       \/  oVo  \/       (__/   ` \      `  \        
    /  /           /,   \__)    (_/\ _ /\_)    (__/         `      \  \       
   /  '           //       \__)  (__V_V__)  (__/                    \  \      
  /  '  '        /'           \   |{___}|   /         .              \  \     
 /  '  /        /              \/ |{___}| \/\          `              \  \    
/     /        '       .        \/{_____}\/  \          \    `         \  \   
     /                ,         /{_______}\   \          \    \         \     
                     /         /{___/_\___}\   `          \    `
)", InType, "DRAGON")
{
    Difficult difficult = GameManager::GetInstance().GetDifficult();
    switch (difficult)
    {
    case Difficult::Easy:
        _maxHp = 300;
        _hp = _maxHp;
        _attackDamge = 10;
        _goldReward = 100;
        break;
    case Difficult::Normal:
        _maxHp = 1000;
        _hp = _maxHp;
        _attackDamge = 30;
        _goldReward = 500;
        break;
    case Difficult::Hard:
        _maxHp = 1500;
        _hp = _maxHp;
        _attackDamge = 50;
        _goldReward = 1000;
        break;
    }

    _isClear = false;
}

MonsterDragon::~MonsterDragon()
{
}

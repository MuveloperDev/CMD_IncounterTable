#include "MonsterDevil.h"
MonsterDevil::MonsterDevil(MonsterType InType) :
	MonsterBase(0, 0, 0, 0, false, R"(



     (                      )
     |\    _,--------._    / |
     | `.,'            `. /  |
     `  '              ,-'   '
      \/_         _   (     /
     (,-.`.    ,',-.`. `__,'
      |/#\ ),-','#\`= ,'.` |
      `._/)  -'.\_,'   ) ))|
      /  (_.)\     .   -'//
     (  /\____/\    ) )`'\
      \ |V----V||  ' ,    \
       |`- -- -'   ,'   \  \      _____
___    |         .'    \ \  `._,-'     `-
   `.__,`---^---'       \ ` -'
      -.______  \ . /  ______,-
              `.     ,'            
)", InType, "DEVIL")
{
    _maxHp = 100;
    _hp = _maxHp;
    _attackDamge = 10;
    _goldReward = 10;
    _isClear = false;
}

MonsterDevil::~MonsterDevil()
{
}



#include "MonsterBigFoot.h"

MonsterBigFoot::MonsterBigFoot(MonsterType InType) :
    MonsterBase(0, 0, 0, 0, false, R"(



                                                      (\`,__=-'__,'/)
                                                   _.-'-.( d\_/b ).-'-._
                                                 /'.-'   ' .---. '   '-.`\
                                               /'  .' (=    (_)    =) '.  `\
                                              /'  .',  `-.__.-.__.-'  ,'.  `\
                                             (     .'.   V       V  ; '.     )
                                             (    |::  `-,__.-.__,-'  ::|    )
                                             |   /|`:.               .:'|\   |
                                             |  / | `:.              :' |`\  |
                                             | |  (  :.             .:  )  | |
                                             | |   ( `:.            :' )   | |
                                             | |    \ :.           .: /    | |
                                             | |     \`:.         .:'/     | |
                                             ) (      `\`:.     .:'/'      ) (
                                             (  `)_     ) `:._.:' (     _(`  )
                                             \  ' _)  .'           `.  (_ `  /
                                              \  '_) /   .'"```"'.   \ (_`  /
                                               `'"`  \  (         )  /  `"'`
)", InType, "BIGFOOT")
{
    _maxHp = 100;
    _hp = _maxHp;
    _attackDamge = 10;
    _goldReward = 10;
    _isClear = false;
}

MonsterBigFoot::~MonsterBigFoot()
{
}

#include "MonsterCyclops.h"
MonsterCyclops::MonsterCyclops(MonsterType InType) :
    MonsterBase(0, 0, 0, 0, false, R"(



                                                       _......._
                                                   .-'.'.'.'.'.'.`-.
                                                 .'.'.'.'.'.'.'.'.'.`.
                                                /.'.'               '.\
                                                |.'    _.--...--._     |
                                                \    `._.-.....-._.'   /
                                                |     _..- .-. -.._   |
                                             .-.'    `.   ((@))  .'   '.-.
                                            ( ^ \      `--.   .-'     / ^ )
                                             \  /         .   .       \  /
                                             /          .'     '.  .-    \
                                            ( _.\    \ (_`-._.-'_)    /._\)
                                             `-' \   ' .--.          / `-'
                                                 |  / /|_| `-._.'\   |
                                                 |   |       |_| |   /-.._
                                             _..-\   `.--.______.'  |
                                                  \       .....     |

)", InType, "CYCLOPS")
{
    _maxHp = 100;
    _hp = _maxHp;
    _attackDamge = 10;
    _goldReward = 10;
    _isClear = false;
}

MonsterCyclops::~MonsterCyclops()
{
}

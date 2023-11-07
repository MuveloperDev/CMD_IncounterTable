#include "MonsterParasiticBat.h"

MonsterParasiticBat::MonsterParasiticBat(MonsterType InType) :
    MonsterBase(0, 0, 0, 0, false, R"(




    _________))                ((__________
   /.-------./\\    \    /    //\.--------.\
  //#######//##\\   ))  ((   //##\\########\\
 //#######//###((  ((    ))  ))###\\########\\
((#######((#####\\  \\  //  //#####))########))
 \##' `###\######\\  \)(/  //######/####' `##/
  )'  ``#)' `##\`-&gt;oo&lt;-'/##' `(#''   `(
          (       ``\`..'/''       )
                     \""(
                      `- )
                      / /
                     ( /\
                     /\| \
                    (  \
                        )
                       /
                      (
)", InType, "PARASITE BAT")
{
    _maxHp = 100;
    _hp = _maxHp;
    _attackDamge = 10;
    _goldReward = 10;
    _isClear = false;
}

MonsterParasiticBat::~MonsterParasiticBat()
{
}

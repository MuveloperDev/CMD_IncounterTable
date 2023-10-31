#include "MonsterSkeleton.h"


MonsterSkeleton::MonsterSkeleton(MonsterType InType) :
    MonsterBase(0, 0, 0, 0, false, R"(



                                                            :::!~!!!!!:.
                                                        .xUHWH!! !!?M88WHX:.
                                                      .X*#M@$!!  !X!M$$$$$$WWx:.
                                                     :!!!!!!?H! :!$!$$$$$$$$$$8X:
                                                    !!~  ~:~!! :~!$!#$$$$$$$$$$8X:
                                                   :!~::!H!&lt;   ~.U$X!?R$$$$$$$$MM!
                                                   ~!~!!!!~~ .:XW$$$U!!?$$$$$$RMM!
                                                     !:~~~ .:!M"T#$$$$WX??#MRRMMM!
                                                     ~?WuxiW*`   `"#$$$$8!!!!??!!!
                                                   :X- M$$$$       `"T#$T~!8$WUXU~
                                                  :%`  ~#$$$m:        ~!~ ?$$$$$$
                                                :!`.-   ~T$$$$8xx.  .xWW- ~""##*"
                                      .....   -~~:&lt;` !    ~?T#$$@@W@*?$$      /`
                                    //W$@@M!!! .!~~ !!     .:XUW$W!~ `"~:    :
                                    //#"~~`.:x%`!!  !H:   !WM$$$$Ti.: .!WUn+!`
                                    //:::~:!!`:X~ .: ?H.!u "$$$B$$$!W:U!T$$M~
                                    //.~~   :X@!.-~   ?@WTWo("*$$$W$TH$! `
                                    //Wi.~!X$?!-~    : ?$$$B$Wu("**$RM!
)", InType, "SKELETON")
{
    _maxHp = 100;
    _hp = _maxHp;
    _attackDamge = 10;
    _goldReward = 10;
    _isClear = false;
}

MonsterSkeleton::~MonsterSkeleton()
{}

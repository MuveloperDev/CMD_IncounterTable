#pragma once
#include "MonsterBase.h"

class MonsterBigFoot : public MonsterBase
{
public:
	MonsterBigFoot(MonsterType InType);
	~MonsterBigFoot();
	void Render();
};


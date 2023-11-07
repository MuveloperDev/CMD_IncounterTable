#pragma once
#include "Enum.h"
#include <iostream>
#include <windows.h>
#include <winnt.h>
#include <stdio.h>
#include <cstdlib> // for system
class ItemBase
{
public:
	ItemBase(ItemType InType, __int32 InPrice);
	~ItemBase();
	virtual void Use();
	void AddCount(__int32 InCount);
	ItemType& GetType();
	__int32 GetCount();
	__int32 GetPrice();
	void SetCount(__int32 InAdd);
	void ReplaceCount(__int32 InAdd);
protected:
	ItemType _type;
	__int32 _count;
	__int32 _price;
};


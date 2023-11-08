#pragma once
#include "Enum.h"
#include <iostream>
#include <windows.h>
#include <winnt.h>
#include <stdio.h>
#include <cstdlib> // for system
#include <string>
class ItemBase
{
public:
	ItemBase(ItemType InType, __int32 InPrice);
	~ItemBase();
	virtual void Use(__int32 InCnt);
	void AddCount(__int32 InCount);
	ItemType& GetType();
	__int32 GetCount();
	__int32 GetPrice();
	std::string& GetDescription();
	void SetCount(__int32 InAdd);
	void ReplaceCount(__int32 InAdd);
protected:
	ItemType _type;
	std::string _description;
	__int32 _count;
	__int32 _price;

protected:
	void SetDescription(std::string& InDescription);
};


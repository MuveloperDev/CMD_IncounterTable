#include "ItemBase.h"

ItemBase::ItemBase(ItemType InType, __int32 InPrice):
	_type(InType), _count(2), _price(InPrice)
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::Use(__int32 InCnt)
{
}

void ItemBase::AddCount(__int32 InCount)
{
	_count += InCount;
}

ItemType& ItemBase::GetType()
{
	return _type;
}

__int32 ItemBase::GetCount()
{
	return _count;
}

__int32 ItemBase::GetPrice()
{
	return _price;
}

std::string& ItemBase::GetDescription()
{
	return _description;
}

void ItemBase::SetCount(__int32 InAdd)
{
	_count += InAdd;
}

void ItemBase::ReplaceCount(__int32 InAdd)
{
	_count = InAdd;
}

void ItemBase::SetDescription(std::string& InDescription)
{
	_description = InDescription;
}

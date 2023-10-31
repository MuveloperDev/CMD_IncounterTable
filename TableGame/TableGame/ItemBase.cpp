#include "ItemBase.h"

ItemBase::ItemBase(ItemType InType, __int32 InPrice):
	_type(InType), _count(0), _price(InPrice)
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::Use()
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

void ItemBase::SetCount(__int32 InAdd)
{
	_count += InAdd;
}

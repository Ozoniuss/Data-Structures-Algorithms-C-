#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	first();
}
//theta(1) complexity all cases

void MapIterator::first() 
{
	current = map.head;
}
//theta(1) all cases

void MapIterator::next()
{
	if (!valid())
		throw std::exception("Invalid iterator!");
	current = current->next;
}
//theta(1) all cases

TElem MapIterator::getCurrent()
{
	if (!valid())
		throw std::exception("Invalid iterator!");
	return current->key_value;
}
//theta(1) all cases

bool MapIterator::valid() const
{
	return current != nullptr;
}
//theta(1) all cases



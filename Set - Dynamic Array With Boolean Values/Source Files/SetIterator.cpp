#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m)
{
	current_element = 0;
}


void SetIterator::first()
{
	current_element = 0;
}
//BC = WC = Th(1)


void SetIterator::next()
{
	//find the next true value from the vector
	while (current_element < set.capacity)
	{
		current_element++;
		if (set.elements[current_element] == true)
		{
			break;
		}
	}
}
//BC = Th(1), WC =Th(cap), AC = O(cap) 


TElem SetIterator::getCurrent()
{
	return set.lowest_element + current_element;
}
//BC = WC = Th(1)

bool SetIterator::valid() const 
{
	if (set.elements[current_element] == true)
		return true;
	else
		return false;
}
//BC = WC = Th(1)


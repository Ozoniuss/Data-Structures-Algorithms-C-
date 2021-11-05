#pragma once
#include "Set.h"

class SetIterator
{
	friend class Set;

private:
	const Set& set;
	SetIterator(const Set& s);

	int current_element = 0;
	//iterate from the first element of the array

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};



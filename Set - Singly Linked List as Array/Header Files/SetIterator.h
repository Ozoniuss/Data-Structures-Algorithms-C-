#pragma once
#include "Set.h"

class SetIterator
{
	friend class Set;
private:
	const Set& set;
	int current;

	SetIterator(const Set& s) : set{ s }, current{ s.headPos } {}

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};



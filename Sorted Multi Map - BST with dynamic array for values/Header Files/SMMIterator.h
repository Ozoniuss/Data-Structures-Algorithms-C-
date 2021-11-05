#pragma once

#include "SortedMultiMap.h"
#include <stack>
//using an inorder iterator
using std::stack;

class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
	stack<int> s;
	int currentPos;
	int currentValuePos;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

class ValueIterator
{
	friend class SortedMultiMap;
private:
	const SortedMultiMap& map;
	ValueIterator(const SortedMultiMap& map, TKey k);
	int key;
	int length;
	int current;
	vector<TValue> elements;
public:
	void first();
	void next();
	bool valid() const;
	TValue getCurrent() const;
};


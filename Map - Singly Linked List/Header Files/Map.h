#pragma once
#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111)
class MapIterator;

typedef bool(*Condition)(TValue);

class Map {
	friend class MapIterator;

private:
	
	//representation of a Node
	struct Node 
	{
		TElem key_value;
		Node* next;
	};

	Node* head;
	Node* tail;
	int length;

public:

	//constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed or NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

	// destructor
	~Map();

	//keeps in the Map only those pairs whose value respects the given condition
	void filter(Condition cond);

};




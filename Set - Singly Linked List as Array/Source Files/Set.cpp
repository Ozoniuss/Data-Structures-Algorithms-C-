#include "Set.h"
#include "SetITerator.h"
#include <exception>

Set::Set() {
	capacity = 4; // initial capacity
	elems = new TElem[capacity];
	nextPos = new TElem[capacity];
	headPos = -1;
	tailPos = -1;
	length = 0;
	for (int i = 0; i < capacity - 1; i++)
		nextPos[i] = i + 1; // fill the vector containing the indexes of the next position
	nextPos[capacity-1] = -1;
	firstEmptyPos = 0; // the position of the next available position in the set
}
//Th(capacity)

bool Set::add(TElem elem) {

	if (length == 0)
	{
		elems[firstEmptyPos] = elem;
		headPos = firstEmptyPos;
		tailPos = headPos;
		firstEmptyPos = nextPos[firstEmptyPos];
		nextPos[headPos] = -1;
		length++;
		return true;
	}

	if (search(elem) == true) { return false; }

	// no available positions means that we need to resize
	if (firstEmptyPos == -1)
	{
		TElem* new_elems = new TElem[capacity * 2];
		int* new_next = new int[capacity * 2];
		for (int i = 0; i < capacity; i++)
		{
			new_elems[i] = elems[i];
			new_next[i] = nextPos[i];
		}
		for (int i = capacity; i < capacity * 2-1; i++)
		{
			new_next[i] = i + 1;
		}
		new_next[capacity * 2 - 1] = -1;
		delete[] elems;
		delete[] nextPos;
		elems = new_elems;
		nextPos = new_next;
		firstEmptyPos = capacity; //the next empty position is going to be the first position 
		capacity = capacity * 2;  //resize if size is too big
	}

	//now add the element
	elems[firstEmptyPos] = elem;
	nextPos[tailPos] = firstEmptyPos;
	tailPos = firstEmptyPos;
	firstEmptyPos = nextPos[firstEmptyPos];
	nextPos[tailPos] = -1;
	length++;
	return true;
	
}
//BC = WC = AC = O(n) amortized because of the search function

bool Set::remove(TElem elem) {
	if (length == 0)
		return false;

	int currentPos = headPos; // current position of the element
	int previousPos = -1;

	//one element
	if (length == 1 && elems[headPos] != elem)
		return false;

	if (length == 1 && elems[headPos] == elem)
	{
		nextPos[headPos] = firstEmptyPos;
		firstEmptyPos = headPos;
		headPos = -1;
		tailPos = -1;
		length = 0;
		return true;
	}

	//find the position of the element and the previous position
	while (currentPos != -1 && elems[currentPos] != elem)
	{
		previousPos = currentPos;
		currentPos = nextPos[currentPos];
	}

	// found
	if (currentPos != -1)
	{
		if (currentPos == headPos)
			headPos = nextPos[headPos];
		else
			nextPos[previousPos] = nextPos[currentPos];
		if (currentPos == tailPos)
		{
			tailPos = previousPos;
			nextPos[tailPos] = -1;
		}
		nextPos[currentPos] = firstEmptyPos;
		firstEmptyPos = currentPos; // first empty position is the position at which the element was deleted
		length--;
		return true;
	}
	else
		return false;
}
//BC = TH(1) if you remove the head
//WC = TH(n) if you remove the tail
//AC = O(n)

bool Set::search(TElem elem) const {
	int currentPos = headPos; //loop through the elements to find its position using the nextPos vector 
	while (currentPos != -1 and elems[currentPos] != elem)
	{
		currentPos = nextPos[currentPos];
	}
	if (currentPos != -1)
		return true;
	else
		return false;
}
//BC = Th(1) if found at the beginning
//WC = Th(n) if not found
//AC = O(n)

int Set::size() const {
	return length;
}
//Th(1)

bool Set::isEmpty() const {
	if (length == 0)
		return true;
	return false;
}
//Th(1)

Set::~Set() {
	delete[] elems;
	delete[] nextPos;
}
//Th(1)

//this is actually pretty simple -- keep removing only the first element, which just changes the headposition and firstempty position
void Set::empty()
{
	if (length != 0)
	{
		int aux = elems[headPos];
		while (length != 0)
		{
			remove(aux);
			aux = elems[headPos];
		}
	}
}
//Th(n) because the function calls remove for the first element for each element, so Th(1)*nr_of_elems

SetIterator Set::iterator() const {
	return SetIterator(*this);
}
//Th(1)


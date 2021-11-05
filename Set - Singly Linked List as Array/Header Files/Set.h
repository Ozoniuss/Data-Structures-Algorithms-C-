#pragma once

#define NULL_TELEM -111111
typedef int TElem;
class SetIterator;

class Set {
	friend class SetIterator;

    private:
        TElem* elems;
        int* nextPos;
        int capacity;
        int headPos;
        int tailPos;
        int firstEmptyPos;
        int length;

    public:
        //constructor
        Set();

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
        bool add(TElem e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        bool remove(TElem e);

        //checks whether an element belongs to the set or not
        bool search(TElem elem) const;

        //returns the number of elements;
        int size() const;

        //check whether the set is empty or not;
        bool isEmpty() const;

        //return an iterator for the set
        SetIterator iterator() const;

        // destructor
        ~Set();

        //empty the set
        void empty();

};






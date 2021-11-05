#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
#define DELETED_TELEM -1
#define NULL_LINE -1
#define NULL_COLUMN -1

struct Triplet
{
	int line;
	int column;
	TElem value;
};


struct HashTable
{
	int size;
	int capacity;
	Triplet* elements;
};


class Matrix {

private:
	int nrL;
	int nrC;
	HashTable table;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

public:

	int simpleHash(int line, int column, int capacity) const;
	int hash(int pos, int line, int column, int capacity) const;
	double loadFactor() const { return (float) table.size / table.capacity; } 
	void resizeDimension(int newLines, int newCols);

	void resize();


};

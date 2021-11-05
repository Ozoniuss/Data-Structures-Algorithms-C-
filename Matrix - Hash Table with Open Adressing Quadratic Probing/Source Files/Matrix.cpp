#include "Matrix.h"
#include <exception>
using namespace std;

//implemented as a hash table using open addressing - quadratic probing

Matrix::Matrix(int nrLines, int nrCols) : nrL{ nrLines }, nrC{nrCols}
{
	table.size = 0;
	table.capacity = 2;
	table.elements = new Triplet[table.capacity];
	for (int i = 0; i < table.capacity; i++)
	{
		table.elements[i].value = NULL_TELEM;    //initialize matrix, empty hash table
		table.elements[i].line = NULL_LINE;
		table.elements[i].column = NULL_COLUMN;
	}
}
//Th(Caacity) for ovious reasons

int Matrix::nrLines() const {
	return nrL;
}
//Th(1)

int Matrix::nrColumns() const {
	return nrC;
}
//Th(1)

//find the element at position i,j
TElem Matrix::element(int i, int j) const {
	if (i >= nrL || j >= nrC || i < 0 || j < 0)
		throw exception(); //invalid indices

	if (table.size == 0) { return NULL_TELEM; }
	
	int step = 0;
	int pos = hash(step, i, j, table.capacity);
	while (table.elements[pos].value != NULL_TELEM) //if we found NULL_TELEM it means that the element was not found
	{                                               //in the probe sequence, if we find DELETED we keep searching
													//DELETED is used to denote an element that was there, but deleted, to avoid stopping through the sequence
		                                            //in case some element was removed
		if ((table.elements[pos].line == i) && (table.elements[pos].column == j))
		{
			if (table.elements[pos].value != DELETED_TELEM) //found
				return table.elements[pos].value;
			else
				return NULL_TELEM;
		}
		step++;

		pos = hash(step, i, j, table.capacity);   //increment step, search through the probe sequence
	}
	return NULL_TELEM; //not found
}
//BEST: TH(1) - element found directly
//WORST: TH(capacity) - highly unlikey, actually worst case load_factor*capacity steps 
//AVERAGE: TH(1)

TElem Matrix::modify(int i, int j, TElem e) {
	if (i >= nrL || j >= nrC || i < 0 || j <0)
		throw exception();
	if (loadFactor() > 0.7) // keep load factor under .7
		resize();

	if (e == NULL_TELEM)  //delete
	{
		int step = 0;
		int pos = hash(step, i, j, table.capacity);
		while (table.elements[pos].value != NULL_TELEM) 
		{                                              
			if ((table.elements[pos].line == i) && (table.elements[pos].column == j) && (table.elements[pos].value != DELETED_TELEM))
				//found the element, it is not deleted
			{
				TElem old = table.elements[pos].value;
				table.elements[pos].value = DELETED_TELEM; //do not remove the values of the line and column, since it helps with complexity
				//also set is at DELETED_TELEM to mark the probing sequence is not finished
				table.size--;
				return old;
			}
			else if ((table.elements[pos].line == i) && (table.elements[pos].column == j) && (table.elements[pos].value == DELETED_TELEM))
			{
				return NULL_TELEM; //found the element, but it was deleted previously
			}
			step++;
			pos = hash(step, i, j, table.capacity);   //search the probe sequence
		}
		return NULL_TELEM; //element not found, it is not in hash
	}

	else if (e != NULL_TELEM) //add or update
	{
		int step = 0;
		int pos = hash(step, i, j, table.capacity);
		while ((table.elements[pos].value != NULL_TELEM) && step < table.capacity)
		{
			if ((table.elements[pos].line == i) && (table.elements[pos].column == j) && (table.elements[pos].value != DELETED_TELEM)) 
				//found the element, it is not deleted
			{
				TElem old = table.elements[pos].value;
				table.elements[pos].value = e; //element not deleted, modify it
				return old;
			}
			else if ((table.elements[pos].line == i) && (table.elements[pos].column == j) && (table.elements[pos].value == DELETED_TELEM))
			{
				table.elements[pos].value = e; //elemment is deleted, just modify its value
				table.size++;
				return NULL_TELEM;
			}
			step++;
			pos = hash(step, i, j, table.capacity);   //search the probe sequence
		}
		table.elements[pos].line = i;
		table.elements[pos].column = j;
		table.elements[pos].value = e;
		table.size++;
		return NULL_TELEM;
	}
}
//BC: TH(1) - delete when the probing sequence starts with NULL, add when probing starts with NULL, update when prob. starts with elem etc
//WC: TH(cap) - any operation when the corresponding element is at the end of the probing sequence and literally all elements have the same simple hash function value
//AC: TH(1)


int Matrix::simpleHash(int line, int column, int capacity) const
{
	return (line * column) % capacity;
}
//TH(1)

//we choose c1=c2=0.5 in the quadratic probing function so we always have a permutation
int Matrix::hash(int step, int line, int column, int capacity) const
{
	return (simpleHash(line, column, capacity) + (step + step * step) / 2) % capacity;
}
//TH(1)

void Matrix::resizeDimension(int newLines, int newCols)
{
	if (newLines <= 0 || newCols <= 0)
		throw exception();
	if (newLines >= nrLines() && newCols >= nrColumns())
	{
		nrL = newLines;
		nrC = newCols;
		return;
	}
	for (int i = 0; i <= table.capacity; i++)
	{
		if ((table.elements[i].line >= newLines) || (table.elements[i].column >= newCols))
		{
			table.elements[i].value = DELETED_TELEM;
		}
		nrL = newLines;
		nrC = newCols;
		return;
	}
}
//complexity: Th(capacity)

void Matrix::resize()
{
	Triplet* new_elements = new Triplet[table.capacity * 2]; // create a new resized table
	for (int i = 0; i < table.capacity * 2; i++)
	{
		new_elements[i].value = NULL_TELEM;
		new_elements[i].line = NULL_LINE;
		new_elements[i].column = NULL_COLUMN;
	}
	table.size = 0;

	//rehash
	for (int i = 0; i < table.capacity; i++)
	{
		Triplet el = table.elements[i];
		if ((el.value != NULL_TELEM) && (el.value != DELETED_TELEM))
		{
			int step = 0;
			int pos = hash(step, el.line, el.column, table.capacity*2);
			while (new_elements[pos].value != NULL_TELEM) //while occupied, loop through the probing sequence
			{
				step++;
				pos = hash(step, el.line, el.column, table.capacity * 2);
			}
			new_elements[pos] = el;
			table.size++;
		}
	}
	Triplet* aux{ table.elements };
	table.elements = new_elements;
	delete[] aux;
	table.capacity = table.capacity * 2;
}
//Best case: TH(capacity)
//worst case: TH(capacity^2) - If every element has the same value for the simple hash function (well not really capacity^2, but rather constant*capacity^2)


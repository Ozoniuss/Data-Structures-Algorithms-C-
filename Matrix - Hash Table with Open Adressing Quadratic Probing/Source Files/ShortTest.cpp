#include <assert.h>
#include "Matrix.h"
#include <iostream>
using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);

	m.resizeDimension(10, 10);
	assert(m.nrLines() == 10);
	assert(m.nrColumns() == 10);
	assert(m.element(8, 8) == NULL_TELEM);
	assert(m.element(1, 1) == 6);

	m.modify(3, 3, 69);
	assert(m.element(3, 3) == 69);

	m.resizeDimension(2, 2);
	assert(m.nrLines() == 2);
	try
	{
		m.element(2, 2);
	}
	catch (...)
	{
		cout<<"Invalid column and line" << endl;
	}
	m.resizeDimension(4, 4);
	assert(m.element(3, 3) == NULL_TELEM); // verify if element was actually deleted
	assert(m.element(1, 1) == 6);
}
#include "Set.h"
#include "SetITerator.h"

//implemented using a dynamic array of boolean values

Set::Set() 
{
	capacity = 1; // capacity of the dynamic array
	elements = new v[capacity];
	elements[0] = false;
	lenght_of_elements = 0; //number of elements
}


bool Set::add(TElem elem)
{

	
	if (lenght_of_elements == 0)
	{
		lowest_element = elem;
		biggest_element = elem;
		elements[0] = true;
		lenght_of_elements = 1;
		return true;
	}
	

	//add the element in between the first and last, no resize
	if (elem >= lowest_element && elem <= biggest_element)
	{
		if (search(elem) == true)
			return false;
		elements[elem - lowest_element] = true;
		lenght_of_elements++;
		return true;

	}

	//add the element in front + resize + shift
	if (elem < lowest_element)
	{
		int new_capacity = biggest_element - elem + 1;
		v* temporary = new v[new_capacity]; //create a vector with new capacity
		for (int i = 0; i < capacity; i++)
			temporary[i] = elements[i];

		for (int i = capacity; i < new_capacity; i++)
			temporary[i] = false;

		delete(elements);
		elements = temporary; //shift the elements to the right in the new array
		
		int shift = new_capacity - capacity;
		
		for (int i = new_capacity-1; i >=shift; i--)
		{
			elements[i] = elements[i - shift];
		}
		for (int i = 0; i < shift; i++)
			elements[i] = false;

		capacity = new_capacity;
		elements[0] = true; // the new element is the first
		lowest_element = elem;
		lenght_of_elements++;
		return true;
	}

	//add the element to the back + resize, but no shift
	if (elem > biggest_element)
	{
		int new_capacity = elem - lowest_element + 1;
		v* temporary = new v[new_capacity];

		//resize
		for (int i = 0; i < capacity; i++)
			temporary[i] = elements[i];
		for (int i = capacity; i < new_capacity; i++)
			temporary[i] = false;

		delete(elements);
		elements = temporary;
		capacity = new_capacity;
		elements[new_capacity - 1] = true; //set the last value to true
		biggest_element = elem;
		lenght_of_elements++;
		return true;
	}
	return false;
}
//BC = Th(1)
//WC = Th(newCapacityAfterResize) (if elements is smaller than first or larger than last)
//AC = O(newCapacityAfterResize) (BC or WC, no between)



bool Set::remove(TElem elem) 
{
	//straightforward
	if (lenght_of_elements == 0)
		return false;
	if (search(elem) == false)
		return false;

	if (lenght_of_elements == 1)
	{
		elements[0] = false;
		lenght_of_elements--;
		return true;
	}
	
	//in between, no resize
	if (elem > lowest_element && elem < biggest_element)
	{
		elements[elem - lowest_element] = false;
		lenght_of_elements--;
		return true;
	}

	// first element + resize
	if (elem == lowest_element)
	{
		TElem new_lowest_element; //find the next lowest element
		for (int i = 1; i < capacity; i++)
		{
			if (elements[i] == true)
			{
				new_lowest_element = lowest_element + i;
				break;
			}
		}
		
		//resize
		int new_capacity = biggest_element - new_lowest_element + 1;
		v* temporary = new v[new_capacity];
		for (int i = 0; i < new_capacity; i++)
		{
			temporary[i] = elements[i + capacity - new_capacity];
		}
		delete(elements);
		elements = temporary;

		lowest_element = new_lowest_element;//set new lowest element and capacity
		capacity = new_capacity;
		lenght_of_elements--;
		return true;
	}


	// last element + resize
	if (elem == biggest_element)
	{
		//find new biggest element
		TElem new_biggest_element;
		for (int i = 1; i < capacity; i++)
		{
			if (elements[(capacity-1)-i] == true)
			{
				new_biggest_element = biggest_element - i;
				break;
			}
		}
		
		//resize
		int new_capacity = new_biggest_element - lowest_element + 1;
		v* temporary = new v[new_capacity];
		for (int i = 0; i < new_capacity; i++)
		{
			temporary[i] = elements[i];
		}
		delete(elements);
		elements = temporary;

		//set new biggest element and capacity
		biggest_element = new_biggest_element;
		capacity = new_capacity;
		lenght_of_elements--;
		return true;
	}
	return false;
}
//BC = Th(1)
//WC = Th(capacity)+Th(newCapacityAfterResize)
//AC = O(capacity) + Th(newCapacityAfterResize) (Th(1) if element between first and last or not in list)

bool Set::search(TElem elem) const 
{
	if (lenght_of_elements == 0)
		return false;
	if (elem < lowest_element || elem > biggest_element)
		return false;
	if (elements[elem - lowest_element] == true)
		return true;
	return false;
}
//BC = WC = AC = Th(1)

int Set::size() const
{
	return lenght_of_elements;
}
//BC = WC = AC = Th(1)

bool Set::isEmpty() const
{
	if (lenght_of_elements == 0)
		return true;
	else
		return false;
}
//BC = WC = AC = Th(1)

Set::~Set()
{
	delete[] elements;
}


SetIterator Set::iterator() const 
{
	return SetIterator(*this);
}
//BC = WC = AC = Th(1)

void Set::filter(Condition cond)
{
	if (lenght_of_elements == 1 && cond(elements[0]) == false)
		this->remove(elements[0]);

	if (lenght_of_elements == 2)
	{
		if (cond(elements[capacity - 1]) == false)
			this->remove(elements[capacity - 1]);
		if (cond(elements[0]) == false)
			this->remove(elements[0]);
	}
	
	if (lenght_of_elements > 2)
	{
		int for_lenght = capacity;

		//this will not change size during iteration because elements are between first and second
		for (int i = 1; i < for_lenght - 1; i++)
		{
			if (elements[i] == true)
			{
				if (cond(elements[i]) == false)
					this->remove(elements[i]);
			}
		}
		
		//both of these will change size so perform them last
		if (cond(elements[capacity - 1]) == false)
			this->remove(elements[capacity - 1]);
		if (cond(elements[0]) == false)
			this->remove(elements[0]);
		
	
	}
	//BC=WC=AC= Th(capacity * cond_complexity) ~ Th(capacity)
	

}



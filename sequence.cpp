// BRADLEY HALL
// 10/20/16
// ASSIGNMENT_5 IMPEMENTATION OF SEQUENCE


//#include "sequence.h"
#include "node2.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#define _SCL_SECURE_NO_WARNINGS

using namespace std;

namespace NSU_DATA_STRUCTURES
{

	// sequence constructor - set private members to null
	template <class Item>
	sequence<Item>::sequence()
	{
		head_ptr = NULL;
		tail_ptr = NULL;
		cursor = NULL;
		precursor = NULL;
		many_nodes = 0;
	}
	// sequence copy constructor - copys one sequence to another. 
	template <class Item>
	sequence<Item>::sequence(const sequence& source)
	{


		if (this == &source)
		{
			return;
		}
		else
		{
			list_copy(source.head_ptr, head_ptr, tail_ptr);
			if (source.precursor == NULL)
			{
				if (source.cursor == NULL)
				{
					cursor = NULL;
					precursor = NULL;
				}
				else
				{
					cursor = head_ptr;
					precursor = NULL;
				}
			}
			else
			{
				node<Item> *temp = head_ptr;
				node<Item> *sourcePtr = source.head_ptr;
				while (sourcePtr != source.precursor)
				{
					sourcePtr = sourcePtr->link();
					temp = temp->link();
				}
				cursor = temp->link();
				precursor = temp;
			}
		}
		many_nodes = source.many_nodes;

	}
	// sequence deconstructor
	template <class Item>
	sequence<Item>::~sequence()
	{
		list_clear(head_ptr);
		many_nodes = 0;
	}
	// start method - moves the cursor to the beginning of the list
	template <class Item>
	void sequence<Item>::start()
	{
		if (head_ptr == NULL && tail_ptr == NULL)
		{
			return;
		}

		cursor = head_ptr;
		precursor = NULL;
	}
	// advance method - moves cursor forward and precursor gets cursor
	template <class Item>
	void sequence<Item>::advance()
	{
		precursor = cursor;
		cursor = cursor->link();
	}
	// insert method - inserts a new link into list with the specified data.
	template <class Item>
	void sequence<Item>::insert(const value_type& entry)
	{

		if (precursor == NULL || !is_item()) 
		{
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;

			if (many_nodes == 0) 
			{
				tail_ptr = head_ptr;
			}
		}

		else 
		{
			list_insert(precursor, entry);
			cursor = precursor->link();
		}

		many_nodes++;
	}
	// attach method - attaches a new link to list with the specified data
	template <class Item>
	void sequence<Item>::attach(const value_type& entry)
	{
		if (is_item()) 
		{
			if (cursor == tail_ptr) 
			{
				list_insert(cursor, entry);
				precursor = cursor;
				cursor = cursor->link();
				tail_ptr = tail_ptr->link();
			}

			else 
			{
				list_insert(cursor, entry);
				precursor = cursor;
				cursor = cursor->link();
			}
		}
		if (!is_item()) 
		{
			if ((head_ptr == NULL) && (tail_ptr == NULL)) {
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				precursor = NULL;
				tail_ptr = head_ptr;
			}

			else 
			{
				precursor = list_locate(head_ptr, list_length(head_ptr));
				list_insert(precursor, entry);
				cursor = precursor->link();
				tail_ptr = tail_ptr->link();
			}
		}
		many_nodes++;
	}
	// remove_current method - removes the currrent item in the linked list
	template <class Item>
	void sequence<Item>::remove_current()
	{
		node<Item> *aNode;
		aNode = NULL;

		if (cursor == head_ptr) 
		{
			if (many_nodes > 1) 
			{
				list_head_remove(head_ptr);
				cursor = head_ptr;
				precursor = NULL;
			}
			else 
			{
				list_head_remove(head_ptr);
				cursor = precursor = head_ptr = tail_ptr = NULL;
			}
		}
		else 
		{
			cursor = cursor->link();
			list_remove(precursor);
		}
		many_nodes--;
	}
	// overloaded assignment operator 
	template <class Item>
	void sequence<Item>::operator=(const sequence<Item>& source)
	{
		if (this == &source)
		{
			return;
		}
		
		else
		{
			list_clear(head_ptr);
			precursor = cursor = head_ptr = tail_ptr = NULL;
			many_nodes = 0;
			list_copy(source.head_ptr, head_ptr, tail_ptr);
			if (source.precursor == NULL)
			{
				if (source.cursor == NULL)
				{
					cursor = NULL;
					precursor = NULL;
				}
				else
				{
					cursor = head_ptr;
					precursor = NULL;
				}
			}
			else
			{
				node<Item> *temp = head_ptr;
				node<Item> *sourcePtr = source.head_ptr;
				while (sourcePtr != source.precursor)
				{
					sourcePtr = sourcePtr->link();
					temp = temp->link();
				}
				cursor = temp->link();
				precursor = temp;
			}
		}
		many_nodes = source.many_nodes;
	}
	// current method - returns the data of the current item
	template <class Item>
	Item sequence<Item>::current() const
	{
		return cursor->data();
	}


}

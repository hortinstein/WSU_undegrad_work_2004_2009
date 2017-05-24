#ifndef LIST_H    // include guard
#define LIST_H

///////////////////////////////////////////////////////////////////////////////
/// \class        List
/// \author       Alex Hortin 
/// \date         Febuary 6 2006
/// \brief        A doubly linked list of ListNodes
///
/// A list that supports iterator operations and is doubly linked.  It stores
/// soundfiles, and has a variety of iterator based modifications with it.
///
/// REVISION HISTORY
///
/// 2/6/2006  Began Implementation and definition of class
///
/// 2/16/2006 Templating the class began
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

#include <iostream>
#include <stdexcept>
#include <vector>
// LOCAL INCLUDES
//
#include "ListIterator.h"//the iterator
#include "ListNode.h"//the node to be defined

// FORWARD REFERENCES
//
template< class Element > class ListIterator;
// CONSTANTS
//

template <class Element >
class List
{
   public:
   
	typedef unsigned long size_type;
   typedef ListIterator<Element> iterator;
	
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the List class with no elements.
	///         Sets head and tail equal to head since they are dummy nodes.
   /// \param  None
   /// \throw  None
  List( void );
  
   /// Copy Constructor.
   /// \pre    An instance of List needs to be present.
   /// \post   Two instances of the same List will exist.
   /// \param  List is the List to copy from.
   /// \throw  None
   List(const List<Element> & from );

   /// Destructor.
   /// \pre    An instance of List has been created.
   /// \post   The instance of List is destroyed.
   ~List( void );
	
// OPERATORS

   /// Assignment operator.
   /// \param  rhs is the object to assign from.
   /// \return A reference to this Vec.
   List& operator=(const List<Element> & rhs ); 
	 
// OPERATIONS 
  
// ACCESS and MUTATE
   
	/// push_back
   /// \pre    A valid Soundfile
   /// \post   A new Soundfile will be appended to the list
   /// \param  a Soundfile
   /// \return None
   /// \throw  None
   void push_back(const Element & sf );
	
	/// insert
   /// \pre    A valid iterator and soundfile
   /// \post   A new file will be inserted
   /// \param  an iterator containing target in playlist
	/// \param  a soundfile to insert
   /// \return an iterator representing the new position of the new soundfile
   /// \throw  None
   ListIterator<Element > insert(ListIterator<Element > it, const Element & sf);
	
	/// erase
   /// \pre    A valid iterator and soundfile
   /// \post   A new file will be inserted
   /// \param  iterator containing target in playlist
   /// \return the position of the next soundfile in the list after the one that got erased. 
   /// \throw  None
   ListIterator<Element > erase(ListIterator<Element > it);
	
// INQUIRY
   
	/// size
   /// \pre    A valid playlist
   /// \post   none
   /// \param  none
   /// \return an unsigned int containing number of soundfiles
   /// \throw  None
   size_type size(void);
	
	/// begin
   /// \pre    A valid playlist
   /// \post   none
   /// \param  none
   /// \return a List Iterator containing pointing to the beginning Soundfile
   /// \throw  None
   ListIterator<Element > begin(void);
	
	/// end
   /// \pre    A valid playlist
   /// \post   none
   /// \param  none
   /// \return a List Iterator containing pointing to the end dummy file
   /// \throw  None
   ListIterator<Element > end(void) const;
	
		/// begin
   /// \pre    A valid playlist
   /// \post   none
   /// \param  none
   /// \return a List Iterator containing pointing to the beginning Soundfile
   /// \throw  None
   ListIterator<Element > begin(void) const;
	
	/// end
   /// \pre    A valid playlist
   /// \post   none
   /// \param  none
   /// \return a List Iterator containing pointing to the end dummy file
   /// \throw  None
   ListIterator<Element > end(void);

// MEMBER VARIABLES
private:
   //the head of the list
	ListNode<Element>* mHead;

	//the tail of the list
	ListNode<Element>* mTail;
	
	//number of Soundfiles stored
	size_type mSize;
   

}; // end of class Soundfile


///////////////////////////////////////////////////////////////////////////////
/// \class        List
/// \author       Alex Hortin 
/// \date         Febuary 6 2006
/// \brief        A doubly linked list of ListNodes
///
/// A list that supports iterator operations and is doubly linked.  It stores
/// soundfiles, and has a variety of iterator based modifications with it.
///
/// REVISION HISTORY
///
/// 2/6/2006  Began Implementation and definition of class
///        
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

// CONSTANTS
//

// LIFECYCLE

///////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the List class with no elements.
///         Sets head and tail equal to head since they are dummy nodes.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
List<Element >::List( void )
{
	this->mHead = new ListNode<Element>;
	this->mTail = mHead;
	this->mSize = 0;
}

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of List needs to be present.
/// \post   Two instances of the same List will exist.
/// \param  List is the List to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
List<Element >::List(const List<Element > & from )
{
	this->mHead = new ListNode<Element>;
	this->mTail = mHead;
	this->mSize = 0;
	
	ListIterator<Element > temp_it = from.begin();
	while (temp_it != from.end())
	{
		push_back((*temp_it));
		temp_it++;
	}
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of List has been created.
/// \post   The instance of List is destroyed.
///////////////////////////////////////////////////////////////////////
template < class Element >
List<Element >::~List( void )
{
	ListNode<Element >* temp_ptr1 = this->mHead;
	ListNode<Element >* temp_ptr2;
	while (temp_ptr1 != this->mTail)
	{
		temp_ptr2 = temp_ptr1->next;
		delete temp_ptr1;
		temp_ptr1 = temp_ptr2;
	}
	delete mTail;
}

// OPERATORS

///////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \param  rhs is the object to assign from.
/// \return A reference to this Vec.
///////////////////////////////////////////////////////////////////////
template < class Element >
List<Element >& List<Element >::operator=(const List<Element> & rhs )
{
	if (rhs.mHead != this->mHead)
	{	
		ListNode<Element >* temp_ptr1 = this->mHead;
		ListNode<Element >* temp_ptr2;
		while (temp_ptr1 != this->mTail)
		{
			temp_ptr2 = temp_ptr1->next;
			delete temp_ptr1;
			temp_ptr1 = temp_ptr2;
		}
		delete mTail;
		
		this->mHead = new ListNode<Element >;
		this->mTail = mHead;
		this->mSize = 0;
		
		ListIterator<Element > temp_it = rhs.begin();
		while (temp_it != rhs.end())
		{
			push_back((*temp_it));
			temp_it++;
		}
	}
	return *this;
}
// OPERATIONS

// ACCESS and MUTATE

///////////////////////////////////////////////////////////////////////
/// push_back
/// \pre    A valid Soundfile
/// \post   A new Soundfile will be appended to the list
/// \param  a Soundfile
/// \return None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
void List<Element >::push_back(const Element & sf )
{
	ListNode<Element >* temp = new ListNode<Element >;
	temp->prev = NULL;
	temp->elem = sf;
	temp->next = NULL;
	
	if (mTail != mHead)
	{
		mTail->prev->next = temp;
		temp->prev = mTail->prev;
		temp->next = mTail;
		mTail->prev = temp;
	}
	else
	{
		mTail->prev = temp;
		temp->next = mTail;
		mHead = temp;	
	}
	this->mSize++;
}

///////////////////////////////////////////////////////////////////////
/// insert
/// \pre    A valid iterator and soundfile
/// \post   A new file will be inserted
/// \param  an iterator containing target in playlist
/// \param  a soundfile to insert
/// \return an iterator representing the new position of the new soundfile
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator<Element > List<Element >::insert(ListIterator<Element> it, const Element & sf)
{
	ListNode<Element >* temp = new ListNode<Element >;
	
	if (it == this->begin() && it == this->end())
	{
		mTail->prev = temp;
		mHead = temp;
		temp->prev = NULL;
	}
	else if (it == this->begin())
	{
		it.mIterator->prev = temp;	
		mHead = temp;
		temp->prev = NULL;
	}
	else
	{
		it.mIterator->prev->next = temp;
		temp->prev = (it.mIterator)->prev;
		it.mIterator->prev = temp;		
	}
	
	temp->elem = sf;
	temp->next = (it.mIterator);
	
	ListIterator<Element > temp_iter;
	temp_iter.mIterator = temp;
	this->mSize++;
	return temp_iter;
}

///////////////////////////////////////////////////////////////////////
/// erase
/// \pre    A valid iterator and soundfile
/// \post   A new file will be inserted
/// \param  iterator containing target in playlist
/// \return the position of the next soundfile in the list after the one that got erased.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator<Element > List<Element >::erase(ListIterator<Element > it)
{
	if (it == this->end())
	{
		return end();
	}
	else if (it == this->begin())
	{
		mHead = it.mIterator->next;
		it.mIterator->next->prev = NULL;
	}
	else
	{
		ListNode<Element>* temp_prev = it.mIterator->prev;
		ListNode<Element>* temp_next = it.mIterator->next;
		 
		it.mIterator->prev->next = temp_next;
		it.mIterator->next->prev = temp_prev;
	}
	
	this->mSize--;
	ListIterator<Element> temp_iter;
	temp_iter.mIterator = it.mIterator->next;
	delete it.mIterator;
	
	return temp_iter;
}
// INQUIRY

///////////////////////////////////////////////////////////////////////
/// size
/// \pre    A valid playlist
/// \post   none
/// \param  none
/// \return an unsigned int containing number of soundfiles
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
typename List< Element >::size_type List<Element >::size(void)
{
	return mSize;
}

///////////////////////////////////////////////////////////////////////
/// begin
/// \pre    A valid playlist
/// \post   none
/// \param  none
/// \return a List Iterator containing pointing to the beginning Soundfile
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator<Element > List<Element >::begin(void)
{
	ListIterator<Element > it;
	it.mIterator = mHead;
	return it;
}

///////////////////////////////////////////////////////////////////////
/// end
/// \pre    A valid playlist
/// \post   none
/// \param  none
/// \return a List Iterator containing pointing to the end dummy file
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator< Element > List< Element >::end(void)
{
	ListIterator<Element > it;
	it.mIterator = mTail;
	return it;
}

///////////////////////////////////////////////////////////////////////
/// begin
/// \pre    A valid playlist
/// \post   none
/// \param  none
/// \return a List Iterator containing pointing to the beginning Soundfile
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator<Element > List<Element >::begin(void) const
{
	ListIterator<Element > it;
	it.mIterator = mHead;
	return it;
}

///////////////////////////////////////////////////////////////////////
/// end
/// \pre    A valid playlist
/// \post   none
/// \param  none
/// \return a List Iterator containing pointing to the end dummy file
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator< Element > List< Element >::end(void) const
{
	ListIterator<Element > it;
	it.mIterator = mTail;
	return it;
}


#endif  // List.h

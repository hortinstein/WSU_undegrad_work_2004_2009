#ifndef LISTITERATOR_H    // include guard
#define LISTITERATOR_H

///////////////////////////////////////////////////////////////////////////////
/// \class        ListIterator
/// \author       Alex Hortin 
/// \date         Febuary 6 2006
/// \brief        an iterator class to target List
///
/// An iterator that can be used to modify and target the class List.  It
/// will be used to taget the list and for a variety of functionality within
/// playlist.  
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

#include "ListNode.h"//the node to be defined
// FORWARD REFERENCES
//

template< class Element > class List;
// CONSTANTS
//

template <class Element >
class ListIterator : public std::iterator< std::forward_iterator_tag, Element >
{
   public:
   
	friend class List<Element>;

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the ListIterator class with no position in any list.
   /// \param  None
   /// \throw  None
  ListIterator( void );
  
// OPERATORS
   
   /// equality operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   NONE
   /// \param  An element of a List.
   /// \return bool based on whether it is equal or not
   /// \throw  NONE   
   bool operator==( const ListIterator & rhs ) const;
   
   /// non-equality operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   NONE
   /// \param  An element of a List.
   /// \return bool based on whether it is equal or not
   /// \throw  NONE   
   bool operator!=( const ListIterator & rhs ) const; 
   
   /// pre incriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the next value.
   /// \param  A ListIterator that calls it
   /// \return A refence to itself
   /// \throw  NONE
   ListIterator & operator++( void );

   /// pre decriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the previous value.
   /// \param  A vector that calls it
   /// \return A refence to itself
   /// \throw  NONE
   ListIterator & operator--( void );
	   
   /// post incriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the next value.
   /// \param  A ListIterator that calls it
   /// \return The next value
   /// \throw  NONE  
   ListIterator operator++( int );

	/// post decriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the previous value.
   /// \param  A vector that calls it
   /// \return The next value
   /// \throw  NONE  
   ListIterator operator--( int );
	
	/// Reference operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a vector.
   /// \return A refence to that element
   /// \throw  NONE
   Element &  operator*( void ) const;
   
   /// -> operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a vector.
   /// \return A pointer to that element denoted by the iterator
   /// \throw  NONE 
   Element * operator->( void ) const;

	
// OPERATIONS 
  
// ACCESS and MUTATE
   
// INQUIRY
   
// MEMBER VARIABLES
private:
	//The node that it points too
   ListNode<Element> * mIterator;
   
}; // end of class ListIterator


///////////////////////////////////////////////////////////////////////////////
/// \class        ListIterator
/// \author       Alex Hortin
/// \date         Febuary 6 2006
/// \brief        an iterator class to target List
///
/// An iterator that can be used to modify and target the class List.  It
/// will be used to taget the list and for a variety of functionality within
/// playlist.
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

///////////////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the ListIterator class with no position in any list.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////////////
template <class Element >
ListIterator<Element >::ListIterator( void )
{
	mIterator = NULL;
}

// OPERATORS

///////////////////////////////////////////////////////////////////////////////
/// equality operator.
/// \pre    The target must be assigned a value in memory.
/// \post   NONE
/// \param  An element of a List.
/// \return bool based on whether it is equal or not
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
bool ListIterator<Element >::operator==( const ListIterator<Element > & rhs ) const
{
	if (this->mIterator == rhs.mIterator)//comparing the iterators
   {
      return true;
   }
   else
   {
      return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
/// non-equality operator.
/// \pre    The target must be assigned a value in memory.
/// \post   NONE
/// \param  An element of a List.
/// \return bool based on whether it is equal or not
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
bool ListIterator<Element >::operator!=( const ListIterator<Element > & rhs ) const
{
   if (this->mIterator != rhs.mIterator)//comparing the iterators
   {
      return true;
   }
   else
   {
      return false;
   }
}

///////////////////////////////////////////////////////////////////////////////
/// pre incriment operator.
/// \pre    The iterator must point to a value.
/// \post   The iterator moves to the next value.
/// \param  A ListIterator that calls it
/// \return A refence to itself
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator<Element > & ListIterator<Element >::operator++( void )
{
   this->mIterator = mIterator->next;
   return *this;//incrimenting the iterator
}

///////////////////////////////////////////////////////////////////////////////
/// pre decriment operator.
/// \pre    The iterator must point to a value.
/// \post   The iterator moves to the previous value.
/// \param  A vector that calls it
/// \return A refence to itself
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator<Element > & ListIterator<Element >::operator--( void )
{
   this->mIterator = mIterator->prev;
   return *this;//decrimenting the iterator
}

///////////////////////////////////////////////////////////////////////////////
/// post incriment operator.
/// \pre    The iterator must point to a value.
/// \post   The iterator moves to the next value.
/// \param  A ListIterator that calls it
/// \return The next value
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator<Element > ListIterator<Element >::operator++( int )
{
   ListIterator temp;
   temp.mIterator = mIterator;
   this->mIterator = this->mIterator->next;//incrimenting the iterator
   return temp;
}

///////////////////////////////////////////////////////////////////////////////
/// post decriment operator.
/// \pre    The iterator must point to a value.
/// \post   The iterator moves to the previous value.
/// \param  A ListIterator that calls it
/// \return The next value
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
ListIterator< Element > ListIterator< Element >::operator--( int )
{
	ListIterator temp;
   temp.mIterator = mIterator;
  	this->mIterator = this->mIterator->prev;//incrimenting the iterator
   return temp;
}

///////////////////////////////////////////////////////////////////////////////
/// Reference operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a ListIterator.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
Element &  ListIterator<Element>::operator*( void ) const
{
	return mIterator->elem;//returning the reference
}

///////////////////////////////////////////////////////////////////////////////
/// -> operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a ListIterator.
/// \return A pointer to that element denoted by the iterator
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
Element * ListIterator<Element>::operator->( void ) const
{
	return &(mIterator->elem);//returning the pointer
}

// OPERATIONS

// ACCESS and MUTATE

// INQUIRY

#endif  // ListIterator.h

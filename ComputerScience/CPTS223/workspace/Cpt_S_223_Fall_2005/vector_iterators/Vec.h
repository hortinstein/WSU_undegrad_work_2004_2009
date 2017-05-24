#ifndef VEC_H    // include guard
#define VEC_H
///////////////////////////////////////////////////////////////////////////////
/// \class        Vec
/// \author       Alex Hortin (Originally Created by Kelly Fitz)
/// \date         9/7/05
/// \brief        A lousy vector implementation to get you started.
///
/// This class is a vector that is built to act just like the standard library
/// vector class.  It was built from a shell given to us by Kelly Fitz.  
///       
/// REVISION HISTORY:
///
/// 9/19/05    Improved the Vec Class to act more like the standard library.
///            I also removed Kelly's unnecissary commentary and variables that 
///            will not apply to my finished Vec class.
///
/// 9/27/05    Added begin, insert, end, and erase, also corrected tests.
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

#include <iostream>
#include <stdexcept>

// LOCAL INCLUDES
//
//the sample sound player

// FORWARD REFERENCES
//
template< class Element > class VecIterator;

// CONSTANTS
//



// We are not worrying about template classes yet.
// Define the Element type here.
//#ifndef ELEMENT_TYPE
//#include <string>
//typedef std::string Element;
//#else
//typedef ELEMENT_TYPE Element;
//#endif

template < class Element >
class Vec 
{
   public:
   
   typedef unsigned long size_type;
   typedef VecIterator<Element> iterator;
 
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Vec class with 0 elements is created.
   /// \param  None
   /// \throw  None
   Vec( void );
   
   /// constructor with size given
   /// \pre    None
   /// \post   An instance of the Vec class with a user specified number of
   ///         elements is created.
   /// \param  None
   /// \throw  None
   Vec(size_type n);

   /// Copy Constructor.
   /// \pre    An instance of Vec needs to be present.
   /// \post   Two instances of the same Vec will exist.
   /// \param  Vec is the Vec to copy from.
   /// \throw  None
   Vec( const Vec & from );

   /// Destructor.
   /// \pre    An instance of PlaybackWindow has been created.
   /// \post   The instance of PlaybackWindow is destroyed.
   ~Vec( void );

// OPERATORS

   /// Assignment operator.
   /// THIS DOESN'T WORK YET!
   /// \param  rhs is the object to assign from.
   /// \return A reference to this Vec.
   Vec& operator=( const Vec & rhs );  

   /// Subscript operator (non-const).
   /// Provide access to the element at the specified rank.
   /// \pre    idx must be less than the number of elements
   ///         stored in the vector, or else it will crash!
   ///         FIX ME so I do something more sensible!
   /// \param  idx is the rank of the element to access
   /// \return access to the element at rank `idx'.
   Element & operator[]( size_type idx );  

   /// Subscript operator (const).   
   /// Provide read-only access to the element at the specified rank.
   /// \pre    idx must be less than the number of elements
   ///         stored in the vector, or else it will crash!
   ///         FIX ME so I do something more sensible!
   /// \param  idx is the rank of the element to access
   /// \return read-only access to the element at rank `idx'.
   const Element & operator[]( size_type idx ) const;  

// OPERATIONS 

   /// push_back
   /// \pre    A Vec must exist to make the call.
   /// \post   The vector has a new element appended to it and possibly
   ///         allocate more memory.  (Double what the number of elements were
   ///         before to insure n performance.)
   /// \param  An element to be appended onto the vector
   /// \return None
   /// \throw  None
   void push_back(Element E);

   /// pop_back
   /// \pre    The array where elements are stored must have something in it.
   /// \post   The last element is removed.
   /// \param  None
   /// \return None
   /// \throw  None
   void pop_back(void);
   
   /// front (const)
   /// \pre    The array where elements are stored must have something in it.
   /// \post   None
   /// \param  None
   /// \return A reference to the starting element of the array
   /// \throw  domain error if the array has nothing in it
   const Element& front(void) const;
   
   /// front 
   /// \pre    The array where elements are stored must have something in it.
   /// \post   None
   /// \param  None
   /// \return A reference to the starting element of the array
   /// \throw  domain error if the array has nothing in it
   Element& front(void);
   
   /// back (const)
   /// \pre    The array where elements are stored must have something in it.
   /// \post   None
   /// \param  None
   /// \return A const reference to the end element of the array
   /// \throw  domain error if the array has nothing in it
   const Element& back(void) const;
   
   /// back
   /// \pre    The array where elements are stored must have something in it.
   /// \post   None
   /// \param  None
   /// \return A reference to the end element of the array
   /// \throw  domain error if the array has nothing in it
   Element& back(void);
   
   /// begin 
   /// \pre    The array where elements are stored must have something in it.
   /// \post   None
   /// \param  None
   /// \return An iterator pointin g to the starting element of the array
   /// \throw  NONE
   VecIterator< Element > begin(void); 

   /// end 
   /// \pre    The array where elements are stored must have something in it.
   /// \post   None
   /// \param  None
   /// \return An iterator pointin g to the ending element of the array
   /// \throw  NONE
   VecIterator< Element > end(void); 
// ACCESS and MUTATE
  
   /// empty (const)
   /// \pre    Their must be an array where elements can be stored.
   /// \post   None
   /// \param  None
   /// \return A bool for the array being full or not.
   /// \throw  None
   bool empty();
   
   /// empty (const)
   /// \pre    Their must be an array where elements can be stored.
   /// \post   None
   /// \param  None
   /// \return A bool for the array being full or not.
   /// \throw  None
   bool empty() const;
   
   /// clear
   /// \pre    Their must be an array where elements can be stored.
   /// \post   The array's elements are removed.
   /// \param  None
   /// \return None
   /// \throw  None
   void clear(void);

   /// resize
   /// \pre    Their must be an array where elements can be stored.
   /// \post   The array's values are all initialized to zero.
   /// \param  A new size for the array.
   /// \return None
   /// \throw  None
   void resize(size_type new_size); 
   
   /// insert (range)
   /// \pre    Their must be an array with which to insert data.
   /// \post   An array with data is inserted
   /// \param  None
   /// \return None
   /// \throw  None
   void insert( VecIterator< Element > it, VecIterator< Element > it_start, VecIterator< Element > it_end);
   
   /// insert
   /// \pre    Their must be an array with which to insert data.
   /// \post   An array with data is inserted
   /// \param  None
   /// \return None
   /// \throw  None
   VecIterator< Element > insert(VecIterator< Element > it, const Element e);
 
   /// erase
   /// \pre    Their must be an array with which to insert data.
   /// \post   An array with data is inserted
   /// \param  None
   /// \return None
   /// \throw  None
   VecIterator< Element > erase( VecIterator< Element > it);
   
// INQUIRY
   /// size
   /// \pre    Their must be an array where elements can be stored.
   /// \post   None
   /// \param  None
   /// \return The number of elements in the vector.
   /// \throw  None
   size_type size( void ) const;
   
   
// MEMBER VARIABLES
private:

   /// contents of the vector
   Element * mArray;
   
   /// size of vector memory
   size_type mArraySize;
   
   /// number of elements stored in the vector
   size_type mNumElements;

}; // end of class Vec


///////////////////////////////////////////////////////////////////////////////
/// \class        VecIterator
/// \author       Alex Hortin
/// \date         9/26/05
/// \brief        A standard lib vector iterator implementation.
///
/// This class is a vector that is built to act just like the standard library
/// vector iterator class.  It was built using the Vec class we created in 
/// project 3.  The Vec class is included within this assignment in Vec.h.  
///       
/// REVISION HISTORY:
///
/// 
///            
///////////////////////////////////////////////////////////////////////////////
template < class Element >
class VecIterator
{

   friend class Vec< Element >;
   public:
   // LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Vec class with 0 elements is created.
   /// \param  None
   /// \throw  None
   VecIterator( void );

   /// Copy Constructor.
   /// \pre    An instance of VecIterator needs to be present.
   /// \post   Two instances of the same VecIterator will exist.
   /// \param  VecIterator is the VecIterator to copy from.
   /// \throw  None
   VecIterator( const VecIterator & from );

   /// Destructor.
   /// \pre    An instance of VecIterator has been created.
   /// \post   The instance of VecIterator is destroyed.
   ~VecIterator( void );

// OPERATORS
   
   /// Assignment operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a vector.
   /// \return A refence to that element
   /// \throw  NONE
   const VecIterator &  operator=( const VecIterator & rhs );
   
   /// Reference operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a vector.
   /// \return A refence to that element
   /// \throw  NONE
   Element &  operator*( void );
   
   /// -> operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a vector.
   /// \return A pointer to that element denoted by the iterator
   /// \throw  NONE 
   Element * operator->( void );
   
   /// pre incriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the next value.
   /// \param  A vector that calls it
   /// \return A refence to itself
   /// \throw  NONE
   VecIterator & operator++( void );
   
   /// post incriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the next value.
   /// \param  A vector that calls it
   /// \return The next value
   /// \throw  NONE  
   VecIterator operator++( int );
   
   /// pre decriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the previous value.
   /// \param  A vector that calls it
   /// \return A refence to itself
   /// \throw  NONE
   VecIterator & operator--( void );
   
   /// post decriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the previous value.
   /// \param  A vector that calls it
   /// \return The next value
   /// \throw  NONE  
   VecIterator operator--( int );
   
   /// equality operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   NONE
   /// \param  An element of a vector.
   /// \return bool based on whether it is equal or not
   /// \throw  NONE   
   bool operator==( const VecIterator & rhs );
   
   /// non-equality operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   NONE
   /// \param  An element of a vector.
   /// \return bool based on whether it is equal or not
   /// \throw  NONE   
   bool operator!=( const VecIterator & rhs );

// OPERATIONS 


// ACCESS and MUTATE
  

   
// INQUIRY



// MEMBER VARIABLES

private:
   Element * mIterator;
   unsigned int mPosition;

}; // end of class VecIterator

#endif

///////////////////////////////////////////////////////////////////////////////
/// \class        Vec
/// \author       Alex Hortin (Originally Created by Kelly Fitz)
/// \date         9/7/05
/// \brief        A lousy vector implementation to get you started.
///
/// This class is a vector that is built to act just like the standard library
/// vector class.  It was built from a shell given to us by Kelly Fitz.  
///       
/// REVISION HISTORY:
///
/// 9/19/05    Improved the Vec Class to act more like the standard library.
///            I also removed Kelly's unnecissary commentary and variables that 
///            will not apply to my finished Vec class.
///
/// 9/26/05    Debugged the Vec according to test's.
///            
///////////////////////////////////////////////////////////////////////////////

                       // class implemented

// SYSTEM INCLUDES
//


// PUBLIC 

// LIFECYCLE 

///////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the Vec class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
Vec< Element >::Vec( void ) :
   mArray(0),
   mArraySize(0),
   mNumElements(0)
{

} // End constructor

///////////////////////////////////////////////////////////////////////
/// constructor with size given
/// \pre    None
/// \post   An instance of the Vec class with a user specified number of
///         elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
Vec< Element >::Vec(size_type n )
{
   mArray = new Element[n];
   mArraySize = n;
   mNumElements = n;
} // End constructor

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of Vec needs to be present.
/// \post   Two instances of the same Vec will exist.
/// \param  Vec is the Vec to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
Vec< Element >::Vec( const Vec & from )
{
   this->mArray = new Element[from.mArraySize];
   for (size_type i = 0; i < from.mNumElements; i++)
   {
      this->mArray[i] = from.mArray[i];//copying all elements over
   }
   this->mNumElements = from.mNumElements;
   this->mArraySize = from.mArraySize;
} // end copy constructor

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of Vec has been created.
/// \post   The instance of Vec is destroyed.
///////////////////////////////////////////////////////////////////////
template < class Element >
Vec< Element >::~Vec( void )
{
   delete [] mArray;

} // end destructor

// OPERATORS 

///////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    A vector is created
/// \post   A reference to the copy is returned  
/// \param  rhs is the object to assign from.
/// \return A reference to this Vec.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
Vec< Element >& Vec< Element >::operator=( const Vec &  rhs )
{
   this->mArray = new Element[rhs.mArraySize];
   for (size_type i = 0; i < rhs.mNumElements; i++)
   {
      this->mArray[i] = rhs.mArray[i];//copying all elements over
   }
   this->mNumElements = rhs.mNumElements;
   this->mArraySize = rhs.mArraySize;
   return *this;
} // end assignment operator

///////////////////////////////////////////////////////////////////////
/// Subscript operator (non-const).
/// \pre    idx must be less than the number of elements
///         stored in the vector,
/// \post   A reference of the element is returned  
/// \param  idx is the rank of the element to access
/// \return access to the element at rank `idx'.
/// \throw  An error if index is out of bounds
///////////////////////////////////////////////////////////////////////
template < class Element >
Element & Vec< Element >::operator[]( Vec::size_type idx )
{
   if ( idx >= mArraySize )//if index is greater or equal to mNumelements
   {
      throw std::out_of_range("Index is greater than the amount of elements in the Vector");//throwing an exception
   }
   return mArray[ idx ];
}

///////////////////////////////////////////////////////////////////////
/// Subscript operator (const).
/// \pre    idx must be less than the number of elements
///         stored in the vector,
/// \post   A reference of the element is returned  
/// \param  idx is the rank of the element to access
/// \return read-only access to the element at rank `idx'.
/// \throw  An error if index is out of bounds
///////////////////////////////////////////////////////////////////////
template < class Element >
const Element & Vec< Element >::operator[]( Vec::size_type idx ) const
{
   if ( idx >= mArraySize )//if index is greater or equal to mNumelements
   {
      throw std::out_of_range("Index is greater than the amount of elements in the Vector");//throwing an exception
   }
   return mArray[ idx ];
}

// OPERATIONS 
///////////////////////////////////////////////////////////////////////
/// push_back
/// \pre    A Vec must exist to make the call.
/// \post   The vector has a new element appended to it and possibly
///         allocate more memory.  (Double what the number of elements were
///         before to insure n performance.)
/// \param  An element to be appended onto the vector
/// \return None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
void Vec< Element >::push_back(Element E)
{
   
   if (mArraySize == 0)
   {
      mArraySize = 1;
      Element *new_array = new Element[mArraySize*2];//creating a new array two times larger than the old one
         
      mArraySize = mArraySize * 2;
         
      mArray = new_array;
         
      mArray[mNumElements] = E;//setting the new value to the next spot in the array and incrimenting mNumElements
   }
   else if (mNumElements < mArraySize)
   {
      mArray[mNumElements] = E;
   }
   else if (mNumElements >= mArraySize)//if array is out of space
   {
      
      Element *new_array = new Element[mArraySize*2];//creating a new array two times larger than the old one
      
      for (size_type i = 0; i < this->mNumElements; i++)
      {
         new_array[i] = this->mArray[i];//copying all old stuff over into new array
      }
      
      mArraySize = mArraySize * 2;
      delete [] mArray;
      mArray = new_array;
      mArray[mNumElements] = E;//setting the new value to the next spot in the array and incrimenting mNumElements
   } 
   mNumElements++;
  
}
///////////////////////////////////////////////////////////////////////
/// pop_back
/// \pre    The array where elements are stored must have something in it.
/// \post   The last element is removed.
/// \param  None
/// \return None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
void Vec< Element >::pop_back(void)
{
   Element empty;
   if (mNumElements != 0)
   {
      mNumElements--;
   }
   mArray[mNumElements] = empty;   
}

///////////////////////////////////////////////////////////////////////
/// front (const)
/// \pre    The array where elements are stored must have something in it.
/// \post   None
/// \param  None
/// \return A reference to the starting element of the array
/// \throw  domain error if the array has nothing in it
///////////////////////////////////////////////////////////////////////
template < class Element >
const Element& Vec< Element >::front(void) const
{
   if (mNumElements == 0)
   {
      throw std::domain_error("Vector is empty");//throwing an exception
   }
   else 
   {
      return mArray[0];
   }
}

///////////////////////////////////////////////////////////////////////
/// front 
/// \pre    The array where elements are stored must have something in it.
/// \post   None
/// \param  None
/// \return A reference to the starting element of the array
/// \throw  domain error if the array has nothing in it
///////////////////////////////////////////////////////////////////////
template < class Element >
Element& Vec< Element >::front(void)
{
   if (mNumElements == 0)
   {
      throw std::domain_error("Vector is empty");//throwing an exception
   }
   else 
   {
      return mArray[0];
   }
}

///////////////////////////////////////////////////////////////////////
/// back (const)
/// \pre    The array where elements are stored must have something in it.
/// \post   None
/// \param  None
/// \return A const reference to the end element of the array
/// \throw  domain error if the array has nothing in it
///////////////////////////////////////////////////////////////////////
template < class Element >
const Element& Vec< Element >::back(void) const
{
   if (mNumElements == 0)
   {
      throw std::domain_error("Vector is empty");//throwing an exception
   }
   else 
   {
      return mArray[mNumElements - 1];
   }
}

///////////////////////////////////////////////////////////////////////
/// back
/// \pre    The array where elements are stored must have something in it.
/// \post   None
/// \param  None
/// \return A reference to the end element of the array
/// \throw  domain error if the array has nothing in it
///////////////////////////////////////////////////////////////////////
template < class Element >
Element& Vec< Element >::back(void)
{
   if (mNumElements == 0)
   {
      throw std::domain_error("Vector is empty");//throwing an exception
   }
   else 
   {
      return mArray[mNumElements - 1];
   }
}

///////////////////////////////////////////////////////////////////////
/// begin 
/// \pre    The array where elements are stored must have something in it.
/// \post   None
/// \param  None
/// \return An iterator pointin g to the starting element of the array
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element> Vec< Element >::begin(void)
{
   VecIterator<Element> it; 
   
   it.mIterator = mArray;
   it.mPosition = 0;
   
   return it;
} 

///////////////////////////////////////////////////////////////////////
/// end 
/// \pre    The array where elements are stored must have something in it.
/// \post   None
/// \param  None
/// \return An iterator pointin g to the ending element of the array
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element> Vec< Element >::end(void)
{
   VecIterator<Element> temp;
   temp.mIterator = (mArray + mNumElements );//+ 1);// - 1);
   temp.mPosition = mNumElements + 1;// - 1;
   return temp;
}

// ACCESS and MUTATE
///////////////////////////////////////////////////////////////////////
/// empty 
/// \pre    Their must be an array where elements can be stored.
/// \post   None
/// \param  None
/// \return A bool for the array being full or not.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
bool Vec< Element >::empty()
{
   if (mNumElements == 0)//checking to see if there is anything in the array
   {
      return true;
   }
   else
   {
      return false;
   }
}


///////////////////////////////////////////////////////////////////////
/// empty (const)
/// \pre    Their must be an array where elements can be stored.
/// \post   None
/// \param  None
/// \return A bool for the array being full or not.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
bool Vec< Element >::empty() const
{
   if (mNumElements == 0)//checking to see if there is anything in the array
   {
      return true;
   }
   else
   {
      return false;
   }
}

///////////////////////////////////////////////////////////////////////
/// clear
/// \pre    Their must be an array where elements can be stored.
/// \post   The array's elements are removed.
/// \param  None
/// \return None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
void Vec< Element >::clear(void)
{
   mNumElements = 0;
}
///////////////////////////////////////////////////////////////////////
/// resize
/// \pre    Their must be an array where elements can be stored.
/// \post   The array's values are all initialized to zero.
/// \param  A new size for the array.
/// \return None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
void Vec< Element >::resize(size_type new_size)
{
   Element empty;
   
   if (mArraySize == 0)
   {
      mArraySize = new_size;
      Element *new_array = new Element[mArraySize];//creating a new array two times larger than the old one
         
         
      mArray = new_array;
      mNumElements = mArraySize;
   }
   else if (new_size <= mArraySize && new_size < mNumElements)
   {
      mNumElements = new_size;
   }
   else
   {
      Element *new_array = new Element[new_size];//creating a new array two times larger than the old one
      size_type i;
      for (i = 0;i<mNumElements-1;i++)
      {
         new_array[i] = mArray[i];//copying the new array
      }
      mArraySize = new_size;
      delete [] mArray;
      mArray = new_array;//setting the array to the new array
      mNumElements = mArraySize;
   }
}
///////////////////////////////////////////////////////////////////////
/// insert (range)
/// \pre    Their must be an array with which to insert data.
/// \post   An array with data is inserted and the pointer Iterator is invalid
/// \param  Iterator I for the position to insert in
/// \param  Iterator i_start for the beginning of the range
/// \param  Iterator i_end for the end of the range
/// \return None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
void Vec< Element >::insert( VecIterator<Element> it, VecIterator<Element> i_start, VecIterator<Element> i_end)
{
   VecIterator<Element> temp = it;
   int loop_time = (i_end.mPosition-i_start.mPosition);
   Element e;
   for (int i = 0; i < loop_time - 1;i++)
   {
      e = *(i_start.mIterator + i);
      temp = insert(temp, e);
      temp++;
   }   
}
///////////////////////////////////////////////////////////////////////
/// insert
/// \pre    Their must be an array with which to insert data.
/// \post   An array with data is inserted
/// \param  An Element that is to be insterted
/// \param  Iterator I for the position to insert in
/// \return a pointer to the new value
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element> Vec< Element >::insert(VecIterator<Element> it, const Element e)
{
   int temp = mNumElements;
   push_back(e);
   Element *dest = mArray + it.mPosition;
   int i;
   for (i = temp; &mArray[i] > dest; --i)
   {
      mArray[i] = mArray[i-1];
   }
   mArray[i] = e;
   VecIterator<Element> return_temp;
   
   return_temp.mPosition = it.mPosition;
   return_temp.mIterator = this->mArray + it.mPosition;
   return return_temp;
}

/////////////////////////////////////////////////////////////////////// 
/// erase
/// \pre    Their must be an array with which to insert data.
/// \post   An array with data is inserted
/// \param  None
/// \return None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element> Vec< Element >::erase( VecIterator<Element> it)
{
   if (it != this->end())
   {
      //Element temp_default;
      unsigned int i;
      for (i = (it.mPosition + 1);  i < mNumElements ; ++i)
      {
         mArray[i-1] = mArray[i];
      }
      mNumElements--;
      //mArray[i] = temp_default;
   }
   VecIterator<Element> return_temp;
   return_temp.mIterator = this->mArray + it.mPosition;
   return_temp.mPosition = it.mPosition;
   
   return return_temp;
}

// INQUIRY 

///////////////////////////////////////////////////////////////////////
/// size
/// \pre    Their must be an array where elements can be stored.
/// \post   None
/// \param  None
/// \return The number of elements in the vector.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
typename Vec< Element >::size_type Vec< Element >::size( void ) const
{
   return mNumElements;
}   



///////////////////////////////////////////////////////////////////////////////
/// \class        VecIterator
/// \author       Alex Hortin
/// \date         9/26/05
/// \brief        A standard lib vector iterator implementation.
///
/// This class is a vector that is built to act just like the standard library
/// vector iterator class.  It was built using the Vec class we created in 
/// project 3.  The Vec class is included within this assignment in Vec.h.  
///       
/// REVISION HISTORY:
///
/// 
///            
///////////////////////////////////////////////////////////////////////////////

// LIFECYCLE

/// Default constructor.
/// \pre    None
/// \post   An instance of the Vec class with 0 elements is created.
/// \param  None
/// \throw  None
template < class Element >
VecIterator<Element>::VecIterator( void )
{
   mIterator = NULL;
   this->mPosition = 0;
}

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of VecIterator needs to be present.
/// \post   Two instances of the same VecIterator will exist.
/// \param  VecIterator is the VecIterator to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element>::VecIterator( const VecIterator & from )
{
   this->mIterator = from.mIterator; 
   this->mPosition = from.mPosition; 
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of VecIterator has been created.
/// \post   The instance of VecIterator is destroyed.
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element>::~VecIterator( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a vector.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template < class Element >
const VecIterator<Element> &  VecIterator<Element>::operator=( const VecIterator & rhs )
{
   this->mIterator = rhs.mIterator;
   this->mPosition = rhs.mPosition;
   return rhs;//assinging the new value over
}

///////////////////////////////////////////////////////////////////////
/// Reference operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a vector.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template < class Element >
Element &  VecIterator<Element>::operator*( void )
{
   return *mIterator;//returning the reference
}

///////////////////////////////////////////////////////////////////////
/// -> operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a vector.
/// \return A pointer to that element denoted by the iterator
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template < class Element >
Element * VecIterator<Element>::operator->( void )
{
   return mIterator;//returning the pointer
}

///////////////////////////////////////////////////////////////////////
/// pre incriment operator.
/// \pre    The iterator must point to a value.
/// \post   The iterator moves to the next value.
/// \param  A vector that calls it
/// \return A refence to itself
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element> & VecIterator<Element>::operator++( void )
{
   this->mIterator++;
   this->mPosition++;
   return *this;//incrimenting the iterator
}

///////////////////////////////////////////////////////////////////////
/// post incriment operator.
/// \pre    The iterator must point to a value.
/// \post   The iterator moves to the next value.
/// \param  A vector that calls it
/// \return The next value
/// \throw  NONE  
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element> VecIterator<Element>::operator++( int )
{
   VecIterator<Element> temp;
   temp.mIterator = mIterator;
   temp.mPosition = mPosition;
   this->mIterator++;//incrimenting the iterator
   this->mPosition++;
   return temp;
}

///////////////////////////////////////////////////////////////////////
/// pre decriment operator.
/// \pre    The iterator must point to a value.
/// \post   The iterator moves to the previous value.
/// \param  A vector that calls it
/// \return A refence to itself
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element> & VecIterator<Element>::operator--( void )
{
   this->mIterator--;
   this->mPosition--;
   return *this;//decrimenting the iterator
}

///////////////////////////////////////////////////////////////////////
/// post decriment operator.
/// \pre    The iterator must point to a value.
/// \post   The iterator moves to the previous value.
/// \param  A vector that calls it
/// \return The next value
/// \throw  NONE  
///////////////////////////////////////////////////////////////////////
template < class Element >
VecIterator<Element> VecIterator<Element>::operator--( int )
{
   VecIterator<Element> temp;
   temp.mIterator = mIterator;
   temp.mPosition = mPosition;
   mIterator--;//incrimenting the iterator
   this->mPosition--;
   return temp;
}

///////////////////////////////////////////////////////////////////////   
/// equality operator.
/// \pre    The target must be assigned a value in memory.
/// \post   NONE
/// \param  An element of a vector.
/// \return bool based on whether it is equal or not
/// \throw  NONE   
///////////////////////////////////////////////////////////////////////
template < class Element >
bool VecIterator<Element>::operator==( const VecIterator<Element> & rhs )
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

///////////////////////////////////////////////////////////////////////
/// non-equality operator.
/// \pre    The target must be assigned a value in memory.
/// \post   NONE
/// \param  An element of a vector.
/// \return bool based on whether it is equal or not
/// \throw  NONE   
///////////////////////////////////////////////////////////////////////
template < class Element >
bool VecIterator<Element>::operator!=( const VecIterator<Element> & rhs )
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

// OPERATIONS 


// ACCESS and MUTATE
  

   
// INQUIRY

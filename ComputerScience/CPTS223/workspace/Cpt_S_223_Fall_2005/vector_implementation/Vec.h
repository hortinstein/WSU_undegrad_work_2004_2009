
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
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

#include <iostream>
#include <stdexcept>

// LOCAL INCLUDES
//
#include "Vec.h"//the sample sound player

// FORWARD REFERENCES
//

// CONSTANTS
//



// We are not worrying about template classes yet.
// Define the Element type here.
#ifndef ELEMENT_TYPE
#include <string>
typedef std::string Element;
#else
typedef ELEMENT_TYPE Element;
#endif

class Vec 
{
   public:
   
   typedef unsigned long size_type;

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

#endif  // VEC_H


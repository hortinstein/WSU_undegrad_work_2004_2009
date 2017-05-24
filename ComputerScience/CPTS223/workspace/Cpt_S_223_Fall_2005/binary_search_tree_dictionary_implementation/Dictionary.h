///////////////////////////////////////////////////////////////////////////////
/// \class        NonexistentElementException
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that stores a pointer to the position.
///
/// This class is one the stores a position of a node in the tree.  It is an 
/// interface tool for the client.
///       
/// REVISION HISTORY:
///
///   NONE
///            
///////////////////////////////////////////////////////////////////////////////


#ifndef DICTIONARY_H    // include guard
#define DICTIONARY_H

//SYSTEM INCLUDES
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <math.h>
// LOCAL INCLUDES
//
#include "BinaryTree.h"
#include "Dictionary.h"

// FORWARD REFERENCES
//

//FUNCTIONS
//

// CONSTANTS
//


template <class Key,class Element> class Dictionary;
// CONSTANTS
//
struct NonexistentElementException : public std::logic_error
{
// LIFECYCLE
   
   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Position class with 0 elements is created.
   /// \param  a string
   /// \throw  none silly it is an error
   NonexistentElementException(std::string error): logic_error(error)
   {}

// OPERATORS

// OPERATIONS 
   
// ACCESS and MUTATE

// INQUIRY

}; // end of class NonexistentElementException

///////////////////////////////////////////////////////////////////////////////
/// \class        Pair
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that stores a pointer to the position.
///
/// This class is one the stores a position of a Pair in the Dictionary.  It is
/// an interface tool for the client.
///       
/// REVISION HISTORY:
///
///   NONE
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

template < class Key, class Element >
class cPair
{
   public:
// LIFECYCLE
   
   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Position class with 0 elements is created.
   /// \param  None
   /// \throw  None
   cPair(void);
   
   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Position class with 0 elements is created.
   /// \param  None
   /// \throw  None
   cPair(Key, Element);

   /// Copy Constructor.
   /// \pre    An instance of Position needs to be present.
   /// \post   Two instances of the same Position will exist.
   /// \param  Vec is the Position to copy from.
   /// \throw  None
   cPair( const cPair & from );

   /// Destructor.
   /// \pre    An instance of Position has been created.
   /// \post   The instance of Position is destroyed.
   ~cPair( void );

// OPERATORS

   /// Assignment operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return A refence to that element
   /// \throw  NONE
   const cPair &  operator=( const cPair & rhs );
  
   /// == operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return bool
   /// \throw  NONE
   bool  operator == ( const cPair & rhs ); 
   
   /// <= operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return bool
   /// \throw  NONE
   bool  operator <= ( const cPair & rhs );
   
   /// >= operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return bool
   /// \throw  NONE
   bool  operator >= ( const cPair & rhs );
   
   /// < operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return bool
   /// \throw  NONE
   bool  operator < ( const cPair & rhs );
   
   /// > operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return bool
   /// \throw  NONE
   bool  operator > ( const cPair & rhs );
// OPERATIONS 
   

// ACCESS and MUTATE

   
// INQUIRY

   /// element
   /// \pre    The array where elements are stored must have something in it.
   /// \post   mPosition is incemented
   /// \param  None
   /// \return The element of the array 
   Element element();
   
   /// key
   /// \pre    The array where elements are stored must have something in it.
   /// \post   mPosition is incemented
   /// \param  None
   /// \return The element of the array 
   Key key();
   
// MEMBER VARIABLES
//private:
   
   //stores the pointer to the position
   Element mElement;
   Key mKey;

}; // end of class Pair

///////////////////////////////////////////////////////////////////////////////
/// \class        Position
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that stores a pointer to the position.
///
/// This class is one the stores a position of a Pair in the Dictionary.  It is
/// an interface tool for the client.
///       
/// REVISION HISTORY:
///
///   NONE
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

template < class Key, class Element >
class cPosition
{
   public:
   friend class Dictionary<Key, Element>;
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Position class with 0 elements is created.
   /// \param  None
   /// \throw  None
   cPosition(void);
   
   /// constructor with node input 
   /// \pre    None
   /// \post   An instance of the Position class with 1 element is created.
   /// \param  A node pointer
   /// \throw  None
   cPosition( cPair<Key,Element>* p );

   /// Copy Constructor.
   /// \pre    An instance of Position needs to be present.
   /// \post   Two instances of the same Position will exist.
   /// \param  Vec is the Position to copy from.
   /// \throw  None
   cPosition( const cPosition & from );

   /// Destructor.
   /// \pre    An instance of Position has been created.
   /// \post   The instance of Position is destroyed.
   ~cPosition( void );

// OPERATORS
   
   /// Assignment operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return A refence to that element
   /// \throw  NONE
   const cPosition &  operator=( const cPosition & rhs );

// OPERATIONS 
   

// ACCESS and MUTATE

   
// INQUIRY
   
   /// element
   /// \pre    There must be an positon to call it on
   /// \post   None
   /// \param  None
   /// \return the element
   Element element( void );
   
   /// element (const)
   /// \pre    There must be an positon to call it on
   /// \post   None
   /// \param  None
   /// \return the element
   Key key( void ) const;
   
   /// isNull  (const)
   /// \pre    There must be an positon to call it on
   /// \post   None
   /// \param  None
   /// \return A bool whether or not their is an element
   bool isNull( void) const;
   
// MEMBER VARIABLES
//private:
   
   //stores the pointer to the position
   cPair<Key, Element >* mPosition;

}; // end of class Position

///////////////////////////////////////////////////////////////////////////////
/// \class        PositionIterator
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that iterates a pointer to the position.
///
/// This class is one the stores a position of a node in the tree.  It is an 
/// interface tool for the client.  So they can iterate through all of the 
/// positions in the tree.
///       
/// REVISION HISTORY:
///
///   NONE
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
template <class Key, class Element >
class cPositionIterator
{
   public:
   friend class Dictionary<Key, Element >;
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the PositionIterator class with 0 elements is created.
   /// \param  None
   /// \throw  None
   cPositionIterator( void );

   /// Copy Constructor.
   /// \pre    An instance of PositionIterator needs to be present.
   /// \post   Two instances of the same PositionIterator will exist.
   /// \param  Vec is the PositionIterator to copy from.
   /// \throw  None
   cPositionIterator( const cPositionIterator & from );

   /// Destructor.
   /// \pre    An instance of PositionIterator has been created.
   /// \post   The instance of PositionIterator is destroyed.
   ~cPositionIterator( void );

// OPERATORS

   /// Assignment operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An position of a tree.
   /// \return A refence to that element
   /// \throw  NONE
   const cPositionIterator &  operator=( const cPositionIterator & rhs );
   
// OPERATIONS 
   

// ACCESS and MUTATE

   
// INQUIRY
 
   /// next
   /// \pre    There must be an iterator to call it on
   /// \post   None
   /// \param  None
   /// \return a bool whether or not their is an iterator
   bool hasNext ( void );
   
   /// hasNext
   /// \pre    The array where elements are stored must have something in it.
   /// \post   mPosition is incemented
   /// \param  None
   /// \return The element of the array 
   cPosition<Key,Element> next ( void );
   
// MEMBER VARIABLES
private:
   //the iterator vector that allows us to store all of the values
   std::vector<cPosition<Key, Element > > mPositionIterator;
   
   //stores the position of the iterator
   unsigned int mPosition;
   
}; // end of class PositionIterator

///////////////////////////////////////////////////////////////////////////////
/// \class        KeyIterator
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that iterates a pointer to the element.
///
/// This class is one the stores a element of a node in the tree.  It is an 
/// interface tool for the client.  So they can iterate through all of the 
/// elements in the tree.
///       
/// REVISION HISTORY:
///
///   NONE
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
template <class Key, class Element>
class cKeyIterator
{
   public:
   friend class Dictionary<Key, Element>;
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the KeyIterator class with 0 elements is created.
   /// \param  None
   /// \throw  None
   cKeyIterator( void );

   /// Copy Constructor.
   /// \pre    An instance of KeyIterator needs to be present.
   /// \post   Two instances of the same KeyIterator will exist.
   /// \param  KeyIterator is the Key to copy from.
   /// \throw  None
   cKeyIterator( const cKeyIterator & from );

   /// Destructor.
   /// \pre    An instance of KeyIterator has been created.
   /// \post   The instance of KeyIterator is destroyed.
   ~cKeyIterator( void );

// OPERATORS

   /// Assignment operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return A refence to that element
   /// \throw  NONE
   const cKeyIterator &  operator=( const cKeyIterator & rhs );
   
// OPERATIONS 
   

// ACCESS and MUTATE
   
// INQUIRY
 
   /// next
   /// \pre    There must be an iterator to call it on
   /// \post   None
   /// \param  None
   /// \return a bool whether or not their is an iterator
   bool hasNext ( void );
   
   /// hasNext
   /// \pre    The array where elements are stored must have something in it.
   /// \post   mPosition is incemented
   /// \param  None
   /// \return The element of the array 
   Key next ( void );
// MEMBER VARIABLES
private:

   //the iterator vector that allows us to store all of the values
   std::vector<Key> mKeyIterator;
   
   //stores the position of the iterator
   unsigned int mPosition;
}; // end of class ElementIterator

///////////////////////////////////////////////////////////////////////////////
/// \class        ElementIterator
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that iterates a pointer to the element.
///
/// This class is one the stores a element of a node in the tree.  It is an 
/// interface tool for the client.  So they can iterate through all of the 
/// elements in the tree.
///       
/// REVISION HISTORY:
///
///   NONE
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
template <class Key, class Element >
class cElementIterator
{
   public:
   friend class Dictionary<Key, Element>;
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the ElementIterator class with 0 elements is created.
   /// \param  None
   /// \throw  None
   cElementIterator( void );

   /// Copy Constructor.
   /// \pre    An instance of ElementIterator needs to be present.
   /// \post   Two instances of the same ElementIterator will exist.
   /// \param  ElementIterator is the Position to copy from.
   /// \throw  None
   cElementIterator( const cElementIterator & from );

   /// Destructor.
   /// \pre    An instance of ElementIterator has been created.
   /// \post   The instance of ElementIterator is destroyed.
   ~cElementIterator( void );

// OPERATORS

   /// Assignment operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a tree.
   /// \return A refence to that element
   /// \throw  NONE
   const cElementIterator &  operator=( const cElementIterator & rhs );
   
// OPERATIONS 
   

// ACCESS and MUTATE
   
// INQUIRY
 
   /// next
   /// \pre    There must be an iterator to call it on
   /// \post   None
   /// \param  None
   /// \return a bool whether or not their is an iterator
   bool hasNext ( void );
   
   /// hasNext
   /// \pre    The array where elements are stored must have something in it.
   /// \post   mPosition is incemented
   /// \param  None
   /// \return The element of the array 
   Element next ( void );
// MEMBER VARIABLES
private:

   //the iterator vector that allows us to store all of the values
   std::vector<Element> mElementIterator;
   
   //stores the position of the iterator
   unsigned int mPosition;
}; // end of class ElementIterator
///////////////////////////////////////////////////////////////////////////////
/// \class        Tree
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A stan
///
/// This class is a vector that is built to act just like the standard library
/// vector class.  It was built from a shell given to us by Kelly Fitz.  
///       
/// REVISION HISTORY:
///
///   NONE
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
template < class Key, class Element >
class Dictionary
{
   public:
   typedef cPair<Key, Element> Pair;
   typedef cPosition<Key, Element> Position;
   typedef cPositionIterator<Key, Element> PositionIterator;
   typedef cKeyIterator<Key, Element> KeyIterator;
   typedef cElementIterator<Key, Element> ElementIterator;
   typedef typename BinaryTree<Pair>::Position bPosition;
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Tree class with 0 elements is created.
   /// \param  None
   /// \throw  None
   Dictionary(void);

   /// Copy Constructor.
   /// \pre    An instance of Tree needs to be present.
   /// \post   Two instances of the same Vec will exist.
   /// \param  Vec is the Tree to copy from.
   /// \throw  None
   Dictionary( const Dictionary & from );

   /// Destructor.
   /// \pre    An instance of Tree has been created.
   /// \post   The instance of Tree is destroyed.
   ~Dictionary( void );

// OPERATORS

   /// Assignment Operator
   /// Provide access to the element at the specified rank.
   /// \pre    there must be a tree to copy
   /// \post   2 copies of the tree will exist
   /// \param  a reference to a tree
   /// \return a reference to a tree
   const Dictionary& operator=( const Dictionary & rhs );  

// OPERATIONS 

   /// find
   /// \pre    There must be a tree to call it on
   /// \post   The tree will have an element added to v's child
   /// \param  A Key
   /// \return A position to the new node (child) 
   Position find(const Key k);
   
   /// findAll
   /// \pre    There must be a tree to call it on
   /// \post   The tree will have an element added to v's child
   /// \param  A Key
   /// \return A positioniterator to the positions 
   PositionIterator findAll(const Key k);
   
// ACCESS and MUTATE

   /// insertItem
   /// \pre    There must be a Dictionary to call it on
   /// \post   The Dictionary will have an element added to it
   /// \param  A Key
   /// \paran  An Element
   /// \return None 
   void insertItem(const Key k, const Element e);
   
   /// removeElement
   /// \pre    There must be a Dictionary to call it on
   /// \post   The Dictionary will have an element removed from it
   /// \param  A key
   /// \return A position to the new node (child) 
   void removeElement(const Key k);
   
   /// removeAllElements
   /// \pre    There must be a Dictionary to call it on
   /// \post   The Dictionary will all elements equal to k from D
   /// \param  A key
   /// \return A position to the new node (child) 
   void removeAllElements(const Key k);
   
// INQUIRY
  
   /// size
   /// \pre    There must be a Dictionary to call it on
   /// \post   The size will be returned
   /// \param  NONE
   /// \return An int with the size in it 
   int size();
   
   /// isEmpty
   /// \pre    There must be a Dictionary to call it on
   /// \post   NONE
   /// \param  NONE
   /// \return a bool if it's empty 
   bool isEmpty();
   
   /// elements
   /// \pre    There must be a Dictionary to call it on
   /// \post   NONE
   /// \param  NONE
   /// \return an element iterator 
   ElementIterator elements();
   
   /// elements
   /// \pre    There must be a Dictionary to call it on
   /// \post   NONE
   /// \param  NONE
   /// \return an element iterator 
   ElementIterator element_help(cElementIterator<Key, Element> e, bPosition a);
   
   /// keys
   /// \pre    There must be a Dictionary to call it on
   /// \post   NONE
   /// \param  NONE
   /// \return a key iterator 
   KeyIterator keys();
  
   /// print
   /// \pre    There must be a Dictionary to call it on
   /// \post   NONE
   /// \param  NONE
   /// \return an element iterator
   void print(void);
   
   /// print
   /// \pre    There must be a Dictionary to call it on
   /// \post   NONE
   /// \param  NONE
   /// \return an element iterator
   void help_print(bPosition p);

// MEMBER VARIABLES
private:
   BinaryTree<Pair> mDictionary;
   unsigned int mSize;
// OPERATIONS
      
}; // end of class Dictionary

///////////////////////////////////////////////////////////////////////////////
/// \class        cPair
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that stores a key-element pair
///
/// This class is one the stores a key element pair in a dictionary  It is an 
/// interface tool for the client.
///       
/// REVISION HISTORY:
///
///   NONE
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
/// \post   An instance of the Position class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPair<Key, Element>::cPair(void)
{
 
}

///////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the Position class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPair<Key, Element>::cPair(Key k, Element e)
{
   mKey = k;
   mElement = e;
}
///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of Position needs to be present.
/// \post   Two instances of the same Position will exist.
/// \param  Vec is the Position to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPair<Key, Element>::cPair( const cPair & from )
{
   this->mKey = from.mKey;
   this->mElement = from.mElement;
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of Position has been created.
/// \post   The instance of Position is destroyed.
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPair<Key, Element>::~cPair( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
const cPair<Key, Element> &  cPair<Key, Element>::operator=( const cPair<Key, Element> & rhs )
{
   this->mKey = rhs.mKey;
   this->mElement = rhs.mElement;
   return rhs;
}

///////////////////////////////////////////////////////////////////////
/// == operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return bool
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool  cPair<Key, Element>::operator == ( const cPair & rhs )
{
   return (this->mKey == rhs.mKey);
}

///////////////////////////////////////////////////////////////////////
/// <= operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return bool
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool  cPair<Key, Element>::operator <= ( const cPair & rhs )
{
   return (this->mKey <= rhs.mKey);
}

///////////////////////////////////////////////////////////////////////
/// >= operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return bool
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool  cPair<Key, Element>::operator >= ( const cPair & rhs )
{
   return (this->mKey >= rhs.mKey);
}

///////////////////////////////////////////////////////////////////////
/// < operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return bool
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool  cPair<Key, Element>::operator < ( const cPair &rhs )
{
   return (mKey < rhs.mKey);
}

///////////////////////////////////////////////////////////////////////
/// > operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return bool
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool  cPair<Key, Element>::operator > ( const cPair & rhs )
{
   return (this->mKey > rhs.mKey);
}

// OPERATIONS 

// ACCESS and MUTATE

// INQUIRY

///////////////////////////////////////////////////////////////////////
/// element
/// \pre    The array where elements are stored must have something in it.
/// \post   mPosition is incemented
/// \param  None
/// \return The element of the array 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Element cPair<Key, Element>::element()
{
   return mElement;
}

///////////////////////////////////////////////////////////////////////
/// key
/// \pre    The array where elements are stored must have something in it.
/// \post   mPosition is incemented
/// \param  None
/// \return The element of the array 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Key cPair<Key, Element>::key()
{
   return mKey;
}


///////////////////////////////////////////////////////////////////////////////
/// \class        Position
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that stores a pointer to the position.
///
/// This class is one the stores a position of a Pair in the Dictionary.  It is
/// an interface tool for the client.
///       
/// REVISION HISTORY:
///
///   NONE
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
/// \post   An instance of the Position class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPosition<Key, Element>::cPosition( void )
{
   this->mPosition = NULL;
}

///////////////////////////////////////////////////////////////////////
/// constructor with node input 
/// \pre    None
/// \post   An instance of the Position class with 1 element is created.
/// \param  A node pointer
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPosition<Key, Element>::cPosition( cPair<Key, Element>* n)
{
   this->mPosition = n;
}

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of Position needs to be present.
/// \post   Two instances of the same Position will exist.
/// \param  Vec is the Position to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPosition<Key, Element>::cPosition( const cPosition & from )
{
   this->mPosition = from.mPosition;
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of Position has been created.
/// \post   The instance of Position is destroyed.
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPosition<Key, Element>::~cPosition( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
const cPosition<Key, Element> &  cPosition<Key, Element>::operator=( const cPosition<Key, Element> & rhs )
{
   this->mPosition = rhs.mPosition;
   return rhs;
}

// OPERATIONS 

// ACCESS and MUTATE


// INQUIRY

///////////////////////////////////////////////////////////////////////
/// element
/// \pre    There must be an positon to call it on
/// \post   None
/// \param  None
/// \return the element
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Element cPosition<Key, Element>::element( void )
{
   return mPosition->element();
}

///////////////////////////////////////////////////////////////////////
/// element (const)
/// \pre    There must be an positon to call it on
/// \post   None
/// \param  None
/// \return the element
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Key cPosition<Key, Element>::key( void ) const
{
   return mPosition->mKey;
}

///////////////////////////////////////////////////////////////////////
/// isNull  (const)
/// \pre    There must be an positon to call it on
/// \post   None
/// \param  None
/// \return A bool whether or not their is an element
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool cPosition<Key, Element>::isNull( void) const
{
   return (mPosition == NULL);
}

///////////////////////////////////////////////////////////////////////////////
/// \class        PositionIterator
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that iterates a pointer to the position.
///
/// This class is one the stores a position of a node in the tree.  It is an 
/// interface tool for the client.  So they can iterate through all of the 
/// positions in the tree.
///       
/// REVISION HISTORY:
///
///   NONE
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
/// \post   An instance of the PositionIterator class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPositionIterator<Key, Element>::cPositionIterator( void )
{
   this->mPosition = 0;
}

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of PositionIterator needs to be present.
/// \post   Two instances of the same PositionIterator will exist.
/// \param  Vec is the PositionIterator to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPositionIterator<Key, Element>::cPositionIterator( const cPositionIterator & from )
{
   this->mPositionIterator = from.mPositionIterator;
   this->mPosition = from.mPosition;
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of PositionIterator has been created.
/// \post   The instance of PositionIterator is destroyed.
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPositionIterator<Key, Element>::~cPositionIterator( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An position of a tree.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
const cPositionIterator<Key, Element> &  cPositionIterator<Key, Element>::operator=( const cPositionIterator & rhs )
{
   this->mPositionIterator = from.mPositionIterator;
   this->mPosition = from.mPosition;
   return rhs;
}

// OPERATIONS 


// ACCESS and MUTATE


// INQUIRY
 
///////////////////////////////////////////////////////////////////////
/// next
/// \pre    There must be an iterator to call it on
/// \post   None
/// \param  None
/// \return a bool whether or not their is an iterator
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool cPositionIterator<Key, Element>::hasNext ( void )
{
   return (mPositionIterator.size() > mPosition);
}

///////////////////////////////////////////////////////////////////////
/// hasNext
/// \pre    The array where elements are stored must have something in it.
/// \post   mPosition is incemented
/// \param  None
/// \return The element of the array 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPosition<Key,Element> cPositionIterator<Key, Element>::next ( void )
{
   if (! hasNext() )
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   mPosition++;
   return mPositionIterator[mPosition-1];
}

///////////////////////////////////////////////////////////////////////////////
/// \class        KeyIterator
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that iterates a pointer to the element.
///
/// This class is one the stores a element of a node in the tree.  It is an 
/// interface tool for the client.  So they can iterate through all of the 
/// elements in the tree.
///       
/// REVISION HISTORY:
///
///   NONE
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

///////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the KeyIterator class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cKeyIterator<Key,Element>::cKeyIterator( void )
{
   this->mPosition = 0;
}

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of KeyIterator needs to be present.
/// \post   Two instances of the same KeyIterator will exist.
/// \param  KeyIterator is the Key to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cKeyIterator<Key,Element>::cKeyIterator( const cKeyIterator<Key,Element> & from )
{
   this->mKeyIterator = from.mKeyIterator;
   this->mPosition = from.mPosition;
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of KeyIterator has been created.
/// \post   The instance of KeyIterator is destroyed.
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cKeyIterator<Key,Element>::~cKeyIterator( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
const cKeyIterator<Key,Element> &  cKeyIterator<Key,Element>::operator=( const cKeyIterator<Key,Element> & rhs )
{
   this->mKeyIterator = from.mKeyIterator;
   this->mPosition = from.mPosition;
   return rhs;
}

// OPERATIONS 

// ACCESS and MUTATE

// INQUIRY

/////////////////////////////////////////////////////////////////////// 
/// next
/// \pre    There must be an iterator to call it on
/// \post   None
/// \param  None
/// \return a bool whether or not their is an iterator
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool cKeyIterator<Key,Element>::hasNext ( void )
{
   return (mKeyIterator.size() > mPosition);
}

///////////////////////////////////////////////////////////////////////
/// hasNext
/// \pre    The array where elements are stored must have something in it.
/// \post   mPosition is incemented
/// \param  None
/// \return The element of the array 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Key cKeyIterator<Key,Element>::next ( void )
{
   if (! hasNext() )
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   mPosition++;
   return mKeyIterator[mPosition-1];
}

///////////////////////////////////////////////////////////////////////////////
/// \class        ElementIterator
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A class that iterates a pointer to the element.
///
/// This class is one the stores a element of a node in the tree.  It is an 
/// interface tool for the client.  So they can iterate through all of the 
/// elements in the tree.
///       
/// REVISION HISTORY:
///
///   NONE
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
/// \post   An instance of the ElementIterator class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cElementIterator<Key,Element>::cElementIterator( void )
{
   this->mPosition = 0;
}

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of ElementIterator needs to be present.
/// \post   Two instances of the same ElementIterator will exist.
/// \param  ElementIterator is the Position to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cElementIterator<Key,Element>::cElementIterator( const cElementIterator<Key,Element> & from )
{
   this->mElementIterator = from.mElementIterator;
   this->mPosition = from.mPosition;
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of ElementIterator has been created.
/// \post   The instance of ElementIterator is destroyed.
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cElementIterator<Key,Element>::~cElementIterator( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
const cElementIterator<Key,Element> &  cElementIterator<Key,Element>::operator=( const cElementIterator<Key,Element> & rhs )
{
   this->mElementIterator = rhs.mElementIterator;
   this->mPosition = rhs.mPosition;
   return rhs;
}

// OPERATIONS 

// ACCESS and MUTATE

// INQUIRY

/////////////////////////////////////////////////////////////////////// 
/// next
/// \pre    There must be an iterator to call it on
/// \post   None
/// \param  None
/// \return a bool whether or not their is an iterator
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool cElementIterator<Key,Element>::hasNext ( void )
{
   return (mElementIterator.size() > mPosition);
}

///////////////////////////////////////////////////////////////////////
/// hasNext
/// \pre    The array where elements are stored must have something in it.
/// \post   mPosition is incemented
/// \param  None
/// \return The element of the array 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Element cElementIterator<Key,Element>::next ( void )
{
   if (! hasNext() )
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   mPosition++;
   return mElementIterator[mPosition-1];
}

///////////////////////////////////////////////////////////////////////////////
/// \class        Dictionary
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A stan
///
/// This class is a vector that is built to act just like the standard library
/// vector class.  It was built from a shell given to us by Kelly Fitz.  
///       
/// REVISION HISTORY:
///
///   NONE
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
/// \post   An instance of the Tree class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Dictionary<Key,Element>::Dictionary(void)
{
   mSize = 0;
}

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of Tree needs to be present.
/// \post   Two instances of the same Vec will exist.
/// \param  Vec is the Tree to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Dictionary<Key,Element>::Dictionary( const Dictionary & from )
{
      this->mDictionary = from.mDictionary;
      this->mSize = from.mSize;
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of Tree has been created.
/// \post   The instance of Tree is destroyed.
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
Dictionary<Key,Element>::~Dictionary( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////
/// Assignment Operator
/// Provide access to the element at the specified rank.
/// \pre    there must be a tree to copy
/// \post   2 copies of the tree will exist
/// \param  a reference to a tree
/// \return a reference to a tree
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
const Dictionary<Key,Element> & Dictionary<Key,Element>::operator=( const Dictionary<Key,Element> & rhs )  
{
   
   this->mDictionary = rhs.mDictionary;
   this->mSize = rhs.mSize;
   return rhs;
}

// OPERATIONS 

///////////////////////////////////////////////////////////////////////
/// find
/// \pre    There must be a tree to call it on
/// \post   The tree will have an element added to v's child
/// \param  A Key
/// \return A position to the new node (child) 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPosition<Key, Element> Dictionary<Key,Element>::find(const Key k)
{
   Element e;
   cPair<Key, Element> pair_temp(k,e);
   typename BinaryTree<Pair>::Position pe = bst_search(this->mDictionary,mDictionary.root(),pair_temp);
   Position c;
   c.mPosition = &(pe.mPosition->mElement);
   return c;
}

///////////////////////////////////////////////////////////////////////
/// findAll
/// \pre    There must be a tree to call it on
/// \post   The tree will have an element added to v's child
/// \param  A Key
/// \return A positioniterator to the positions 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cPositionIterator<Key, Element> Dictionary<Key,Element>::findAll(const Key k)
{
   Element e;
   PositionIterator gh;
   Position c;
   cPair<Key, Element> pair_temp(k,e);
   
   typename BinaryTree<Pair>::Position pe = bst_search(this->mDictionary,mDictionary.root(),pair_temp);
   while (!pe.isNull())
   {
      c.mPosition = &(pe.mPosition->mElement);
      gh.mPositionIterator.push_back(c);
      pe = bst_search(this->mDictionary,mDictionary.root(),pair_temp);
   }
   return gh;
}

// ACCESS and MUTATE

///////////////////////////////////////////////////////////////////////
/// insertItem
/// \pre    There must be a Dictionary to call it on
/// \post   The Dictionary will have an element added to it
/// \param  A Key
/// \paran  An Element
/// \return None 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
void Dictionary<Key,Element>::insertItem(const Key k, const Element e)
{
   cPair<Key, Element> pair_temp(k,e);
   mSize++;
   bst_insert(mDictionary,pair_temp);
}

///////////////////////////////////////////////////////////////////////
/// removeElement
/// \pre    There must be a Dictionary to call it on
/// \post   The Dictionary will have an element removed from it
/// \param  A key
/// \return A position to the new node (child) 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
void Dictionary<Key,Element>::removeElement(const Key k)
{
   Element e;
   cPair<Key, Element> pair_temp(k,e);
   if (bst_search(this->mDictionary,mDictionary.root(),pair_temp).isNull())
   {
      throw (NonexistentElementException("Nothing to erase"));
   }

   bst_remove(this->mDictionary,mDictionary.root(),pair_temp);
}

///////////////////////////////////////////////////////////////////////
/// removeAllElements
/// \pre    There must be a Dictionary to call it on
/// \post   The Dictionary will all elements equal to k from D
/// \param  A key
/// \return A position to the new node (child) 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
void Dictionary<Key,Element>::removeAllElements(const Key k)
{
   while (1 == 1)
   {
      try
      {
         removeElement(k);
      }
      catch (std::logic_error)
      {
         return;
      }
   }
   
}

// INQUIRY

///////////////////////////////////////////////////////////////////////  
/// size
/// \pre    There must be a Dictionary to call it on
/// \post   The size will be returned
/// \param  NONE
/// \return An int with the size in it 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
int Dictionary<Key,Element>::size()
{
   return mSize;
}

///////////////////////////////////////////////////////////////////////
/// isEmpty
/// \pre    There must be a Dictionary to call it on
/// \post   NONE
/// \param  NONE
/// \return a bool if it's empty 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
bool Dictionary<Key,Element>::isEmpty()
{
   return (mDictionary.size() == 0);
}

///////////////////////////////////////////////////////////////////////
/// elements
/// \pre    There must be a Dictionary to call it on
/// \post   NONE
/// \param  NONE
/// \return an element iterator 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cElementIterator<Key, Element> Dictionary<Key,Element>::elements()
{
   cElementIterator<Key, Element> temp;
//   bPosition a = mDictionary.root();
//   temp = element_help(temp,a);
   return temp;

}
///////////////////////////////////////////////////////////////////////
/// elements
/// \pre    There must be a Dictionary to call it on
/// \post   NONE
/// \param  NONE
/// \return an element iterator 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cElementIterator<Key, Element> Dictionary<Key,Element>::element_help(cElementIterator<Key, Element> e, bPosition  p)
{
//   bPosition excheck = mDictionary.leftChild(p);
//   if (mDictionary.isInternal(excheck))
//   {
//      element_help(mDictionary.leftChild(p));
//   }
//   e.mElementIterator.push_back( p.element().element() << " ");
//   excheck = mDictionary.rightChild(p);
//   if (mDictionary.isInternal(excheck))
//   {
//      element_help(mDictionary.rightChild(p));
//   }
//   return e;
}
///////////////////////////////////////////////////////////////////////
/// keys
/// \pre    There must be a Dictionary to call it on
/// \post   NONE
/// \param  NONE
/// \return a key iterator 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
cKeyIterator<Key, Element> Dictionary<Key,Element>::keys()
{   
   cKeyIterator<Key, Element> temp;
}
///////////////////////////////////////////////////////////////////////
/// print
/// \pre    There must be a Dictionary to call it on
/// \post   NONE
/// \param  NONE
/// \return NONE 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
void Dictionary<Key,Element>::print(void)
{
   help_print(mDictionary.root());
}

///////////////////////////////////////////////////////////////////////
/// print
/// \pre    There must be a Dictionary to call it on
/// \post   NONE
/// \param  NONE
/// \return NONE 
///////////////////////////////////////////////////////////////////////
template <class Key, class Element > 
void Dictionary<Key,Element>::help_print( bPosition p)
{
   bPosition excheck = mDictionary.leftChild(p);
   if (mDictionary.isInternal(excheck))
   {
      help_print(mDictionary.leftChild(p));
   }
   std::cout << p.element().key() << " ";
   excheck = mDictionary.rightChild(p);
   if (mDictionary.isInternal(excheck))
   {
      help_print(mDictionary.rightChild(p));
   }
}

#endif

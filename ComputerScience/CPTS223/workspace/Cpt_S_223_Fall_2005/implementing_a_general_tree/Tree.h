#ifndef TREE_H    // include guard
#define TREE_H
///////////////////////////////////////////////////////////////////////////////
/// \class        Node
/// \author       Alex Hortin
/// \date         10/17/05
/// \brief        A node that makes up part of a tree
///
/// This class is one the stores each individual part of the tree. It stores 
/// a element, a parent pointer, and an array of pointers to all of it's 
/// children. 
///       
/// REVISION HISTORY:
///
///   NONE
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
// LOCAL INCLUDES
//
#include "Tree.h"
// FORWARD REFERENCES
//
using std::cout;
using std::endl;
class Tree;
// CONSTANTS
//

#ifndef ELEMENT_TYPE
#include <string>
typedef std::string Element;
#else
typedef ELEMENT_TYPE Element;
#endif

class cNode
{
   public:
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Node class is created.
   /// \param  None
   /// \throw  None
   cNode( void );
   
   /// Copy Constructor.
   /// \pre    An instance of Node needs to be present.
   /// \post   Two instances of the same Node will exist.
   /// \param  Node is the Node to copy from.
   /// \throw  None
   cNode( const cNode & from );

   /// Destructor.
   /// \pre    An instance of Node has been created.
   /// \post   The instance of Node is destroyed.
   ~cNode( void );

// OPERATORS

// OPERATIONS 

// ACCESS and MUTATE
 
// INQUIRY  
   
// MEMBER VARIABLES
//private:
   
   //stored the element contained in the node
   Element mElement;
   
   //stores the adress of the parent node
   cNode* mParent;
   
   //stores all the nodes children
   std::vector<cNode *> mChildren;

}; // end of class Node


///////////////////////////////////////////////////////////////////////////////
/// \class        Position
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

// SYSTEM INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

// CONSTANTS
//

class cPosition
{
   public:
   friend class Tree;
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Position class with 0 elements is created.
   /// \param  None
   /// \throw  None
   cPosition( void );
   
   /// constructor with node input 
   /// \pre    None
   /// \post   An instance of the Position class with 1 element is created.
   /// \param  A node pointer
   /// \throw  None
   cPosition( cNode* n);

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

// OPERATIONS 
   

// ACCESS and MUTATE

   
// INQUIRY
   
   /// element
   /// \pre    There must be an positon to call it on
   /// \post   None
   /// \param  None
   /// \return the element
   Element element( void );
   
   /// isNull
   /// \pre    There must be an positon to call it on
   /// \post   None
   /// \param  None
   /// \return A bool whether or not their is an element
   bool isNull( void);
   
   /// element (const)
   /// \pre    There must be an positon to call it on
   /// \post   None
   /// \param  None
   /// \return the element
   Element element( void ) const;
   
   /// isNull  (const)
   /// \pre    There must be an positon to call it on
   /// \post   None
   /// \param  None
   /// \return A bool whether or not their is an element
   bool isNull( void) const;
   
// MEMBER VARIABLES
private:
   
   //stores the pointer to the position
   cNode * mPosition;

}; // end of class Position

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

class cElementIterator
{
   public:
   friend class Tree;
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

class cPositionIterator
{
   public:
   friend class Tree;
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
   cPosition next ( void );
   
// MEMBER VARIABLES
private:
   //the iterator vector that allows us to store all of the values
   std::vector<cPosition> mPositionIterator;
   
   //stores the position of the iterator
   unsigned int mPosition;
   
}; // end of class PositionIterator


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

class Tree
{
   public:
   typedef cNode Tree::Node;
   typedef cPosition Tree::Position;
   typedef cElementIterator Tree::ElementIterator;
   typedef cPositionIterator Tree::PositionIterator;
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Tree class with 0 elements is created.
   /// \param  None
   /// \throw  None
   Tree( Element e );

   /// Copy Constructor.
   /// \pre    An instance of Tree needs to be present.
   /// \post   Two instances of the same Vec will exist.
   /// \param  Vec is the Tree to copy from.
   /// \throw  None
   Tree( const Tree & from );

   /// Destructor.
   /// \pre    An instance of Tree has been created.
   /// \post   The instance of Tree is destroyed.
   ~Tree( void );

// OPERATORS

   /// Assignment Operator
   /// Provide access to the element at the specified rank.
   /// \pre    there must be a tree to copy
   /// \post   2 copies of the tree will exist
   /// \param  a reference to a tree
   /// \return a reference to a tree
   Tree& operator=( const Tree & rhs );  

// OPERATIONS 

   /// addchild
   /// \pre    There must be a tree to call it on
   /// \post   The tree will have an element added to v's child
   /// \param  A position
   /// \paran  An Element
   /// \return A position to the new node (child) 
   Position addChild(const Position& v, const Element e);

// ACCESS and MUTATE

   /// replaceElement
   /// \pre    There must be a tree to call it on
   /// \post   The Position will be replaced with the element
   /// \param  A position 
   /// \param  An Element
   /// \return None   
   void replaceElement( Position v, Element e);
   
   /// swapElement
   /// \pre    There must be a tree to call it on
   /// \post   The Position will be replaced with the element
   /// \param  A position to swap
   /// \param  A position to swap
   /// \return None   
   void swapElements( Position v,  Position w) ;
   
// INQUIRY
  
   /// print
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return None
   void print(Position v);
   
   /// root
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return The Position to the root of the tree
   Position root( void ) const;
   
   /// isRoot
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  A position
   /// \return bool if its a root
   bool isRoot( Position& v) const;
   
   /// isExternal
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  A position
   /// \return bool if its external
   bool isExternal(Position& v) const;

   /// isInternal
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  A position
   /// \return bool if its internal
   bool isInternal( Position& v) const;
   
   /// size
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return the size of a tree
   unsigned int size( void) const ;

   /// parent
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  A position
   /// \return the parent of a node   
   Position parent(const Position& v) const;
   
   /// Children
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  A position
   /// \return the parent of a node
   PositionIterator children(const Position& v) const;
   
   /// elements
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return an Iterator of Elements
   ElementIterator elements(void ) const;
   
   /// positions
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return an Iterator of Positions
   PositionIterator positions(void ) const;
   
   /// getelements
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return an Iterator of Elements
  void getelements(ElementIterator& iter, Position p ) const;
   
   /// getpositions
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return an Iterator of Positions
   void getpositions(PositionIterator& iter, Position p ) const;
   
// MEMBER VARIABLES
private:
   Node* mRoot;
   
   unsigned int mSize;
 
   
   /// deleteSubtree
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return an Iterator of Positions
   void deleteSubtree( Node * p);
   
   /// getpositions
   /// \pre    There must be a tree to call it on
   /// \post   None
   /// \param  None
   /// \return an Iterator of Positions
   Node* copySubtree( Node * p);
      
}; // end of class Tree

#endif

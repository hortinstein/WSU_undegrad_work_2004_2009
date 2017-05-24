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
template <class Element> class Tree;
// CONSTANTS
//

//#ifndef ELEMENT_TYPE
//#include <string>
//typedef std::string Element;
//#else
//typedef ELEMENT_TYPE Element;
//#endif

template < class Element >
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
template <class Element> class Tree;

// CONSTANTS
//
template < class Element >
class cPosition
{
   public:
   friend class Tree< Element >;
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
   cPosition( cNode< Element >* n);

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
   cNode< Element > * mPosition;

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
template < class Element >
class cElementIterator
{
   public:
   friend class Tree< Element >;
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
template < class Element >
class cPositionIterator
{
   public:
   friend class Tree< Element >;
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
   cPosition<Element> next ( void );
   
// MEMBER VARIABLES
private:
   //the iterator vector that allows us to store all of the values
   std::vector<cPosition< Element > > mPositionIterator;
   
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
template < class Element >
class Tree
{
   public:
   typedef cNode<Element> Node;
   typedef cPosition<Element> Position;
   typedef cElementIterator<Element> ElementIterator;
   typedef cPositionIterator<Element> PositionIterator;
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
#include "Tree.h"                                // class implemented

// SYSTEM INCLUDES
//

// LOCAL INCLUDES
//

// PUBLIC 

// LIFECYCLE 

///////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the Node class is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
cNode< Element >::cNode( void )
{
   mParent = NULL;
}

///////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of Node needs to be present.
/// \post   Two instances of the same Node will exist.
/// \param  Node is the Node to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
cNode< Element >::cNode( const cNode & from )
{
   mParent = from.mParent;
   mElement = from.mElement;
   mChildren = from.mChildren;
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of Node has been created.
/// \post   The instance of Node is destroyed.
///////////////////////////////////////////////////////////////////////
template < class Element >
cNode< Element >::~cNode( void )
{
}

// OPERATORS 

// OPERATIONS 

// ACCESS and MUTATE 

// INQUIRY 

// PROTECTED  

// PRIVATE  

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

// PUBLIC 

// LIFECYCLE 

///////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the Position class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////
template < class Element >
cPosition< Element >::cPosition( void )
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
template < class Element >
cPosition< Element >::cPosition( cNode< Element > * n)
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
template < class Element >
cPosition< Element >::cPosition( const cPosition & from )
{
   this->mPosition = from.mPosition;
}

///////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of Position has been created.
/// \post   The instance of Position is destroyed.
///////////////////////////////////////////////////////////////////////
template < class Element >
cPosition< Element >::~cPosition( void )
{
}

// OPERATORS 

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
template < class Element >
Element cPosition< Element >::element( void )
{
   if (mPosition == NULL)
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   return (mPosition->mElement);
}

///////////////////////////////////////////////////////////////////////
/// isNull
/// \pre    There must be an positon to call it on
/// \post   None
/// \param  None
/// \return A bool whether or not their is an element
///////////////////////////////////////////////////////////////////////
template < class Element >
bool cPosition< Element >::isNull( void )
{
   return (mPosition == NULL);
}

///////////////////////////////////////////////////////////////////////
/// element (const)
/// \pre    There must be an positon to call it on
/// \post   None
/// \param  None
/// \return the element
///////////////////////////////////////////////////////////////////////
template < class Element >
Element cPosition< Element >::element( void ) const
{
   if (mPosition == NULL)
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   return (mPosition->mElement);
}

///////////////////////////////////////////////////////////////////////
/// isNull(const)
/// \pre    There must be an positon to call it on
/// \post   None
/// \param  None
/// \return A bool whether or not their is an element
///////////////////////////////////////////////////////////////////////
template < class Element >
bool cPosition< Element >::isNull( void ) const
{
   return (mPosition == NULL);
}

// PROTECTED  

// PRIVATE  

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

// PUBLIC 

// LIFECYCLE 

///////////////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the ElementIterator class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////////////
template < class Element >
cElementIterator< Element >::cElementIterator( void )
{
   this->mPosition = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of ElementIterator needs to be present.
/// \post   Two instances of the same ElementIterator will exist.
/// \param  ElementIterator is the Position to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////////////
template < class Element >
cElementIterator< Element >::cElementIterator( const cElementIterator & from )
{
   this->mElementIterator = from.mElementIterator;
   this->mPosition = from.mPosition;
}

///////////////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of ElementIterator has been created.
/// \post   The instance of ElementIterator is destroyed.
///////////////////////////////////////////////////////////////////////////////
template < class Element >
cElementIterator< Element >::~cElementIterator( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An element of a tree.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
const cElementIterator< Element > &  cElementIterator< Element >::operator=( const cElementIterator & rhs )
{
   this->mPosition = rhs.mPosition;
   this->mElementIterator = rhs.mElementIterator;
   return rhs;
}

///////////////////////////////////////////////////////////////////////////////
// OPERATIONS 
/// next
/// \pre    There must be an iterator to call it on
/// \post   None
/// \param  None
/// \return a bool whether or not their is an iterator
///////////////////////////////////////////////////////////////////////////////
template < class Element >
bool cElementIterator< Element >::hasNext ( void )
{
   return (mElementIterator.size() > mPosition);
}

///////////////////////////////////////////////////////////////////////////////
/// hasNext
/// \pre    The array where elements are stored must have something in it.
/// \post   mPosition is incemented
/// \param  None
/// \return The element of the array 
///////////////////////////////////////////////////////////////////////////////
template < class Element >
Element cElementIterator< Element >::next ( void )
{
   if (! hasNext() )
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   mPosition++;
   return mElementIterator[mPosition-1];
}
// ACCESS and MUTATE 

// INQUIRY 

// PROTECTED  

// PRIVATE  

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

// PUBLIC 

// LIFECYCLE 

///////////////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the PositionIterator class with 0 elements is 
///         created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////////////
template < class Element >
cPositionIterator< Element >::cPositionIterator( void )
{
   this->mPosition = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of PositionIterator needs to be present.
/// \post   Two instances of the same PositionIterator will exist.
/// \param  Vec is the PositionIterator to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////////////
template < class Element >
cPositionIterator< Element >::cPositionIterator( const cPositionIterator & from )
{
   this->mPositionIterator = from.mPositionIterator;
   this->mPosition = from.mPosition;
}

///////////////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of PositionIterator has been created.
/// \post   The instance of PositionIterator is destroyed.
///////////////////////////////////////////////////////////////////////////////
template < class Element >
cPositionIterator< Element >::~cPositionIterator( void )
{
}

// OPERATORS

///////////////////////////////////////////////////////////////////////////////
/// Assignment operator.
/// \pre    The target must be assigned a value in memory.
/// \post   A reference value will be returned.
/// \param  An position of a tree.
/// \return A refence to that element
/// \throw  NONE
///////////////////////////////////////////////////////////////////////////////
template < class Element >
const cPositionIterator< Element > &  cPositionIterator< Element >::operator=( const cPositionIterator & rhs )
{
   this->mPosition = rhs.mPosition;
   this->mPositionIterator = rhs.mPositionIterator;
   return rhs;
}

// OPERATIONS 


// ACCESS and MUTATE


// INQUIRY

/////////////////////////////////////////////////////////////////////////////// 
/// next
/// \pre    There must be an iterator to call it on
/// \post   None
/// \param  None
/// \return a bool whether or not their is an iterator
///////////////////////////////////////////////////////////////////////////////
template < class Element >
bool cPositionIterator< Element >::hasNext ( void )
{
   return (mPositionIterator.size() > mPosition);
}
///////////////////////////////////////////////////////////////////////////////
/// hasNext
/// \pre    The array where elements are stored must have something in it.
/// \post   mPosition is incemented
/// \param  None
/// \return The element of the array 
///////////////////////////////////////////////////////////////////////////////
template < class Element >
cPosition< Element > cPositionIterator< Element >::next( void )
{
   if (! hasNext() )
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   mPosition++;
   return mPositionIterator[mPosition-1];
}
// PROTECTED  

// PRIVATE  

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

// PUBLIC 

// LIFECYCLE 

///////////////////////////////////////////////////////////////////////////////
/// Default constructor.
/// \pre    None
/// \post   An instance of the Tree class with 0 elements is created.
/// \param  None
/// \throw  None
///////////////////////////////////////////////////////////////////////////////
template < class Element >
Tree< Element >::Tree( Element e )
{
   mSize = 1;
   mRoot = new Node;
   mRoot->mParent = NULL;
   mRoot->mElement = e;
}

///////////////////////////////////////////////////////////////////////////////
/// Copy Constructor.
/// \pre    An instance of Tree needs to be present.
/// \post   Two instances of the same Vec will exist.
/// \param  Vec is the Tree to copy from.
/// \throw  None
///////////////////////////////////////////////////////////////////////////////
template < class Element >
Tree< Element >::Tree( const Tree & from )
{
   
   if (from.mRoot != this->mRoot)
   {
      this->mRoot = copySubtree(from.mRoot);
   }
   this->mSize = from.mSize;
   
   
}

///////////////////////////////////////////////////////////////////////////////
/// Destructor.
/// \pre    An instance of Tree has been created.
/// \post   The instance of Tree is destroyed.
///////////////////////////////////////////////////////////////////////////////
template < class Element >
Tree< Element >::~Tree( void )
{
   deleteSubtree(mRoot);
}

// OPERATORS

///////////////////////////////////////////////////////////////////////////////
/// Assignment Operator
/// Provide access to the element at the specified rank.
/// \pre    there must be a tree to copy
/// \post   2 copies of the tree will exist
/// \param  a reference to a tree
/// \return a reference to a tree
///////////////////////////////////////////////////////////////////////////////
template < class Element >
Tree< Element >& Tree< Element >::operator=( const Tree & rhs )
{ 
   
   if (rhs.mRoot != this->mRoot)
   {
      deleteSubtree(mRoot);
      this->mRoot = copySubtree(rhs.mRoot);
   }
   this->mSize = rhs.mSize;
   return *this;
}

// OPERATIONS 

///////////////////////////////////////////////////////////////////////////////
/// addchild
/// \pre    There must be a tree to call it on
/// \post   The tree will have an element added to v's child
/// \param  A position
/// \paran  An Element
/// \return A position to the new node (child) 
///////////////////////////////////////////////////////////////////////////////
template < class Element >
typename Tree< Element >::Position Tree< Element >::addChild( const Position& v, const Element e)
{
   if (v.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   Node* temp = new Node;//creating the new node
   v.mPosition->mChildren.push_back(temp);//adding the new node to the children list of its parent
   temp->mParent = v.mPosition;//telling the child that they are adopted
   temp->mElement = e;
   mSize++;//incrimenting the size
   Position temp_pos;
   temp_pos.mPosition = temp;//makeing and storing a position to return of the new node
   return temp_pos;
}

// ACCESS and MUTATE

///////////////////////////////////////////////////////////////////////////////
/// replaceElement
/// \pre    There must be a tree to call it on
/// \post   The Position will be replaced with the element
/// \param  A position 
/// \param  An Element
/// \return None   
///////////////////////////////////////////////////////////////////////////////
template < class Element >
void Tree< Element >::replaceElement(Position v, Element e) 
{
   if (v.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   v.mPosition->mElement = e;
}

///////////////////////////////////////////////////////////////////////////////
/// swapElement
/// \pre    There must be a tree to call it on
/// \post   The Position will be replaced with the element
/// \param  A position to swap
/// \param  A position to swap
/// \return None   
///////////////////////////////////////////////////////////////////////////////
template < class Element >
void Tree< Element >::swapElements(Position v, Position w) 
{
   if (v.isNull() || w.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   Element temp = w.mPosition->mElement;
   w.mPosition->mElement = v.mPosition->mElement;
   v.mPosition->mElement = temp;
}
   
// INQUIRY
///////////////////////////////////////////////////////////////////////////////
/// root
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return The Position to the root of the tree
///////////////////////////////////////////////////////////////////////////////
template < class Element >
void Tree< Element >::print(Position v)
{
   if (v.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   std::cout << v.element();
   PositionIterator children_rec = this->children(v);
   while (children_rec.hasNext())
   {
      std::cout << " ";
      print(children_rec.next());
   }
}

///////////////////////////////////////////////////////////////////////////////
/// root
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return The Position to the root of the tree
///////////////////////////////////////////////////////////////////////////////
template < class Element >
typename Tree< Element >::Position Tree< Element >::root( void ) const
{
   Position root_temp;
   root_temp.mPosition = mRoot;
   return root_temp;
}

///////////////////////////////////////////////////////////////////////////////
/// isRoot
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  A position
/// \return bool if its a root
///////////////////////////////////////////////////////////////////////////////
template < class Element >
bool Tree< Element >::isRoot(Position& v) const
{
   if (v.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   return (v.mPosition == mRoot);
}

///////////////////////////////////////////////////////////////////////////////
/// isExternal
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  A position
/// \return bool if its external
///////////////////////////////////////////////////////////////////////////////
template < class Element >
bool Tree< Element >::isExternal(Position& v) const
{
   if (v.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   return (v.mPosition->mChildren.size() == 0);
}

///////////////////////////////////////////////////////////////////////////////
/// isInternal
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  A position
/// \return bool if its internal
///////////////////////////////////////////////////////////////////////////////
template < class Element >
bool Tree< Element >::isInternal(Position& v) const
{
   if (v.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   return (v.mPosition->mChildren.size() != 0);
}

///////////////////////////////////////////////////////////////////////////////
/// size
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return the size of a tree
///////////////////////////////////////////////////////////////////////////////
template < class Element >
unsigned int Tree< Element >::size( void ) const
{
   return mSize;
}

///////////////////////////////////////////////////////////////////////////////
/// parent
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  A position
/// \return the parent of a node   
///////////////////////////////////////////////////////////////////////////////
template < class Element >
typename Tree< Element >::Position Tree< Element >::parent( const Position& v) const
{
   if (v.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   Tree::Position p;
   p.mPosition = (v.mPosition->mParent);
   return p;
   
}
///////////////////////////////////////////////////////////////////////////////
/// children
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  A position
/// \return the parent of a node
///////////////////////////////////////////////////////////////////////////////
template < class Element >
typename Tree< Element >::PositionIterator Tree< Element >::children(const Position& v) const
{
   if (v.isNull())
   {
      throw std::out_of_range("OMFG WTFBBQ PWNT");
   }
   PositionIterator temp_it;
   for (unsigned int i = 0; i < (v.mPosition->mChildren.size());i++)
   {
      Position temp_pos(v.mPosition->mChildren[i]);
      (temp_it.mPositionIterator).push_back(temp_pos);
   }
   return temp_it;
}

///////////////////////////////////////////////////////////////////////////////
/// elements
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return an Iterator of Elements
///////////////////////////////////////////////////////////////////////////////
template < class Element >
typename Tree< Element >::ElementIterator Tree< Element >::elements(void ) const
{
   ElementIterator x;
   getelements(x,root());
   return x;
}

///////////////////////////////////////////////////////////////////////////////
/// positions
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return an Iterator of Positions
///////////////////////////////////////////////////////////////////////////////
template < class Element >
typename Tree< Element >::PositionIterator Tree< Element >::positions(void ) const
{
   PositionIterator x;
   getpositions(x,root());
   return x;
}

///////////////////////////////////////////////////////////////////////////////
/// getelements
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return an Iterator of Elements
///////////////////////////////////////////////////////////////////////////////
template < class Element >
void Tree< Element >::getelements(ElementIterator& iter, Position p ) const
{
   iter.mElementIterator.push_back( p.element() );
   Element i = p.element();
   PositionIterator children_rec = children(p);
   while (children_rec.hasNext())
   {
      getelements(iter,(children_rec.next()));
   }
}

///////////////////////////////////////////////////////////////////////////////
/// getpositions
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return an Iterator of Positions
///////////////////////////////////////////////////////////////////////////////
template < class Element >
void Tree< Element >::getpositions(PositionIterator& iter, Position p ) const
{
   iter.mPositionIterator.push_back( p );
   PositionIterator children_rec = children(p);
   while (children_rec.hasNext())
   {
      getpositions(iter,(children_rec.next()));
   }
}


// PROTECTED  

// PRIVATE  
///////////////////////////////////////////////////////////////////////////////
/// deleteSubtree
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return an Iterator of Positions
///////////////////////////////////////////////////////////////////////////////
template < class Element >
void Tree< Element >::deleteSubtree( Node * p)
{
   typename std::vector<Node *>::iterator it = p->mChildren.begin();
   while (it != p->mChildren.end())
   {
      deleteSubtree(*it);
      it++;
   }
   delete p;
}

///////////////////////////////////////////////////////////////////////////////
/// copySubTree
/// \pre    There must be a tree to call it on
/// \post   None
/// \param  None
/// \return an Iterator of Positions
///////////////////////////////////////////////////////////////////////////////
template < class Element >
typename Tree< Element >::Node * Tree< Element >::copySubtree( Node * p)
{
   Node* Temp = new Node;
   Node* New_Child;
   Temp->mParent = p->mParent;
   Temp->mElement = p->mElement;
   
   typename std::vector<Node *>::iterator it = p->mChildren.begin();
   while (it != p->mChildren.end())
   {
      New_Child = copySubtree(*it);
      it++;
      Temp->mChildren.push_back(New_Child);
      New_Child->mParent = Temp;
   }
   return Temp;
   
}

#endif

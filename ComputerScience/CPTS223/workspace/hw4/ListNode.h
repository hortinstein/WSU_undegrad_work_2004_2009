#ifndef LISTNODE_H
#define LISTNODE_H

///////////////////////////////////////////////////////////////////////////////
/// \struct       ListNode
/// \author       Alex Hortin 
/// \date         January 25 2006
/// \brief        A resizable random-access sequence.
///
/// A node that is present within our playlist of nodes.  Is a struct for easy 
/// access.
///
/// REVISION HISTORY
///
/// 2/16/2006 Templating the class began
///
///////////////////////////////////////////////////////////////////////////////

template <class Element >
struct ListNode
{
    Element elem;
    ListNode<Element> * next;
    ListNode<Element> * prev;
    
    //  Constructor to initialize node pointers.
    //  If provided, a copy of the Element argument
    //  is stored in this node, otherwise, a default
    //  Elment is stored.
    ListNode( const Element & sf = Element() ) :
        elem( sf ), next( 0 ), prev( 0 )
    {
    }
};

#endif

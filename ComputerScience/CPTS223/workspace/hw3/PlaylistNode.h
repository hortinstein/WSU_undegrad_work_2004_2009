#ifndef PLAYLISTNODE_H
#define PLAYLISTNODE_H

///////////////////////////////////////////////////////////////////////////////
/// \struct       PlaylistNode
/// \author       Alex Hortin 
/// \date         January 25 2006
/// \brief        A resizable random-access sequence.
///
/// A node that is present within our playlist of nodes.  Is a struct for easy 
/// access.
///
/// REVISION HISTORY
///
/// NONE
///////////////////////////////////////////////////////////////////////////////

#include "Soundfile.h"
struct PlaylistNode
{
    Soundfile elem;
    PlaylistNode * next;
    PlaylistNode * prev;
    
    //  Constructor to initialize node pointers.
    //  If provided, a copy of the Soundfile argument
    //  is stored in this node, otherwise, a default
    //  Soundfile is stored.
    PlaylistNode( const Soundfile & sf = Soundfile() ) :
        elem( sf ), next( 0 ), prev( 0 )
    {
    }
};

#endif


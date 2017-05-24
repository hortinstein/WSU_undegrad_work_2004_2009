#ifndef PLAYLISTITERATOR_H    // include guard
#define PLAYLISTITERATOR_H

///////////////////////////////////////////////////////////////////////////////
/// \class        PlaylistIterator
/// \author       Alex Hortin 
/// \date         Febuary 6 2006
/// \brief        an iterator class to target Playlist
///
/// An iterator that can be used to modify and target the class Playlist.  It
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

#include <iostream>
#include <stdexcept>
#include <vector>
// LOCAL INCLUDES
//

#include "PlaylistNode.h"//the node to be defined
// FORWARD REFERENCES
//

// CONSTANTS
//

class PlaylistIterator
{
   public:
   
	friend class Playlist;

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the PlaylistIterator class with no position in any list.
   /// \param  None
   /// \throw  None
  PlaylistIterator( void );
  
// OPERATORS
   
   /// equality operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   NONE
   /// \param  An element of a Playlist.
   /// \return bool based on whether it is equal or not
   /// \throw  NONE   
   bool operator==( const PlaylistIterator & rhs ) const;
   
   /// non-equality operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   NONE
   /// \param  An element of a Playlist.
   /// \return bool based on whether it is equal or not
   /// \throw  NONE   
   bool operator!=( const PlaylistIterator & rhs ) const; 
   
   /// pre incriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the next value.
   /// \param  A PlaylistIterator that calls it
   /// \return A refence to itself
   /// \throw  NONE
   PlaylistIterator & operator++( void );

   /// pre decriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the previous value.
   /// \param  A vector that calls it
   /// \return A refence to itself
   /// \throw  NONE
   PlaylistIterator & operator--( void );
	   
   /// post incriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the next value.
   /// \param  A PlaylistIterator that calls it
   /// \return The next value
   /// \throw  NONE  
   PlaylistIterator operator++( int );

	/// post decriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the previous value.
   /// \param  A vector that calls it
   /// \return The next value
   /// \throw  NONE  
   PlaylistIterator operator--( int );
	
	/// Reference operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a vector.
   /// \return A refence to that element
   /// \throw  NONE
   const Soundfile &  operator*( void ) const;
   
   /// -> operator.
   /// \pre    The target must be assigned a value in memory.
   /// \post   A reference value will be returned.
   /// \param  An element of a vector.
   /// \return A pointer to that element denoted by the iterator
   /// \throw  NONE 
   const Soundfile * operator->( void ) const;

	
// OPERATIONS 
  
// ACCESS and MUTATE
   
// INQUIRY
   
// MEMBER VARIABLES
private:
	//The node that it points too
   PlaylistNode * mIterator;
   
}; // end of class PlaylistIterator

#endif  // PlaylistIterator.h

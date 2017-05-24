#ifndef PLAYLIST_H    // include guard
#define PLAYLIST_H

///////////////////////////////////////////////////////////////////////////////
/// \class        Playlist
/// \author       Alex Hortin 
/// \date         Febuary 6 2006
/// \brief        A doubly linked list of PlaylistNodes
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

#include <iostream>
#include <stdexcept>
#include <vector>
// LOCAL INCLUDES
//
#include "PlaylistIterator.h"//the iterator
#include "Soundfile.h"//the soundfile
#include "PlaylistNode.h"//the node to be defined
// FORWARD REFERENCES
//

// CONSTANTS
//

class Playlist
{
   public:
   

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Playlist class with no elements.
	///         Sets head and tail equal to head since they are dummy nodes.
   /// \param  None
   /// \throw  None
  Playlist( void );
  
   /// Copy Constructor.
   /// \pre    An instance of Playlist needs to be present.
   /// \post   Two instances of the same Playlist will exist.
   /// \param  Playlist is the Playlist to copy from.
   /// \throw  None
   Playlist( const Playlist & from );

   /// Destructor.
   /// \pre    An instance of Playlist has been created.
   /// \post   The instance of Playlist is destroyed.
   ~Playlist( void );
	
// OPERATORS

   /// Assignment operator.
   /// \param  rhs is the object to assign from.
   /// \return A reference to this Vec.
   Playlist& operator=( const Playlist & rhs ); 
	 
// OPERATIONS 
  
// ACCESS and MUTATE
   
	/// push_back
   /// \pre    A valid Soundfile
   /// \post   A new Soundfile will be appended to the list
   /// \param  a Soundfile
   /// \return None
   /// \throw  None
   void push_back(const Soundfile & sf );
	
	/// insert
   /// \pre    A valid iterator and soundfile
   /// \post   A new file will be inserted
   /// \param  an iterator containing target in playlist
	/// \param  a soundfile to insert
   /// \return an iterator representing the new position of the new soundfile
   /// \throw  None
   PlaylistIterator insert(PlaylistIterator it, const Soundfile & sf);
	
	/// erase
   /// \pre    A valid iterator and soundfile
   /// \post   A new file will be inserted
   /// \param  iterator containing target in playlist
   /// \return the position of the next soundfile in the list after the one that got erased. 
   /// \throw  None
   PlaylistIterator erase(PlaylistIterator it);
	
// INQUIRY
   
	/// size
   /// \pre    A valid playlist
   /// \post   none
   /// \param  none
   /// \return an unsigned int containing number of soundfiles
   /// \throw  None
   unsigned int size(void);
	
	/// begin
   /// \pre    A valid playlist
   /// \post   none
   /// \param  none
   /// \return a Playlist Iterator containing pointing to the beginning Soundfile
   /// \throw  None
   PlaylistIterator begin(void) const;
	
	/// end
   /// \pre    A valid playlist
   /// \post   none
   /// \param  none
   /// \return a Playlist Iterator containing pointing to the end dummy file
   /// \throw  None
   PlaylistIterator end(void) const;
	
	/// size
   /// \pre    A valid Soundfile
   /// \post   The list is printed in Std::cout
   /// \param  none
   /// \return None
   /// \throw  None
   void print(void);
// MEMBER VARIABLES
private:
   //the head of the list
	PlaylistNode* mHead;

	//the tail of the list
	PlaylistNode* mTail;
	
	//number of Soundfiles stored
	unsigned int mSize;
   

}; // end of class Soundfile

#endif  // Playlist.h

#ifndef BOARD_H//guard conditional compilation
#define BOARD_H//guard conditional compilation

///////////////////////////////////////////////////////////////////////////////
/// \class        board
/// \author      Alex Hortin
/// \date         2/28/06  
/// \brief	This is the file that defines all the functions that handle board setup and board display
///
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//
#include <iostream>
#include <string>//string.h include
#include <vector>//vector.h include
#include <stdio.h>

// LOCAL INCLUDES
//
#include "board.h"
// FORWARD REFERENCES
//

// CONSTANTS
//

class board
{
   public:
// LIFECYCLE
   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the board is created.
   /// \param  None
   /// \throw  None
   board( void );//the basic constructor used for testing

   /// Destructor.
   /// \pre    An instance of board has been created.
   /// \post   The instance of board is destroyed.
   ~board();//the destructor
	
// OPERATORS

// OPERATIONS 

// ACCESS and MUTATE
   
   /// dropChip
   /// \pre    a board has been constructed
   /// \post   a chip is added
   /// \param number of player
   /// \return a char to indicate status
   /// \throw  None
   const char* dropChip(int player, int column);

// INQUIRY

   /// printBoard prints an ascii board of the informatio stored in the board
   /// \pre    a board has been constructed
   /// \post   nothing
	/// \param none
   /// \return None
   /// \throw  None
	void printboard(void);
	
// MEMBER VARIABLES


private:
// OPERATIONS

// ACCESS and MUTATE
	
// MEMBER VARIABLES
   int mBoard[7][6];
}; // end of class Name

#endif  // BOARD_H

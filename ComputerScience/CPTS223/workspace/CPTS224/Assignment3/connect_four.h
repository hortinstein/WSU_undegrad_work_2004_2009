#ifndef CONNECT_FOUR_H//guard conditional compilation
#define CONNECT_FOUR_H//guard conditional compilation

///////////////////////////////////////////////////////////////////////////////
/// \class       connect_four
/// \author      Alex Hortin
/// \date         2/28/06  
/// \brief	This is the file that defines all the functions that play the game
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
#include "connect_four.h"

// FORWARD REFERENCES
//

// CONSTANTS
//

class connect_four
{
   public:
// LIFECYCLE
   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the connect_four is created.
   /// \param  None
   /// \throw  None
   connect_four( board );//the basic constructor used for testing

   /// Destructor.
   /// \pre    An instance of connect_four has been created.
   /// \post   The instance of connect_four is destroyed.
   ~connect_four();//the destructor
	
// OPERATORS

// OPERATIONS 

// ACCESS and MUTATE
   
   /// startGame
   /// \pre    a connect_four has been constructed
   /// \post   a chip is added
   /// \param number of player
   /// \return a bool if drop could be made successfully
   /// \throw  None
   void startGame();

// INQUIRY
	
// MEMBER VARIABLES


private:
// OPERATIONS

// ACCESS and MUTATE
	
// MEMBER VARIABLES
   board* mBoard;
   int mPlayerturn;
}; // end of class Name

#endif  // connect_four_H

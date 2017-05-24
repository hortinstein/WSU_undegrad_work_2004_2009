#ifndef DECKOFCARDS_H    // include guard
#define DECKOFCARDS_H

///////////////////////////////////////////////////////////////////////////////
/// \class        DeckofCards
/// \author       Alex Hortin 
/// \date         Febuary 6 2006
/// \brief        A Card Deck class
///
/// A class that stores a deck of cards and organizes it into lists pertaining
/// to each suit and than can shuffle it
///
/// REVISION HISTORY
///
/// None
///
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
// LOCAL INCLUDES
//
#include "List.h"
#include "Card.h"//the node to be defined
#include "DeckofCards.h"//the node to be defined
// FORWARD REFERENCES
//

// CONSTANTS
//

class DeckEmpty 
{   
public:
// LIFECYCLE
   
   /// Constructor.
   /// \pre    None.
   /// \post   None.
   /// \param  err A string describing the condition that gave rise 
   ///         to the exception.
   /// \return Nothing. 
   DeckEmpty( const std::string& err ) : mErrorMsg( err ) { }

   /// getMessage
   /// Return a copy of the error message for this object.
   /// \pre    None.
   /// \post   None.
   /// \param  None
   /// \return A copy of the error message string. 
   std::string what( void ) const { return mErrorMsg; }
   
private:                               
// MEMBER VARIABLES

   std::string mErrorMsg;  // an error message describing the 
                           // exceptional condition
};

class DeckofCards
{
   public:

// LIFECYCLE

	/// Default Constructor.
   /// \pre    None
   /// \post   A defualt DeckofCards is created with 52 unique playing cards stored in order by suit
   /// \param  None
   /// \throw  None
   DeckofCards(void);

// OPERATORS
	
// OPERATIONS 
	/// shuffle
   /// \pre    A valid DeckofCards
   /// \post   the cards are mixed up order
   /// \param  None
   /// \return none
   /// \throw  None
   void shuffle( void );
  
// ACCESS and MUTATE
	/// drawCard
   /// \pre    A valid Deck
   /// \post   a card is taken away from the top (o is bottom);
   /// \param  None
   /// \return the card drawn
   /// \throw  None
   Card drawCard( void );
	
// INQUIRY
	
	/// size
   /// \pre    an initailized deck of cards
   /// \post   none
   /// \param  none
   /// \return the number of cards in the deck
   /// \throw  None
   unsigned int size( void ) const;
	
	/// printDeck
   /// \pre    an initailized deck of cards
   /// \post   the deck will be printed out to the console
   /// \param  none
   /// \return none
   /// \throw  None
	void printDeck( void ) const;
	
	/// bottom_for_trump
   /// \pre    an initailized deck of cards
   /// \post   the deck will be printed out to the console
   /// \param  none
   /// \return the last card dealt for determining the trump suit;
   /// \throw  None
	Card bottom_for_trump( void ) const;
// MEMBER VARIABLES
private:
	//the deck
	std::vector<Card> mDeck;
	
	//the top card
	std::vector<Card>::iterator mTop;
	
}; // end of class Card

#endif

#ifndef WHIST_H    // include guard
#define WHIST_H

///////////////////////////////////////////////////////////////////////////////
/// \class        Whist
/// \author       Alex Hortin 
/// \date         March 6 2006
/// \brief        A Whist class
///
/// A class that stores uses a deck or cards and four hands enabling a smart 
/// program with all of the tools to play the game whist
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
#include "HandOfCards.h"
#include "DeckofCards.h"
#include "Whist.h"
// FORWARD REFERENCES
//

// CONSTANTS
//


class Whist
{
   public:

// LIFECYCLE

	/// Default Constructor.
   /// \pre    None
   /// \post   A defualt Whist is made with 4 hands and one deck
   /// \param  None
   /// \throw  None
 	Whist(void);

// OPERATORS
	
// OPERATIONS 

	/// deal
   /// \pre 	A deck must be constructed and populated
   /// \post   the cards are mixed up and all the cards are dealt to the four hands
   /// \param  None
   /// \return none
   /// \throw  None
   void deal( void );
	
	/// playCard
   /// \pre    A valid Card
   /// \post   a card is removed from a hand
   /// \param  suit a valid string for suit
   /// \return A card
   /// \throw  InvalidSuit if invalid suit is specified
	/// \throw InvalidPip if invalid pip is specified
   Card playCard( const std::string & suit, const std::string & pip );
	
	/// updateTricks
   /// \pre    A game is in progress
   /// \post   determines a winner and updates score
   /// \param  none
   /// \return a reference to a hand of cards representing that player
	const HandOfCards & updateTricks( void );
	
	/// updatePoints
   /// \pre    A game is in progress
   /// \post   determines a winner and updates score
   /// \param  none
   /// \return a reference to a hand of cards representing that player
	void updatePoints( void );
	
// ACCESS and MUTATE
	
// INQUIRY

	/// currentPlayer
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return a reference to the current trick
	const HandOfCards & currentPlayer( void );	

	/// trumpSuit
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return the h,s,d,c for what suit is the trumpsuit
	std::string trumpSuit( void ) const;
	
	/// isTrickOver
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return a bool if the trick is over
	bool isTrickOver( void ) const;
	
	/// isHandOver
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return a bool if the Hand is over
	bool isHandOver( void ) const;
	
	/// currentTrick
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return a reference to the current trick
	const std::vector<Card> & currentTrick( void ) const;
	
	/// tricksNorthSouth
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return number of tricks won by north south
	unsigned int tricksNorthSouth( void ) const;
	
	/// tricksEastWest
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return number of tricks won by east west
	unsigned int tricksEastWest( void ) const;
	
	/// pointsNorthSouth
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return total number of points for north south
	unsigned int pointsNorthSouth( void ) const;
	
	/// pointsEastWest
   /// \pre    A game is in progress
   /// \post   none
   /// \param  none
   /// \return total number of points for east west
	unsigned int pointsEastWest( void ) const;
	
	/// isGameOver
   /// \pre    A game is started
   /// \post   none
   /// \param  none
   /// \return checks to see if a game is over
	bool isGameOver(void);
	
	/// printAllHands
   /// \pre    A game is started
   /// \post   none
   /// \param  none
   /// \return prints all the hands
	void printAllHands(void);
	
	/// returnAllHands
   /// \pre    A game is started
   /// \post   none
   /// \param  none
   /// \return returns all the hands
	std::vector<HandOfCards> & returnAllHands(void);
	
// MEMBER VARIABLES
private:
	//the deck
	DeckofCards mDeck;
	//the different hands 
	std::vector<HandOfCards> mHands;
	//the current trick
	std::vector<Card> mCurrentTrick;	
	//the current trick
	std::vector<int> mCurrentTrickOrderPlayed;	
	//dealer button
	unsigned int mDealer;
	//current turn
	unsigned int mTurn;
	//the current trump suit
	std::string mTrump;
	//the suit for the current trick
	std::string mTrick_suit;
	//the score of tricks for eastwest
	unsigned int mEastWest_tricks;
	//the score of tricks for northsouth
	unsigned int mNorthSouth_tricks;
	//the score of points for eastwest
	unsigned int mEastWest_points;
	//the score of points for northsouth
	unsigned int mNorthSouth_points;

}; // end of class Card

#endif

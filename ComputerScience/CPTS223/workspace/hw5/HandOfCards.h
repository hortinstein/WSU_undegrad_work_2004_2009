#ifndef HANDOFCARDS_H    // include guard
#define HANDOFCARDS_H

///////////////////////////////////////////////////////////////////////////////
/// \class        HandOfCards
/// \author       Alex Hortin 
/// \date         Febuary 6 2006
/// \brief        A Card handler class
///
/// A class that stores a hand of cards and organizes it into lists pertaining
/// to each suit
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
// LOCAL INCLUDES
//
#include "List.h"
#include "Card.h"//the node to be defined
#include "HandOfCards.h"//the node to be defined
// FORWARD REFERENCES
//

// CONSTANTS
//

class HandOfCards
{
   public:
  
	typedef List<Card>::iterator iterator;
// LIFECYCLE
	/// Default Constructor.
   /// \pre    None
   /// \post   A defualt HandOfCards is created
   /// \param  None
   /// \throw  None
   HandOfCards();

   /// Copy Constructor.
   /// \pre    An instance of HandOfCards needs to be present.
   /// \post   Two instances of the same HandOfCards will exist.
   /// \param  from is the HandOfCards to copy from.
   /// \throw  None
   HandOfCards(const HandOfCards & from );
   
	/// Destructor.
   /// \pre    An instance of HandOfCards has been created.
   /// \post   The instance of HandOfCards is destroyed.
   ~HandOfCards();//the destructor
// OPERATORS

   /// Assignment operator.
   /// \param  rhs is the object to assign from.
   /// \return A reference to this HandOfCards.
   HandOfCards& operator=(const HandOfCards & rhs ); 
	
// OPERATIONS 
  
// ACCESS and MUTATE
	/// addCard
   /// \pre    A valid Card
   /// \post   a card is added
   /// \param  Card the card to be added
   /// \return none
   /// \throw  None
   void addCard( const Card & c );
	
	/// playSuit
   /// \pre    A valid Card
   /// \post   a card is removed
   /// \param  suit a valid string for suit
   /// \return A card
   /// \throw  InvalidSuit if invalid suit is specified
   Card playSuit( const std::string & suit );
	
// INQUIRY
   
	/// beginHearts
   /// \pre    A valid Card
   /// \post   none
   /// \param  none
   /// \return an iterator to beginning of Hearts
   /// \throw  None
   HandOfCards::iterator beginHearts( void );
	
	/// beginSpades
   /// \pre    A valid Card
   /// \post   none
   /// \param  none
   /// \return an iterator to beginning of Spades
   /// \throw  None
   HandOfCards::iterator beginSpades( void );
	
	/// beginClubs
   /// \pre    A valid Card
   /// \post   none
   /// \param  none
   /// \return an iterator to beginning of Clubs
   /// \throw  None
   HandOfCards::iterator beginClubs( void );
	
	/// beginDiamonds
   /// \pre    A valid instance of HandofCards
   /// \post   none
   /// \param  none
   /// \return an iterator to beginning of Diamonds
   /// \throw  None
   HandOfCards::iterator beginDiamonds( void );
	
	/// beginHearts
   /// \pre    A valid Card
   /// \post   none
   /// \param  none
   /// \return an iterator to beginning of hearts
   /// \throw  None
   HandOfCards::iterator end( void );
	
	/// printHand
   /// \pre    A valid Hand
   /// \post   none
   /// \param  none
   /// \return a ostream containing the hand to print to console
   /// \throw  None
   std::ostream & printHand( std::ostream & os );

// MEMBER VARIABLES
private:
	//mHand
	List<Card> mHand;
	
	// beginHearts
	List<Card>::iterator mBeginHearts;

   // beginSpades
	List<Card>::iterator mBeginSpades;
	
   // beginClubs
	List<Card>::iterator mBeginClubs;
	
   // beginDiamonds
	List<Card>::iterator mBeginDiamonds;
	
   // end
	List<Card>::iterator mEnd;
	
}; // end of class Card

#endif

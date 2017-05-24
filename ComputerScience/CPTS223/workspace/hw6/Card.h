#ifndef CARD_H    // include guard
#define CARD_H

///////////////////////////////////////////////////////////////////////////////
/// \class        Card
/// \author       Alex Hortin 
/// \date         Febuary 6 2006
/// \brief        A Card Class
///
/// A class that stores the minimum details nessecary to identify and play a
/// card.  Also include error checking
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
#include "Card.h"//the node to be defined

// FORWARD REFERENCES
//

// CONSTANTS
//

class InvalidSuit 
{   
public:
// LIFECYCLE
   
   /// Constructor.
   /// \pre    None.
   /// \post   None.
   /// \param  err A string describing the condition that gave rise 
   ///         to the exception.
   /// \return Nothing. 
   InvalidSuit( const std::string& err ) : mErrorMsg( err ) { }

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

class InvalidPip 
{   
public:
// LIFECYCLE
   
   /// Constructor.
   /// \pre    None.
   /// \post   None.
   /// \param  err A string describing the condition that gave rise 
   ///         to the exception.
   /// \return Nothing. 
   InvalidPip( const std::string& err ) : mErrorMsg( err ) { }

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


class Card
{
   public:
   
	
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Card class with no elements.
	///         Sets head and tail equal to head since they are dummy nodes.
   /// \param  None
   /// \throw  None
  	Card( void );
  
   /// Specific constructor
   /// \pre    An instance of Card needs to be present.
   /// \post   Two instances of the same Card will exist.
   /// \param  suit is the cards suit
	/// \param	pip is the cards pip
   /// \throw  InvalidPip if pip is invalid
	/// \throw	InvalidSuit if suit is invalid
   Card( const std::string & suit, const std::string & pip );

// OPERATORS

   /// pre decriment operator.
   /// \pre    The iterator must point to a value.
   /// \post   The iterator moves to the previous value.
   /// \param  A vector that calls it
   /// \return A refence to itself
   /// \throw  NONE
   bool operator<(const Card & rhs) const ;
	
// OPERATIONS 
  
// ACCESS and MUTATE
	
// INQUIRY
   
	/// suit
   /// \pre    A valid Card
   /// \post   none
   /// \param  none
   /// \return a string containing the suit
   /// \throw  None
   std::string suit( void ) const ;
	
	/// pip
   /// \pre    A valid Card
   /// \post   none
   /// \param  none
   /// \return a string containing the pip
   /// \throw  None
 	std::string pip( void ) const;

// MEMBER VARIABLES
private:
   //pip
	std::string mPip;

	//suit
	std::string mSuit;
	

}; // end of class Card

#endif

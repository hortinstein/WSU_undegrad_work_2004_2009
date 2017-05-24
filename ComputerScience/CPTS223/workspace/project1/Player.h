#ifndef PLAYER_H    // include guard
#define PLAYER_H

///////////////////////////////////////////////////////////////////////////////
/// \class        Player
/// \author       Alex Hortin 
/// \date         March 20 2006
/// \brief        A class that stores a players details
///
/// This class stores a players details and can modify HP, award XP, save the
/// the level and skills of that player.
///
/// REVISION HISTORY
///
/// None
///
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
// LOCAL INCLUDES
//
#include "Player.h"//the node to be defined

// FORWARD REFERENCES
//

// CONSTANTS
//

class InvalidFile
{
public:
// LIFECYCLE
   
   /// Constructor.
   /// \pre    None.
   /// \post   None.
   /// \param  err A string describing the condition that gave rise 
   ///         to the exception.
   /// \return Nothing. 
   InvalidFile( const std::string& err ) : mErrorMsg( err ) { }

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


class Player
{
   public:
   
	
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of player is constructed and new stats file will be contructed
   /// \param  string for the username
   /// \throw  None
  	Player(std::string name);

// OPERATORS
	
// OPERATIONS 

	/// takeDamage
   /// \pre    A valid Player
   /// \post   hitpoints are reduced
   /// \param  int for the value of the Hit Points to take away
   /// \return none
   /// \throw  None
   void takeDamage( int hp );  	

	/// useFuel
   /// \pre    A valid Player
   /// \post   fuel is reduced by the param
   /// \param  int for the x value of the Hit Points
   /// \return none
   /// \throw  None
   void useFuel( int fuel );  	
	
	/// setLocation
   /// \pre    A valid Player
   /// \post   hitpoints are gained or reduced
   /// \param  int for the x value of the Hit Points
   /// \return none
   /// \throw  None
   void setLocation( int x );  	

	
// ACCESS and MUTATE
	
// INQUIRY
   
	/// name
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return a string containing the name
   /// \throw  None
   std::string name( void ) const ;

	/// getLocation
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return int for the x value of the location
   /// \throw  None
	int getLocation( ) const ; 
	
	/// hitPoints
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return int for the x Hit Points Left
   /// \throw  None
	int hitPoints( void ) const ; 

	/// isAlive
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return a bool true if alive, false if dead
   /// \throw  None
	bool isAlive( void ) const ; 

	/// getFuelRemaining
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return int for the x value of the remaining fuel
   /// \throw  None
	int getFuelRemaining(void ) const ; 
// MEMBER VARIABLES
private:
   //Name
	std::string mName;
	
	//Location int x
	int mLocation;
	
	//HitPoints
	int mHitPoints;
	
	//HitPoints
	int mFuel;

}; // end of class Card

#endif

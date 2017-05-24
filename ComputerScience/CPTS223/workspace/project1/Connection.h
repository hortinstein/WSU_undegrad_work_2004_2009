#ifndef CONNECTION_H    // include guard
#define CONNECTION_H

///////////////////////////////////////////////////////////////////////////////
/// \class        Connection
/// \author       Alex Hortin 
/// \date         April 3 2006
/// \brief        A polymorphic class that handles communication
///
/// All this class is is a polymorphic container class for chris's class that
/// that handles all of my communication for me
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
#include <sstream>
#include <vector>
// LOCAL INCLUDES
//
#include "Connection.h"
#include "Socket.h"
// FORWARD REFERENCES
//

// CONSTANTS
//


class Connection
{
   public:
   
	struct Shot
	{
		unsigned int power;
		unsigned int angle;
		unsigned int payload;
	};
// LIFECYCLE

   /// Default constructor. PURE VIRTUAL
   /// \pre    None
   /// \post   An instance of player is constructed and new stats file will be contructed
   /// \param  string for the username
   /// \throw  None
  	Connection(void );

	/// Destructor.
   /// \pre    There must be something to destroy
   /// \post   Poof! that virtual bitch is gone!
   virtual ~Connection( void );

// OPERATORS
	
// OPERATIONS 

	/// makeConnection
   /// \pre    a connection class with a type is made
   /// \post   All the connections will be made
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void makeConnection(std::string username) = 0;  	
	
	/// setupGame
   /// \pre    A connection with everyone present
   /// \post   all clients will be sent the server data
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void setupGame(int location) = 0;  
	
	/// isReady
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void isReady() = 0;  
	
	/// sendMyTurn
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual Shot sendMyTurn(Shot theShot) = 0;  
	
	/// waitForData
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual Shot waitForData() = 0;  
	
// ACCESS and MUTATE
	
// INQUIRY

	/// getPlayerNames
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return a vector of player names
   /// \throw  None
	std::vector<std::string> getPlayerNames(void ) const ; 
	
	/// getPlayerLocations
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return a vector of player locations
   /// \throw  None
	std::vector<int> getPlayerLocations(void ) const ; 
	
	/// getSeed
   /// \pre    make connection must have already be ran
   /// \post   none
   /// \param  none
   /// \return a time_t for the seed value
   /// \throw  None
	time_t getSeed(void ) const; 
	
	/// isMyTurn
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   none
   /// \param  none
   /// \return a bool if it is their turn or not
   /// \throw  None
   bool isMyTurn(int i);  
	
	
// MEMBER VARIABLES
protected:
	//seed value
	time_t mSeed;
	//reprenting what turn they will go
	int mMyTurnNumber;
	//this usersname
	std::string mUserName;

	//A string of Player names
	std::vector<std::string> mNames;
	//A vector of player locations in same order 
	std::vector<int> mLocations;
	
private:	

}; // end of class Card

#endif

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
		unsigned int left;
		unsigned int right;
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

	/// makeConnection makes the connections between all the players and the server, it is polymorphic
   /// \pre    a connection class with a type is made
   /// \post   All the connections will be made
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void makeConnection(std::string username) = 0;  	
	
	/// setupGame this sets up the game and exchanges the data so everyone knows usernames and locations
   /// \pre    A connection with everyone present
   /// \post   all clients will be sent the server data
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void setupGame(int location) = 0;  
	
	/// isReady returns after all clients and the server have called this function
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void isReady() = 0;  
	
	/// sendMyTurn a polymorphic function to send everyone a turn, the server than relays
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual Shot sendMyTurn(Shot theShot) = 0;  
	
	/// waitForData is the function that waits for the server to relay the turns to everyone
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual Shot waitForData() = 0;  
	
// ACCESS and MUTATE
	

// INQUIRY

	/// getPlayerNames returns all of the player names in a vector
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return a vector of player names
   /// \throw  None
	std::vector<std::string> getPlayerNames(void ) const ; 
	
	/// getPlayerLocations returns all of the player locations in a vector
   /// \pre    A valid Player
   /// \post   none
   /// \param  none
   /// \return a vector of player locations
   /// \throw  None
	std::vector<int> getPlayerLocations(void ) const ; 
	
	/// getSeed seeds the time and returns it to relay to the clients
   /// \pre    make connection must have already be ran
   /// \post   none
   /// \param  none
   /// \return a time_t for the seed value
   /// \throw  None
	time_t getSeed(void ) const; 
	
	/// isMyTurn returns true if its the users turn
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

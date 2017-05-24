#ifndef CLIENTCONNECTION_H    // include guard
#define CLIENTCONNECTION_H

///////////////////////////////////////////////////////////////////////////////
/// \class        ClientConnection
/// \author       Alex Hortin 
/// \date         April 3 2006
/// \brief        A polymorphic class that handles communication
///
/// All this class is is a polymorphic container class for chris's class that
/// that handles all of my communication for me.  This inherits 
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
// LOCAL INCLUDES
//
#include "Connection.h"//the node to be defined
#include "ClientConnection.h"//the node to be defined
#include "Socket.h"
// FORWARD REFERENCES
//

// CONSTANTS
//


class ClientConnection: public Connection
{
   public:
   
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of player is constructed and new stats file will be contructed
   /// \param  string for the username
   /// \throw  None
  	ClientConnection(std::string ip);
	
	/// Destructor.
   /// \pre    There must be something to destroy
   /// \post   Poof! that virtual bitch is gone!
   ~ClientConnection( void );
// OPERATORS
	
// OPERATIONS 

	/// makeConnection makes the connections between all the players and the server, it is polymorphic
   /// \pre    a connection class with a type is made
   /// \post   All the connections will be made
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void makeConnection(std::string username);  	
	
	/// setupGame this sets up the game and exchanges the data so everyone knows usernames and locations
   /// \pre    A connection with everyone present
   /// \post   all clients will be sent the server data
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void setupGame(int location);  
	
	/// isReady returns after all clients and the server have called this function
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void isReady();   
	
	/// sendMyTurn a polymorphic function to send everyone a turn, the server than relays
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual Shot sendMyTurn(Shot theShot);  
	
	/// waitForData is the function that waits for the server to relay the turns to everyone
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual Shot waitForData();  
	
// ACCESS and MUTATE

// INQUIRY
	
// ACCESS and MUTATE
	
// INQUIRY
	
// MEMBER VARIABLES
private:
	std::string mIP;
	Socket * mConnection;

}; // end of class Card

#endif

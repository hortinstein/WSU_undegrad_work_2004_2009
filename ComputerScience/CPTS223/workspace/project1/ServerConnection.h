#ifndef SERVERCONNECTION_H    // include guard
#define SERVERCONNECTION_H

///////////////////////////////////////////////////////////////////////////////
/// \class        ServerConnection
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
#include "ServerConnection.h"//the node to be defined
#include "Socket.h"
// FORWARD REFERENCES
//

// CONSTANTS
//


class ServerConnection: public Connection
{
   public:
   
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of player is constructed and new stats file will be contructed
   /// \param  string for the username
   /// \throw  None
  	ServerConnection(int players);

	/// Destructor.
   /// \pre    There must be something to destroy
   /// \post   Poof! that virtual bitch is gone!
   virtual ~ServerConnection( void );
// OPERATORS
	
// OPERATIONS 

	/// makeConnection
   /// \pre    a connection class with a type is made
   /// \post   All the connections will be made
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void makeConnection(std::string username);  	
	
	/// setupGame
   /// \pre    A connection with everyone present
   /// \post   all clients will be sent the server data
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void setupGame(int location);  
	
	/// isReady
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void isReady();  

	/// sendMyTurn
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual Connection::Shot sendMyTurn(Connection::Shot theShot);  
	
	/// waitForData
   /// \pre    A connection with everyone present and game is set up and locations are filled
   /// \post   The game will start
   /// \param  none
   /// \return none
   /// \throw  None
   virtual Connection::Shot waitForData();  
	
// ACCESS and MUTATE
	
// INQUIRY
	
// ACCESS and MUTATE
	
// INQUIRY
	
// MEMBER VARIABLES
private:

	std::vector<Socket *> mConnections;
	int mNumOfPlayers;
	int mCurrentTurn;
	

}; // end of class Card

#endif

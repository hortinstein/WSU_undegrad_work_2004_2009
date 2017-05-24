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
	
	/// changestate
   /// \pre    A connection with everyone present
   /// \post   it will ping every client and get information
   /// \param  none
   /// \return none
   /// \throw  None
   virtual void changestate(std::string process_check) = 0;  
	
	/// switchColor
   /// \pre    the connection is set
   /// \post   a color specified is switched
   /// \param  none
   /// \return none
   /// \throw  None
   void switchColor(std::string color);  
// ACCESS and MUTATE
	
// INQUIRY

	/// red
   /// \pre    the connection is set
   /// \post   none
   /// \param  none
   /// \return a bool if it is on or not
   /// \throw  None
   bool red();  
	
	/// blue
   /// \pre    the connection is set
   /// \post   none
   /// \param  none
   /// \return a bool if it is on or not
   /// \throw  None
   bool blue();  
	
	/// green
   /// \pre    the connection is set
   /// \post   none
   /// \param  none
   /// \return a bool if it is on or not
   /// \throw  None
   bool green();  
	
	/// yello
   /// \pre    the connection is set
   /// \post   none
   /// \param  none
   /// \return a bool if it is on or not
   /// \throw  None
   bool yellow();  
	
	
// MEMBER VARIABLES
protected:
	//the bools for each color
	bool mRed;
	bool mBlue;
	bool mGreen;
	bool mYellow;
	
	std::string mUserName;
private:	

}; // end of class Card

#endif

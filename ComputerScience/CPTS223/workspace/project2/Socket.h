#ifndef SOCKET_H
#define SOCKET_H
///////////////////////////////////////////////////////////////////////////////
/// \class        Socket
/// \author       Chris Mallery
/// \date         22 March 2006
/// \brief        Provides simple point-to-point communication over TCP/IP.
///
/// Use an instance of this class to set up a communication link with
/// a nother program over TCP/IP. 
/// 
/// This class requires the FLTK library, because it supports a 
/// blocking receive that keeps FLTK applications alive by calling
/// Fl::check repeatedly, so that the GUI won't freeze while the
/// Socket is waiting to receive a message. 
///
/// REVISION HISTORY:
///
/// 22 March   creation and uglification by Mallery
/// 24 March   documentation by Fitz
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//
#include <string>
#include <deque>
#include <arpa/inet.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

// CONSTANTS
//

class Socket
{
public:

// LIFECYCLE

   /// Default constructor.
   /// Construct a new Socket that is not connected to anything.
   Socket( void );
   
   /// Destructor.
   /// Clean up by disconnecting this socket from anything 
   /// it might be connected to.
   ~Socket( void );
   
// OPERATIONS 
   
   /// Start up a server listening on the specified port for 
   /// a client to connect. Returns only after a client 
   /// has connected. Only a server should call this.
   ///
   /// This function does not return until a connection is
   /// made, but it does call Fl::check so that FLTK apps
   /// stay active (including callbacks) and do not freeze up
   /// while awaiting the connection. 
   ///
   /// \param portNumber the number of the port over which
   ///        to communicate, try something bigger than 1024
   ///        and smaller than 9999.  
   /// \throw std::runtime_error if the port cannot be used.
   void listen( unsigned int portNumber );
   
   /// Connect to a server at the specified IP address 
   /// (use 127.0.0.1 for the if the server is on the
   /// same computer as the client) that is listening
   /// on the specified port. Returns after a connection
   /// has been made to the server. Only a client should
   /// call this.
   ///
   /// This function does not wait around for a connection.
   /// If a server is available, a connection is made 
   /// immediately. If not, an exception is thrown.
   ///
   /// \param ipAddress the IP address of the computer on
   ///        which the server is running, use 127.0.0.1
   ///        for the local host
   /// \param portNumber the number of the port over which
   ///        to communicate, try something bigger than 1024
   ///        and smaller than 9999.  
   /// \throw std::runtime_error if a socket cannot be created
   ///        or if no server is listening on the specified
   ///        port at the specified IP address
   void connect( std::string ipAddress, unsigned int portNumber );
   
   /// Send a message over an established connection (either
   /// from server to client, or from client to server). 
   /// There must be a connection established before 
   /// anything can be sent.
   /// 
   /// \pre   message must be shorter than 1024 characters
   /// \pre   the Socket must be connected (using listen/connect)
   /// \param message the message to send, formated as a
   ///        sequence of characters that do not include '\0'.
   /// \throw std::domain_error if the message is longer than
   ///        1023 characters
   /// \throw std::runtime_error if the message cannot be 
   ///        sent (due to some network problem, or because
   ///        there is no connection)
   void send( std::string message );
   
   /// Wait for a message to arrive over an established
   /// connection (from server to client, or from client 
   /// to server). Returns only after a message has been 
   /// received. If keepFltkAlive is true (the default)
   /// then call Fl::check while waiting for the message
   /// to arrive, so that FLTK apps stay active (including 
   /// callbacks) and do not freeze up while waiting. 
   ///
   /// \pre    the Socket must be connected (using listen/connect)
   /// \param  keepFltkAlive if true (the default), FLTK apps
   ///         are kept alive while waiting for a message by
   ///         calls to Fl::check.
   /// \return a string storing the message received
   std::string recv( bool keepFltkAlive = true );
   
// MEMBER VARIABLES

private:

   int mServSock;
   int mClntSock;
   struct sockaddr_in mServAddr;
   struct sockaddr_in mClntAddr;

   std::deque<std::string> mRcvdMessages;
   bool mLastIsComplete;

// BUSTED
   
   ///   Do not try to use copy and assignment, these operation 
   ///   don't work well with sockets.
   Socket(const Socket& rhs);
   Socket& operator=(const Socket& rhs);

};

#endif

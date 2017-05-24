#ifndef CONNECTIONWINDOW_H//guard conditional compilation
#define CONNECTIONWINDOW_H//guard conditional compilation

///////////////////////////////////////////////////////////////////////////////
/// \class        ConnectionWindow
/// \author       Alex Hortin
/// \date         2/28/06  
/// \brief			This is a window that tests the HandOfCards class
///
/// This Class is the window that you will see that contains all the work 
/// behind the program interface.  It will display graphics for hands, and 
/// pop up error messages when nessecary.
///
///       
/// REVISION HISTORY:
///
/// NONE
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//
#include <FL/Fl.H>//the FLTK source files
#include <FL/Fl_Window.H>//the FLTK source files
#include <FL/Fl_Button.H>//the FLTK source files
#include <FL/Fl_Input.H>//the FLTK source files
#include <FL/Fl_Output.H>//the FLTK source files
#include <FL/Fl_GIF_Image.h>//the FLTK gif class
#include <Fl/fl_ask.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/gl.h>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <GL/gl.h>
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Output.H>//the FLTK source files
#include <FL/Fl_Multiline_Output.H>
#include <string>//string.h include
#include <vector>//vector.h include
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

// LOCAL INCLUDES
//

#include "Connection.h"
#include "ClientConnection.h"
#include "ServerConnection.h"
// FORWARD REFERENCES
//

// CONSTANTS
//

class ConnectionWindow : public Fl_Window//inheritance for the window
{
   public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the MyWindow is created.
   /// \param  None
   /// \throw  None
   ConnectionWindow ();//the basic constructor used for testing

   /// Destructor.
   /// \pre    An instance of PlaybackWindow has been created.
   /// \post   The instance of PlaybackWindow is destroyed.
   ~ConnectionWindow();//the destructor
	
// OPERATORS

// OPERATIONS 

// ACCESS and MUTATE

// INQUIRY

	/// returnConnection
   /// \pre    A the connection is finised being created
   /// \post   the connection will be passed into the scorch window
	/// \param none
   /// \return a pointer to the connection
   /// \throw  None
	Connection* returnConnection(void);
	
// MEMBER VARIABLES

		Fl_Button*  cConnect;
		Fl_Input* cIP;
		Fl_Input* cPlayers;
		Fl_Input* cUserName;
		Fl_Round_Button* cServer;
		Fl_Round_Button* cClient;
		Connection* mConnection;
private:
// OPERATIONS

	/// draw
   /// \pre    A valid window
   /// \post   a window is added
	/// \param none
   /// \return none
   /// \throw  None
	void draw(void);
	
	/// handle
   /// \pre    a button is clicks
   /// \post   a card is added
   /// \param  the event number
   /// \return the event number
   /// \throw  None
	int handle(int event);
	

// ACCESS and MUTATE

	/// cb_server is the call that the program makes when the server button is pressed
	/// \pre   None
	/// \post  The button will be set, label of input changed, and other button turned off if its on
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void cb_server(Fl_Widget*, void* v);//the button for tell me
   
	/// cb_server_i is the call that the program makes when the server button is pressed
	/// \pre   None
	/// \post  The button will be set, label of input changed, and other button turned off if its on
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   void cb_server_i();//the button for tell me
	
	/// cb_client is the call that the program makes when the client button is pressed
	/// \pre   None
	/// \post   The button will be set, label of input changed, and other button turned off if its on
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void cb_client(Fl_Widget*, void* v);//the button for tell me
   
	/// cb_client_i is the call that the program makes when the client button is pressed
	/// \pre   None
	/// \post  The button will be set, label of input changed, and other button turned off if its on
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   void cb_client_i();//the button for tell me
   
	/// cb_connect is the call that the program makes when the connect button is pressed
	/// \pre   None
	/// \post  A polymorphic connection is assgined to mConnection
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void cb_connect(Fl_Widget*, void* v);
   
	/// cb_connect_i is the call that the program makes when the connect button is pressed
	/// \pre   None
	/// \post  A polymorphic connection is assgined to mConnection
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   void cb_connect_i();
	
// MEMBER VARIABLES

}; // end of class Name

// INLINE METHODS
//

#endif  // DATABASEWINDOW_H

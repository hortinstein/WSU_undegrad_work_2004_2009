#ifndef SQUARESWIN_H//guard conditional compilation
#define SQUARESWIN_H//guard conditional compilation

///////////////////////////////////////////////////////////////////////////////
/// \class        SquaresWin
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
#include "Connection.h"//this file!!!11!
// FORWARD REFERENCES
//

// CONSTANTS
//

class SquaresWin : public Fl_Double_Window//inheritance for the window
{
   public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the MyWindow is created.
   /// \param  None
   /// \throw  None
   SquaresWin (Connection * connections);//the basic constructor used for testing

   /// Destructor.
   /// \pre    An instance of PlaybackWindow has been created.
   /// \post   The instance of PlaybackWindow is destroyed.
   ~SquaresWin();//the destructor
	
// OPERATORS

// OPERATIONS 

// ACCESS and MUTATE

// INQUIRY

// MEMBER VARIABLES
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
	
	/// make_this
   /// \pre    a button is clicks
   /// \post   a card is added
   /// \param  the event number
   /// \return the event number
   /// \throw  None
	static void make_this(SquaresWin * w, std::string process);


// ACCESS and MUTATE

   
	/// update is the call that the program makes when the DrawT errain button
	/// is pressed.
	/// \pre   None
	/// \post  The terrain is mapped to the box
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void update( void* v);//the button for tell me

	
// MEMBER VARIABLES
	
	std::string mProcess;
	 
}; // end of class Name

// INLINE METHODS
//

#endif  // DATABASEWINDOW_H

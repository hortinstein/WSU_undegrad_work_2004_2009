#ifndef MYWINDOW_H//guard conditional compilation
#define MYWINDOW_H//guard conditional compilation

///////////////////////////////////////////////////////////////////////////////
/// \class        DatabaseWindow
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
#include <FL/Fl_Output.H>//the FLTK source files
#include <FL/Fl_Multiline_Output.H>
#include <string>//string.h include
#include <vector>//vector.h include
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

// LOCAL INCLUDES
//
#include "Whist.h"//the sample sound player
#include "MyWindow.h"//this file!!!11!
// FORWARD REFERENCES
//

// CONSTANTS
//

class MyWindow : public Fl_Window//inheritance for the window
{
   public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the MyWindow is created.
   /// \param  None
   /// \throw  None
   MyWindow ();//the basic constructor used for testing

   /// Destructor.
   /// \pre    An instance of PlaybackWindow has been created.
   /// \post   The instance of PlaybackWindow is destroyed.
   ~MyWindow();//the destructor

// OPERATORS

// OPERATIONS 
   
// ACCESS and MUTATE

// INQUIRY

// MEMBER VARIABLES

		Fl_Input* mSuit;
		Fl_Input* mPip;
		Fl_Button* mPlayCard;
		Fl_Multiline_Output* mGameInfo;//the info panel where the games last trick/scores/ and tricks won are stored

private:
// OPERATIONS

	/// draw
   /// \pre    A valid Card
   /// \post   a card is added
   /// \param  Card the card to be added
   /// \return none
   /// \throw  None
	void draw(void);

// ACCESS and MUTATE

   
	/// cb_playCard is the call that the program makes when the Play Suit button
	/// is pressed.  It makes sure that a card can be played or it will throw an error
	/// \pre   a card must be in hand
	/// \post  a card will be removed or error window thrown
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void cb_PlayCard(Fl_Widget*, void* v);//the button for tell me
   
	/// cb_playCard is the call that the program makes when the Play Suit button
	/// is pressed.  It makes sure that a card can be played or it will throw an error
	/// \pre   a card must be in hand
	/// \post  a card will be removed or error window thrown
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   void cb_PlayCard_i();//the call that the button makes
      
	/// int_to_string
	/// \pre  None
	/// \post  None
	/// \param  an integer
	/// \return a string
	/// \throw  n/a
   std::string int_to_string(int i);
	
// MEMBER VARIABLES
   Whist mGame;
   
}; // end of class Name

// INLINE METHODS
//

#endif  // DATABASEWINDOW_H

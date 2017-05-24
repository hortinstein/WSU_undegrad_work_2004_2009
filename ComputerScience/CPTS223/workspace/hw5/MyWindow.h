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
#include <string>//string.h include
#include <vector>//vector.h include
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

// LOCAL INCLUDES
//
#include "HandOfCards.h"//the sample sound player
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
      Fl_Input* mSuit;//the suit input
    	Fl_Input* mPip;
		Fl_Button* mAddCard;
		Fl_Input* mPlaySuit_Suit;
		Fl_Button* mPlaySuit;

private:
// OPERATIONS

	/// addCard
   /// \pre    A valid Card
   /// \post   a card is added
   /// \param  Card the card to be added
   /// \return none
   /// \throw  None
	void draw(void);

// ACCESS and MUTATE
      
   /// cb_addCard is the call that the program makes when the Add Card button 
   /// is pressed.  It makes sure that the suit and Pip are valid and than adds the card
   /// \pre   the pre conditions is there must be a valid suit and card.
   /// \post  a card will be added or error window thrown
   /// \param  a widget pointer
   /// \return void
   /// \throw  n/a
   static void cb_addCard(Fl_Widget*, void* v);//the button for tell me
   
   /// cb_addCard is the call that the program makes when the Add Card button 
   /// is pressed.  It makes sure that the suit and Pip are valid and than adds the card
   /// \pre   the pre conditions is there must be a valid suit and card.
   /// \post  a card will be added or error window thrown
   /// \param  a widget pointer
   /// \return void
   /// \throw  n/a
   void cb_addCard_i();//the call that the button makes
   
	/// cb_playSuit is the call that the program makes when the Play Suit button
	/// is pressed.  It makes sure that a card can be played or it will throw an error
	/// \pre   a card must be in hand
	/// \post  a card will be removed or error window thrown
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void cb_playSuit(Fl_Widget*, void* v);//the button for tell me
   
	/// cb_playSuit is the call that the program makes when the Play Suit button
	/// is pressed.  It makes sure that a card can be played or it will throw an error
	/// \pre   a card must be in hand
	/// \post  a card will be removed or error window thrown
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   void cb_playSuit_i();//the call that the button makes
      

// MEMBER VARIABLES
   HandOfCards mHand;
   
}; // end of class Name

// INLINE METHODS
//

#endif  // DATABASEWINDOW_H

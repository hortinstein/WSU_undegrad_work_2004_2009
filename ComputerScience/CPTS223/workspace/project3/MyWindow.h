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
#include "Scorch.h"//the sample sound player
#include "MyWindow.h"//this file!!!11!
#include "ConnectionWindow.h"
#include "Connection.h"
#include "ClientConnection.h"
#include "ServerConnection.h"
// FORWARD REFERENCES
//

// CONSTANTS
//

class MyWindow : public Fl_Double_Window//inheritance for the window
{
   public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the MyWindow is created.
   /// \param  a connection and a user name
   /// \throw  None
   MyWindow (Connection* connections,std::string username);//the basic constructor used for testing

   /// Destructor.
   /// \pre    An instance of PlaybackWindow has been created.
   /// \post   The instance of PlaybackWindow is destroyed.
   ~MyWindow();//the destructor
	
// OPERATORS

// OPERATIONS 

// ACCESS and MUTATE

// INQUIRY

// MEMBER VARIABLES

		//Fl_Input* mAngle;
		//Fl_Input* mPower;
		Fl_Button* mFire;
		Fl_Button* mStartGame;
		//Fl_Button* mPlayCard;
		Fl_Button* mDrawTerrain;
		Fl_Multiline_Output* mGameInfo;//the info panel where the games last trick/scores/ and tricks won are stored
		Fl_Value_Slider* mPower;
		Fl_Dial* mDial;
		//Fl_Value_Slider* mAngle;
		double mAngle;
		Fl_Value_Slider* mPayload;
		Fl_Overlay_Window* mShots_disp;
		
private:
// OPERATIONS

	/// draw draws all of the board including terrain and shots
   /// \pre    A valid window
   /// \post   a window is added
	/// \param none
   /// \return none
   /// \throw  None
	void draw(void);
	
	/// handle handles my mousewheel events for anglechange and placement and movement
   /// \pre    a button is clicks
   /// \post   a card is added
   /// \param  the event number
   /// \return the event number
   /// \throw  None
	int handle(int event);
	
	/// cycleTurn wait for and registers firing
   /// \pre    it is the players turn
   /// \post   a card is added
   /// \param  the event number
   /// \return the event number
   /// \throw  None
	void cycleTurn();

// ACCESS and MUTATE

   
	/// cb_DrawTerrain is the call that the program makes when the DrawT errain button
	/// is pressed.
	/// \pre   None
	/// \post  The terrain is mapped to the box
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void cb_DrawTerrain(Fl_Widget*, void* v);//the button for tell me
   
	/// cb_DrawTerrain is the call that the program makes when the Draw Terrain button
	/// is pressed.
	/// \pre   None
	/// \post  The terrain is mapped to the box
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   void cb_DrawTerrain_i();//the call that the button makes
   
	/// cb_fire is the call that the program makes when the DrawT errain button
	/// is pressed.
	/// \pre   None
	/// \post  The terrain is mapped to the box
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void cb_fire(Fl_Widget*, void* v);//the button for tell me
   
	/// cb_fire_i is the call that the program makes when the Draw Terrain button
	/// is pressed.
	/// \pre   None
	/// \post  The terrain is mapped to the box
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   void cb_fire_i();//the call that the button makes
	
	/// cb_startgame is the call that the program makes when the startgame button
	/// is pressed.
	/// \pre   None
	/// \post  the game starts
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   static void cb_startgame(Fl_Widget*, void* v);
   
	/// cb_fire_i is the call that the program makes when the cb_startgame button
	/// is pressed.
	/// \pre   None
	/// \post  the game starts
	/// \param  a widget pointer
	/// \return void
	/// \throw  n/a
   void cb_startgame_i();

	
	
// MEMBER VARIABLES
	std::string mUserName;
   Scorch mGame;
	Connection::Shot mTempShot;
   bool mShotFired;
	int mMyTurnNumber;
	bool mTerrainDraw;
	bool mPlacement;
	bool mGameStarted;
	Connection* mConnection;
	std::vector<Scorch::x_y> line_shot;
}; // end of class Name

// INLINE METHODS
//

#endif  // DATABASEWINDOW_H

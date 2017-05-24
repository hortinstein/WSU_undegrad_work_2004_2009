#ifndef PLAYBACKWINDOW_H//guard conditional compilation
#define PLAYBACKWINDOW_H//guard conditional compilation

///////////////////////////////////////////////////////////////////////////////
/// \class        PlaybackWindow
/// \author       Alex Hortin
/// \date         8/31/05  
/// \brief        This class creates a playback window that is inherits 
///               from the FLTK class and uses library functions from 
///               sampleplayer
///
/// This class is meant to generate a simple window using FLTK and play a 
/// sound file.  There are two buttons on the window, a play and a quit button.
/// When pressed the play button's text changes to stop and back to play when
/// it is pressed again.  The class must be called with a string, which is the
/// path and file name to the sample sounds that is being played.
///
/// \invariant   None
///       
/// REVISION HISTORY:
///
/// 9/12/05       Coding standard quality commenting and naming, with addition
///               of required features.
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//
#include <FL/Fl.H>//the FLTK source files
#include <FL/Fl_Window.H>//the FLTK source files
#include <FL/Fl_Button.H>//the FLTK source files
#include <FL/Fl_Input.H>//the FLTK source files
#include <FL/Fl_Output.H>//the FLTK source files
#include <string>//string.h include
#include <vector>//vector.h include
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <stdexcept>

// LOCAL INCLUDES
//
#include "SamplePlayer.h"//the sample sound player

// FORWARD REFERENCES
//
using std::string;//includes the string command
using std::vector;
// CONSTANTS
//

class PlaybackWindow : public Fl_Window//inheritance for the window
{
   public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the playback window is created.
   /// \param  A string containing the name for a file.
   /// \throw  None
   PlaybackWindow(string file_name);//the basic constructor used for testing

   /// Copy Constructor.
   /// \pre    An instance of PlaybackWindow needs to be present.
   /// \post   Two instances of the same window will exist.
   /// \param   PlaybackWindow is the PlaybackWindow to copy from.
   /// \throw  None
   PlaybackWindow( const PlaybackWindow &PlaybackWindow );//the copy constructor

   /// Destructor.
   /// \pre    An instance of PlaybackWindow has been created.
   /// \post   The instance of PlaybackWindow is destroyed.
   ~PlaybackWindow();//the destructor

// OPERATORS

// OPERATIONS 

   /// cb_play_or_stop
   /// \pre    The Play or Stop button must be pressed.
   /// \post   Play is changed to stop or stop is changed to play and the sound
   ///         plays.
   /// \param  Fl_Widget is the button that must be pressed.
   /// \return None
   /// \throw  None
   static void cb_play_or_stop(Fl_Widget*, void*);//the button for play or stop
   /// cb_play_or_stop_i
   /// \pre    cb_play_or_stop must have been called by the button press.
   /// \post   Play is changed to stop or stop is changed to play, and the bool 
   ///         value is_playing is changed as well.
   /// \param  None
   /// \return None
   /// \throw  None
   inline void cb_play_or_stop_i();//the call that the button makes to play or stop
   /// cb_quit
   /// \pre    The quit button must have been presses.
   /// \post   The cb_quit_i function is called to terminate the program.
   /// \param  Fl_Widget is the button that must be pressed.
   /// \return None
   /// \throw  None
   static void cb_quit(Fl_Widget*, void*);//the button to quit
   /// cb_quit_i
   /// \pre    cb_quit must have been called by the button press.
   /// \post   The program terminates
   /// \param  None
   /// \return None
   /// \throw  None
   inline void cb_quit_i();//the fuction that quits
 
// ACCESS and MUTATE

// INQUIRY

// MEMBER VARIABLES
   Fl_Button* play_or_stop;//the pointer that contains the dual button fo play or stop
   Fl_Button* quit;//the pointer that contains the button for "quit"
   SamplePlayer *mPlayer;//the instance the player ready for initialization in our constructor

private:
// MEMBER VARIABLES
   bool mIs_playing;//stores a bool value to see whether or not a sound is playing...most likely a temp variable 
   vector <float> mReadSamples;//the vector that stores all of the data for our sound sample 
   int mFrames;//stores number of frames
   
}; // end of class Name

// INLINE METHODS
//

#endif  // PLAYBACKWINDOW_H

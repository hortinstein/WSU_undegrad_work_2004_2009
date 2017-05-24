
#ifndef RIDDLEWINDOW_H//guard conditional compilation
#define RIDDLEWINDOW_H//guard conditional compilation
///////////////////////////////////////////////////////////////////////////////
/// \class        RiddleWindow
/// \author       Alex Hortin
/// \date         8/30/2005
/// \brief        This class is meant to make a window that contains a riddle
///               that can be of any size, and the window will resize based on
///               how long the riddle is.
///
/// This class inherits from the FLTK toolset and uses widgets and other members
///  of that toolset to accomplish the making of the window.  
///
/// \invariant   n/a
///       
/// REVISION HISTORY:
/// 
/// 9/06/05       Changed commenting to fit the standard and added in automatic
///               resizing.
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
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
using std::string;//includes the string command

// CONSTANTS
//


#include <FL/Fl.H>//the FLTK source files
#include <FL/Fl_Window.H>//the FLTK source files
#include <FL/Fl_Button.H>//the FLTK source files
#include <FL/Fl_Input.H>//the FLTK source files
#include <FL/Fl_Output.H>//the FLTK source files
#include <string>//string.h include
using std::string;//includes the string command



class RiddleWindow : public Fl_Window//inheritance for the window
{
	public:
	  // LIFECYCLE


      ///   Default Constructor.
      /// \pre    This is a default constructor so it must be passed two strings
      ///          and called to construct something. 
      /// \post   There are no post conditions
      /// \param  2 strings, each containing part of a riddle
      /// \return It returns nothing
      /// \throw  n/a
		RiddleWindow(string w, string h);//the basic constructor used for testing
      
		///   Copy Constructor.
		/// \pre    This is a Copy constructor so it must be passed a reference
		///          and called to construct the copy. 
		/// \post   There are no post conditions
		/// \param  The parameters are the refence to something to copy it.
		/// \return It returns nothing
		/// \throw  n/a
		RiddleWindow( const RiddleWindow& RiddleWindow );//the copy constructor
      
      ///   Destructor.
		/// \pre    it must be called to destroy soemthing
		/// \post   There are no post conditions
		/// \param  The parameters are the refence to something to copy it.
		/// \return It returns nothing
		/// \throw  n/a
		~RiddleWindow();//the destructor
      
      // member public variables used in construction of the window
		Fl_Button* tell_me;//the pointer that contains the button for "tell me"
		Fl_Button* quit;//the pointer that contains the button for "quit"
		Fl_Input* rid;//stores the riddle button
		Fl_Output* ans;//stores the ans button
	//private variables and methods
	private:
      /// cb_tell_me is the call that the program makes when the tell me button is 
		///  pressed.  It than shows the contents.
		/// \pre   the pre conditions for this is the button being pressed  
		/// \post  there are no post conditions
		/// \param  a widget pointer
		/// \return void
		/// \throw  n/a
		static void cb_tell_me(Fl_Widget*, void*);//the button for tell me
      /// cb_tell_me_i is the call that the program makes when the tell me button is 
		///  pressed.  This part shows the contents
		/// \pre   the pre conditions for this is the button being pressed  
		/// \post  there are no post conditions
		/// \param  a widget pointer
		/// \return void (shows the contents in the window
		/// \throw  n/a
		inline void cb_tell_me_i();//the call that the button makes
      /// cb_quit is the call that the program makes when the quit button is pressed.
      /// \pre   the pre conditions for this is the button being pressed  
      /// \post  there are no post conditions
      /// \param  a widget pointer
      /// \return void
      /// \throw  n/a	
		static void cb_quit(Fl_Widget*, void*);//the buton to quit
      /// cb_quit_i is the call that the cb_quit makes so that information hiding can
		///  can be kept in tact
		/// \pre   the pre conditions for this is the button being pressed  
		/// \post  there are no post conditions
		/// \param  none
		/// \return void
		/// \throw  n/a
		inline void cb_quit_i();//the fuction that quits
 
		string answer; //the string that stores the answer
}; // end of class RiddleWindow

#endif//end of the guard code

#ifndef DATABASEWINDOW_H//guard conditional compilation
#define DATABASEWINDOW_H//guard conditional compilation

///////////////////////////////////////////////////////////////////////////////
/// \class        DatabaseWindow
/// \author       Alex Hortin
/// \date         10/25/05  
/// \brief        This class creates a Database window that inherits 
///               from the FLTK class and uses the templated Tree class.
///
/// This Class is the window that you will see that contains all the work 
/// behind the program interface.  It will create the file structure and put it
/// all into a tree. 
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
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Hold_Browser.H>
#include <string>//string.h include
#include <vector>//vector.h include
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

// LOCAL INCLUDES
//
#include "Tree.h"//the sample sound player
#include "DatabaseWindow.h"//this file!!!11!
// FORWARD REFERENCES
//

// CONSTANTS
//

class DatabaseWindow : public Fl_Window//inheritance for the window
{
   public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the playback window is created.
   /// \param  A string containing the name for a file.
   /// \throw  None
   DatabaseWindow (char* file_name);//the basic constructor used for testing

   /// Destructor.
   /// \pre    An instance of PlaybackWindow has been created.
   /// \post   The instance of PlaybackWindow is destroyed.
   ~DatabaseWindow();//the destructor

// OPERATORS

// OPERATIONS 
  
   /// convertMonth
   /// \pre    Their must be a string given as an argument.
   /// \post   A file structure contained in a tree is created and stored in this class.
   /// \param  the string to convert
   /// \return None
   /// \throw  None
   std::string convertMonth ( std::string monthconvert );
   
   /// convertDate
   /// \pre    Their must be a string given as an argument.
   /// \post   A file structure contained in a tree is created and stored in this class.
   /// \param  the string to convert
   /// \return None
   /// \throw  None
   std::string convertDate ( std::string dateconvert );

   /// buildDatabase
   /// \pre    Their must be a directory given as a command line argument.
   /// \post   A file structure contained in a tree is created and stored in this class.
   /// \param  None
   /// \return None
   /// \throw  None
   void buildDatabase ( std::string pathName );
   
   /// getMonth
   /// \pre    Their must be a string given as an argument.
   /// \post   A file structure contained in a tree is created and stored in this class.
   /// \param  the string to convert
   /// \return None
   /// \throw  None
   cPosition<std::string> getMonth ( std::string month );
   
   /// getDate
   /// \pre    The position must have been returned 
   /// \post   A file structure contained in a tree is created and stored in this class.
   /// \param  the string to convert
   /// \return None
   /// \throw  None
   cPosition<std::string> getDate (cPosition<std::string> Month, std::string date );
   
   /// searchRecurse
   /// \pre    The position must have been returned 
   /// \post   A file structure contained in a tree is created and stored in this class.
   /// \param  the string to convert
   /// \return None
   /// \throw  None
   void searchRecurse (cPosition<std::string> Search );
   
// ACCESS and MUTATE

// INQUIRY

// MEMBER VARIABLES
      Fl_Hold_Browser* mResults;//the results of the search aka the files
      Fl_Input* mSearch;//the search button
      Fl_Multiline_Output* mFileInfo;//the file info panel
      Fl_Button* mSearchButton;

private:
// ACCESS and MUTATE
      
   /// cb_search is the call that the program makes when the search button 
   /// is pressed.  It than calls a search of the tree for results.
   /// \pre   the pre conditions for this is the button being pressed and a tree existing to search through 
   /// \post  the mResults browser will be modified
   /// \param  a widget pointer
   /// \return void
   /// \throw  n/a
   static void cb_search(Fl_Widget*, void*);//the button for tell me
   
   /// cb_search is the call that the program makes when the search button 
   /// is pressed.  It than calls a search of the tree for results.
   /// \pre   the pre conditions for this is the button being pressed and a tree existing to search through 
   /// \post  the mResults browser will be modified
   /// \param  a widget pointer
   /// \return void
   /// \throw  n/a
   inline void cb_search_i();//the call that the button makes
   
   /// cb_browser is the call that the program makes when the search button 
   /// is pressed.  It than calls a search of the tree for results.
   /// \pre   the pre conditions for this is the button being pressed and a tree existing to search through 
   /// \post  the mResults browser will be modified
   /// \param  a widget pointer
   /// \return void
   /// \throw  n/a
   static void cb_browser(Fl_Widget*, void*);//the button for tell me
   
   /// cb_browser is the call that the program makes when the search button 
   /// is pressed.  It than calls a search of the tree for results.
   /// \pre   the pre conditions for this is the button being pressed and a tree existing to search through 
   /// \post  the mResults browser will be modified
   /// \param  a widget pointer
   /// \return void
   /// \throw  n/a
   inline void cb_browser_i();//the call that the button makes
      

// MEMBER VARIABLES
   std::string mDirectoryName;
   std::vector<std::string> hold_browser_ish;
   Tree<std::string>*  mDatabase;
   
}; // end of class Name

// INLINE METHODS
//

#endif  // DATABASEWINDOW_H

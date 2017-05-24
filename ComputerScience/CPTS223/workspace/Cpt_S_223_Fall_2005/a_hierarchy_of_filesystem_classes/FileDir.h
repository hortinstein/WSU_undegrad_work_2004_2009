#ifndef FILEDIR_H    // include guard
#define FILEDIR_H

///////////////////////////////////////////////////////////////////////////////
/// \class        FileDir
/// \author       Alex Hortin
/// \date         10/13/05
/// \brief        This is the directory file type
///
/// This is the class that inherits from file.  It is derived from file, and 
/// redefines some of the key function using the 1337 dark art of polymorphism.  
///       
/// REVISION HISTORY:
///
/// NONE
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//
#include <vector>
// LOCAL INCLUDES
//
#include "File.h"
// FORWARD REFERENCES
//

// CONSTANTS
//

class FileDir  : public File
{
public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    Function must be called.
   /// \post   A default file is constructed
   /// \throw  NONE
   FileDir(std::string path);

   /// Destructor.
   /// \pre    There must be something to mercelessly rape pillage and destroy
   /// \post   Poof! that bitch is gone!
   ~FileDir( void );

// OPERATORS

   /// Assignment operator.
   /// \pre    The fuction is called by trying to assign
   /// \post   NONE
   /// \param  rhs is the object to assign from.
   /// \return A reference to this Name.
   /// \throw  NONE
   FileDir& operator=( const FileDir & rhs );  
   
// OPERATIONS 

// ACCESS and MUTATE

// INQUIRY
   
   /// preview
   /// \pre    The class has been created
   /// \post   A string is returned with the name in it
   /// \param  None
   /// \return A string
   /// \throw  NONE
   virtual Fl_Window* preview(void);
   
   /// cb_preview_browser is the call that the program makes when the search button 
   /// is pressed.  It than calls a search of the tree for results.
   /// \pre   the pre conditions for this is the button being pressed and a tree existing to search through 
   /// \post  the mResults browser will be modified
   /// \param  a widget pointer
   /// \return void
   /// \throw  n/a
   static void cb_preview_browser(Fl_Widget*, void*);//the button for tell me
   
   /// cb_preview_browser_i is the call that the program makes when the search button 
   /// is pressed.  It than calls a search of the tree for results.
   /// \pre   the pre conditions for this is the button being pressed and a tree existing to search through 
   /// \post  the mResults browser will be modified
   /// \param  a widget pointer
   /// \return void
   /// \throw  n/a
   inline void cb_preview_browser_i();//the button for tell me

// MEMBER VARIABLES

   Fl_Window * win ;
   Fl_Hold_Browser * box ;
   
protected:

   std::vector<std::string> mNames;
   std::string mContents;
   std::string mPath;
private:

   
}; // end of class Name

// INLINE METHODS
//
   
 
#endif  // FILEDIR_H

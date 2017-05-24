#ifndef FILE_H    // include guard
#define FILE_H

///////////////////////////////////////////////////////////////////////////////
/// \class        File
/// \author       Alex Hortin
/// \date         10/13/05
/// \brief        This is the base class for all of the file types
///
/// This is the class that makes all of the files work, due to inheritance and
/// polymorphism.  
///       
/// REVISION HISTORY:
///
/// NONE
///            
///////////////////////////////////////////////////////////////////////////////
#include "File.h"
// SYSTEM INCLUDES
//
#include <FL/Fl.H>//the FLTK source files
#include <FL/Fl_Window.H>//the FLTK source files
#include <FL/Fl_Button.H>//the FLTK source files
#include <FL/Fl_Input.H>//the FLTK source files
#include <FL/Fl_Output.H>//the FLTK source files
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Hold_Browser.H>
#include <Fl/Fl_JPEG_Image.H>
#include <Fl/Fl_Box.H>
#include <string>//string.h include
#include <vector>//vector.h include
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <iostream>
#include <sstream>

using std::ostringstream;

// LOCAL INCLUDES
//
#include "File.h"

// FORWARD REFERENCES
//

// CONSTANTS
//

class File 
{
public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    Function must be called.
   /// \post   A default file is constructed
   /// \throw  NONE
   File( void );

   /// Copy Constructor.
   /// \pre    A file must be there to copy
   /// \post   Two copies of the same file exist.
   /// \param  from is the Name to copy from.
   /// \throw  NONE
   File( const File & from );

   /// Destructor.
   /// \pre    There must be something to mercelessly rape pillage and destroy
   /// \post   Poof! that bitch is gone!
   virtual ~File( void );

// OPERATORS

// OPERATIONS 

   /// create
   /// \pre    NONE
   /// \post   A new instance of the concrete class is created
   /// \param  A path in the form of the string
   /// \return A pointer to a file
   /// \throw  An exception if the path does not exist
   static File * create( const std::string & path );

// ACCESS and MUTATE

// INQUIRY

   /// name
   /// \pre    The class has been created
   /// \post   A string is returned with the name in it
   /// \param  None
   /// \return A string containing name
   /// \throw  NONE
   std::string name(void);
   
   /// path
   /// \pre    The class has been created
   /// \post   A string is returned with the path in it
   /// \param  None
   /// \return A strings containing path
   /// \throw  NONE
   std::string path(void);
   
   /// infoString
   /// \pre    The class has been created
   /// \post   A string is returned with the name in it
   /// \param  None
   /// \return A string
   /// \throw  NONE
   std::string infoString(void) const ;
   
   /// preview
   /// \pre    The class has been created
   /// \post   A string is returned with the name in it
   /// \param  None
   /// \return A string
   /// \throw  NONE
   virtual Fl_Window* preview(void) = 0;

// MEMBER VARIABLES
   
protected:
   std::string mPath;//stores the path
   std::string mFileName;//stores the filename
   std::string mInfoString;//stores the information string


private:


}; // end of class Name

// INLINE METHODS
//
   
   /// Output operator.
   /// \pre    The fuction is called by trying to assign
   /// \post   NONE
   /// \param  rhs is the object to print from.
   /// \return A reference to this Name.
   /// \throw  NONE
   std::ostream& operator << (std::ostream& os, const File & rhs );  

#endif  // FILE_H

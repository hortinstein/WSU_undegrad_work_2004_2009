#ifndef FILEJPEG_H    // include guard
#define FILEJPEG_H

///////////////////////////////////////////////////////////////////////////////
/// \class        FileJpeg
/// \author       Alex Hortin
/// \date         10/13/05
/// \brief        This is the JPEG file type
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
//#include <string>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

// CONSTANTS
//

class FileJpeg: public File
{
public:

// LIFECYCLE

   /// Default constructor.
   /// \pre    Function must be called.
   /// \post   A default file is constructed
   /// \throw  NONE
   FileJpeg( std::string path);

   /// Destructor.
   /// \pre    There must be something to mercelessly rape pillage and destroy
   /// \post   Poof! that bitch is gone!
   ~FileJpeg( void );

// OPERATORS

   /// Assignment operator.
   /// \pre    The fuction is called by trying to assign
   /// \post   NONE
   /// \param  rhs is the object to assign from.
   /// \return A reference to this Name.
   /// \throw  NONE
   FileJpeg& operator=( const FileJpeg & rhs );  
   
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
   
protected:

// MEMBER VARIABLES

private:

   
}; // end of class Name

// INLINE METHODS
//

#endif  // FILEJPEG_H

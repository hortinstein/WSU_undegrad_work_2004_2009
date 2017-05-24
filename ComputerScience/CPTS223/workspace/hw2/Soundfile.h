#ifndef SOUNDFILE_H    // include guard
#define SOUNDFILE_H

///////////////////////////////////////////////////////////////////////////////
/// \class        SoundFile
/// \author       Alex Hortin 
/// \date         January 25 2006
/// \brief        A resizable random-access sequence.
///
/// A Vector stores elements in a resizable contiguous memory
/// block and provides efficient random access using the
/// subscript operator. 
///
/// REVISION HISTORY
///
/// 1/25/2006  Created the File Skeleton with comments and definitions
///
/// 1/30/2006  Continued to create my class
/// Plan for Assignment
///
/// 1. name, sampleRate, numChannels, numSampleFrames, read, playback, and both destructors
///   descriptions must all be written.
///    
/// 2. fill out a .h file in adherence with the form laid out by the comments.
/// 
/// 3. implement the functions of the class Soundfile
/// 
/// 4. test these implementations by playing a sound, and substituting my SoundFile, for Kelly's
/// 
/// 5. Have no problems to fix in 353 late monday night.
///    
/// 6. Get docked 20 percent by chris for a petty error (i have accepted this 
///   as a part of the assignment process.
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

#include <iostream>
#include <stdexcept>
#include <vector>
// LOCAL INCLUDES
//
#include "Soundfile.h"//the sample sound player

// FORWARD REFERENCES
//

// CONSTANTS
//

class Soundfile 
{
   public:
   

// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of the Soundfile class with a 44100 is created.
   /// \param  None
   /// \throw  None
   Soundfile( void );
   
   /// Filename constructor.
   /// \pre    None
   /// \post   An instance of the Vec class with a user specified number of
   ///         elements is created.
   /// \param  None
   /// \throw  None
   Soundfile(const std::string & filename);

// OPERATORS

// OPERATIONS 

   /// read
   /// \pre    A valid soundfile name can be 
   /// \post   The soundfile class will have stored all the files samples into
   ///         memory.
   /// \param  The name of the file
   /// \return None
   /// \throw  std::runtime_error if file cannot be read into memory
   void read(const std::string & filename);
   
  
// ACCESS and MUTATE
   
// INQUIRY
   
   /// name
   /// \pre    A soundfile must be given.
   /// \post   The name is returned
   /// \param  None
   /// \return A string containing the name
   /// \throw  None
   std::string name( void ) const;
   
   /// sampleRate
   /// \pre    A soundfile must be loaded into memory.
   /// \post   None
   /// \param  None
   /// \return a double containing the sample rate
   /// \throw  None
   double sampleRate( void ) const;

   /// numChannels
   /// \pre    A soundfile must be given.
   /// \post   None
   /// \param  None
   /// \return an unsigned int containing the number of channels
   /// \throw  None
   unsigned int numChannels( void ) const;   
   
   /// numSampleFrames
   /// \pre    A soundfile must be given.
   /// \post   The name is returned
   /// \param  None
   /// \return The number of sample frames
   /// \throw  None
   unsigned long numSampleFrames( void ) const;
   
   /// playback
   /// \pre    A soundfile must be given.
   /// \post   None
   /// \param  None
   /// \return None
   /// \throw  std::runtime_error if the sound cannot be played
   void playback( void ) const;
   
// MEMBER VARIABLES
private:
   /// Storage of the Sound Samples
   std::vector<double> mSamples;
   /// The name
   std::string mName;
   /// The sampleRate
   double mSampleRate;
   /// The numChannels
   unsigned int mNumChannels;
   /// The numSampleFrames
   unsigned long mNumSampleFrames;
   

}; // end of class Soundfile

#endif  // SOUNDFILE_H


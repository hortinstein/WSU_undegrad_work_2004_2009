#ifndef SOUNDFILE_H
#define SOUNDFILE_H
///////////////////////////////////////////////////////////////////////////////
/// \class        Soundfile
/// \author       Kelly Fitz
/// \date         10 January 2006
/// \brief        A structure for storing information about a sound file.
///
/// Soundfile stores information about a sound file, including the
/// sound samples themselves. Populate this structure using the
/// readSoundfile function. 
///       
/// REVISION HISTORY:
///
/// 10 January 2006  Creation. -kel
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//
#include <string>

struct Soundfile
{
   double * samples;               // an array of samples to play back
   unsigned long numSampleFrames;  // the number of sample frames stored in samples
   int sampleRate;                 // the sample rate in Hz at which the samples should
                                   // be played back (44100 is the CD rate)
   int numChannels;                // the number of channels of audio represented
                                   // by each sample frame (2 for stereo)
};

///////////////////////////////////////////////////////////////////////
/// readSoundfile
///
/// Populate a Soundfile struct with information from the specified 
/// sound file.
/// 
/// \param  filename the name of the sound file to read
/// \param  sfile the Soundfile structure to populate
/// \return he number of sample frames read, or 0 on error.
///////////////////////////////////////////////////////////////////////
unsigned long 
readSoundfile( const std::string & filename, Soundfile & sfile );

#endif /* not defined SOUNDFILE_H */

#ifndef PLAYSAMPS_H
#define PLAYSAMPS_H
///////////////////////////////////////////////////////////////////////////////
/// \author       Kelly Fitz
/// \date         10 January 2006
/// \brief        Function for playing samples on a Linux workstation.
///
/// Declaration of a function for playing sound
/// samples (stored as doubles) on a linux machine.
///
/// REVISION HISTORY:
///
/// 10 January 2006  Creation. -kel
///            
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
/// DEVICE
///
/// A string that specifies the name of the soundcard
/// device to which play_sample_frames will dump the sample
/// bytes. By default, this is defined to be "/dev/dsp".
/// Change it if you know that your machine uses some
/// other device for the soundcard.
///////////////////////////////////////////////////////////////////////
extern char * DEVICE;


///////////////////////////////////////////////////////////////////////
/// playSampleFrames
///
/// Stream a sequence of num_sample_frames frames of
/// num_channels samples of type double to the device
/// specified in DEVICE. Only works on little-endian 
/// *nix systems configured such that DEVICE is a 
/// compatible sound card. The maximum absolute value of
/// any sample should be less than 1.0, otherwise distortion
/// (clipping) will occur.
/// 
/// \param  samples an array of samples to play back
/// \param  numSampleFrames the number of sample frames stored in samples
/// \param  sampleRate the sample rate in Hz at which the samples should
///         be played back (44100 is the CD rate)
/// \param  numChannels the number of channels of audio represented
///         by each sample frame (2 for stereo)
/// \return the number of sample frames played, which should equal
///         num_sample_frames unless there is an error.
///////////////////////////////////////////////////////////////////////
unsigned long playSampleFrames( const double * samples, 
                                unsigned long numSampleFrames,
                                int sampleRate, int numChannels );

#endif   /* not defined PLAYSAMPS_H */

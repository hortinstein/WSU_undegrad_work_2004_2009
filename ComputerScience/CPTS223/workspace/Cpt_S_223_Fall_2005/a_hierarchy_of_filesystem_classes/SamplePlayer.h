#ifndef SAMPLEPLAYER_H  // include guard
#define SAMPLEPLAYER_H
///////////////////////////////////////////////////////////////////////////////
/// \class        SamplePlayer
/// \author       Kelly Fitz
/// \date         07 Mar 05
///
/// \brief        Manage sound sample playback using the PortAudio library.
///
///               SamplePlayer manages sound playback by establishing a
///               connection with the sound device and feeding samples
///               to it. Clients provide the samples by passing a pointer
///               to a buffer of samples, and the size (in frames) of
///               the buffer, to the startPlayback member. The samples
///               must be of type float. Playback of the specified samples
///               begins when startPlayback returns. Playback stops when
///               stopPlayback is called, or when the specified number
///               of sample frames have been played back.
///
///               This class can only be used in a program running with
///               access to the sound card! Most often, that means that
///               a program using this class cannot be launched over a 
///               network (including ssh). 
///
///               To compile this class, you may need to add something
///               to your compile flags so that the header portaudio.h
///               can be found (most often it is installed in 
///               /usr/local/include so you can add
///               -I/usr/local/include
///               to your CXXFLAGS.
///
///               To link a program using this class, you need to link 
///               the portaudio library, as well as the pthread library. 
///               You shouldbe able to add something like this to your
///               link command:
///               -L/usr/local/lib -lportaudio -lpthread
///
///       
/// REVISION HISTORY:
///
/// 07 Mar 05     Creation.
///
/// 09 Mar 05     Clean up and rename. -kel
///
/// 23 Mar 05     Modify to make copy and assignment work better. Now, 
///               streams are opened and closed on activation, instead 
///               of on construction. The old way prevented you from
///               ever having two players in existence at the same time.
///               Now, the only limitation is that only one may be 
///               active at a time. -kel
///
/// 30 Aug 05     Rewrote to simply play a buffer of floating point 
///               samples, no longer a base class. Renamed to SamplePlayer
///               from SoundPlayer. -kel      
///////////////////////////////////////////////////////////////////////////////

#include <portaudio.h> 

class SamplePlayer 
{

public:

// LIFECYCLE

   /// Initialize a new instance with the specified
   /// sample rate (in Hz) and number of channels
   /// of audio.
   ///
   /// \param  rate is the sample rate in Hz
   /// \param  nchans is the number of channels of audio
   SamplePlayer( double rate, unsigned int nchans );

   /// Initialize a new instance that has the same
   /// sample rate and number of channels as another
   /// instance.
   ///
   /// The audio stream is not copied, only the sample 
   /// rate and number of channels.
   ///
   /// \param  rhs is the SamplePlayer to copy from.
   SamplePlayer( const SamplePlayer & rhs );

   /// Deactivate and close the audio stream.
   ~SamplePlayer( void );

// OPERATORS

   /// Make this instance a copy of another instance.
   /// The audio stream is not copied, only the sample 
   /// rate and number of channels.
   ///  
   /// \param  rhs is the SamplePlayer to copy from.
   /// \return a reference to this SamplePlayer.
   SamplePlayer & operator=( const SamplePlayer & rhs );  

// OPERATIONS 

   /// Start playing samples from the specified buffer
   /// of floats. 
   /// 
   /// \param  buffer is the address of the first sample 
   ///         to playback
   /// \param  howMany is the number of sample frames to
   ///         stereo sample frames are stored in 
   ///         the buffer, and should be played back.
   void startPlayback( const float * buffer, unsigned int howMany );

   /// If a sound is playing, stop playback. Otherwise
   /// do nothing.
   void stopPlayback( void );

   
   /// Sleep for the specified number of milliseconds,
   /// then return, useful for busy wait loops.
   ///
   /// \param  sleepTimeMs is the (approximate) number of 
   ///         milliseconds to wait.
   void wait( int sleepTimeMs ) const;
  
// ACCESS and MUTATE

   /// getNumChannels
   ///
   /// \return the number of audio channels (samples per frame),
   ///         1 for mono, 2 for stereo, etc.
   unsigned int getNumChannels( void ) const;
   
   /// getSampleRate
   ///
   /// \return the playback sample rate in sample frames per second (Hz). 
   double getSampleRate( void ) const;


// INQUIRY

   /// isPlaying
   /// 
   /// \return true if the instance is playing samples, and
   ///         false otherwise.
   bool isPlaying( void ) const;

private:

	/// Invoked by the callback function on the active instance
   /// each time more samples are needed. This member fills
   /// the portaudio output buffer with samples from the buffer
   /// specified in the call to startPlayback.
	///
	/// \param  buffer is the sample buffer
	/// \param  framesPerBuffer is the number of sample frames to
	///         stereo sample frames are stored in the buffer,
	///         and should be filled in by this call.
	/// \return true if more samples are to be played, false
	///         otherwise.
	bool playback( float * buffer, unsigned int framesPerBuffer );

// HELPERS

   /// startSoundStream
   /// helper function to establish a connection to the sound device
   /// and begin playback.
   /// 
   /// \throw  std::runtime_error if the sound stream cannot be 
   ///         initialized or activated
   void startSoundStream( void );
 
   /// stopSoundStream
   /// helper function to break a connection to the sound device
   /// 
   /// \throw  std::runtime_error if there is an error while closing 
   ///         the sound stream
   void stopSoundStream( void ) const;
   
 	///	PaCallback
	///	Callback function PortAudio uses to request more samples.
    /// 
    /// \param  inputBuffer is the input sample frames (not used)
    /// \param  outputBuffer is the output sample frames, fill this
    ///         with samples to playback
    /// \param  framesPerBuffer is the size of the input and output
    ///         buffers in sample frames
    /// \param  outTime is a timestamp for the current frame (not used)
    /// \param  userData is a pointer to callback data, used here to 
    ///         pass an instance of SamplePlayer into the callback.
	static int PaCallback( void *inputBuffer, void *outputBuffer,
	                       unsigned long framesPerBuffer,
	                       PaTimestamp outTime, void *userData );
	   
// MEMBER VARIABLES

   mutable PortAudioStream * mStream;  // audio stream object, used to manage 
                              			// a connection to the audio device

	double mSampleRate;       // sample rate in Hz
	unsigned int mNumChannels;// number of audio channels

	const float * mCurrentSample;   // pointer into sample buffer
	const float * mEndSamples;      // pointer to end of sample buffer
};

#endif  // SAMPLEPLAYER_H


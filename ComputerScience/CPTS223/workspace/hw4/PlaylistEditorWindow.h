#ifndef PLAYLISTEDITORWINDOW_H
#define PLAYLISTEDITORWINDOW_H

///////////////////////////////////////////////////////////////////////////////
/// \class        PlaylistEditorWindow
/// \author       Christopher J. Mallery
/// \date         1/30/2006
/// \brief        Simple Playlist Editor
/// BASE CLASSES: Fl_Window
///
/// PURPOSE:   Allows for the building of an audio playlist.            
///
/// REVISION HISTORY:
/// 1/31/2006          Initial Creation
///           
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//
#include <string>

// PROJECT INCLUDES
//
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Box.h>

#include "List.h"
#include "Soundfile.h"
class PlaylistEditorWindow : public Fl_Window
{

public:

	typedef ListIterator<Soundfile> PlaylistIterator;
// LIFECYCLE

	/// Default constructor.
	PlaylistEditorWindow( void );
	
	/// Destructor.
	~PlaylistEditorWindow( void );

private:

	/// nextButtonCallback_static
	/// The static callback for mNextButton
	/// \param void* data: A pointer to this
	/// THIS FUNCTION SHOULD NEVER BE CALLED BY HAND
	static void nextButtonCallback_static( Fl_Widget *w, void* data );
	
	/// prevButtonCallback_static
	/// The static callback for mPrevButton
	/// \param void* data: A pointer to this
	/// THIS FUNCTION SHOULD NEVER BE CALLED BY HAND
	static void prevButtonCallback_static( Fl_Widget *w, void* data );
	
	/// insertButtonCallback_static
	/// The static callback for mInsertButton
	/// \param void* data: A pointer to this
	/// THIS FUNCTION SHOULD NEVER BE CALLED BY HAND
	static void insertButtonCallback_static( Fl_Widget *w, void* data );
	
	/// eraseButtonCallback_static
	/// The static callback for mEraseButton
	/// \param void* data: A pointer to this
	/// THIS FUNCTION SHOULD NEVER BE CALLED BY HAND
	static void eraseButtonCallback_static( Fl_Widget *w, void* data );
	
	/// playAllButtonCallback_static
	/// The static callback for mPlayAllButton
	/// \param void* data: A pointer to this
	/// THIS FUNCTION SHOULD NEVER BE CALLED BY HAND
	static void playAllButtonCallback_static( Fl_Widget *w, void* data );

	/// nextButtonCallback
	/// This method is called when the "Next" button is pushed
	void nextButtonCallback( void );
	
	/// prevButtonCallback
	/// This method is called when the "Previous" button is pushed	
	void prevButtonCallback( void );
	
	/// insertButtonCallback
	/// This method is called when the "Insert" button is pushed	
	void insertButtonCallback( void );
	
	/// eraseButtonCallback
	/// This method is called when the "Erase" button is pushed
	void eraseButtonCallback( void );
	
	/// playAllButtonCallback
	/// This method is called when the "Play All" button is pushed
	void playAllButtonCallback( void );
	
	/// updateButtonState
	/// Enables/Disables the four buttons according to 
	/// the internal state of class
	void updateButtonState( void );
	
	/// updateFilenameDisplay
	/// Call this function to update the window's displayed filename.
	void updateFilenameDisplay( const std::string & s );
		
	/// Pointers to the window's 5 buttons and the filename display
	Fl_Button* 	mNextButton;
	Fl_Button* 	mPrevButton;
	Fl_Button*	mInsertButton;
	Fl_Button* 	mEraseButton;
	Fl_Button*	mPlayAllButton;
	Fl_Box* 	mFilenameDisplay;
	
	List<Soundfile> mPlaylist;
	ListIterator<Soundfile> mPlaylistIterator;
};

#endif


#ifndef SCORCH_H    // include guard
#define SCORCH_H

///////////////////////////////////////////////////////////////////////////////
/// \class        Scorch
/// \author       Alex Hortin 
/// \date         March 20 2006
/// \brief        A class that stores a players details
///
/// This class stores a players details and can modify HP, award XP, save the
/// the level and skills of that player.
///
/// REVISION HISTORY
///
/// None
///
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
// LOCAL INCLUDES
//
#include "Player.h"//the node to be defined
#include "Scorch.h"//the node to be defined
// FORWARD REFERENCES
//

// CONSTANTS
//


class Scorch
{
   public:
   
	struct x_y
	{
		int x;
		int y;
	};
	
	
// LIFECYCLE

   /// Default constructor.
   /// \pre    None
   /// \post   An instance of player is constructed and new stats file will be contructed
   /// \param  string for the username
   /// \throw  None
  	Scorch();

// OPERATORS
	
// OPERATIONS 
  
	/// fire fires a shot changes game state using the modify terrain and deal damage
   /// \pre    a games is started and players are put into their locations
   /// \post   The terrain vector is built
   /// \param  power for power of bullet
	/// \param	angle for the angle of bullet
	/// \param	payload for the size of bullet
   /// \return the x and y values of the bullets
   /// \throw  None
   std::vector<Scorch::x_y> fire(unsigned int power, unsigned int angle, unsigned int payload);
	
	/// buildTerrain builds the terrain using the seed
   /// \pre    none
   /// \post   The terrain vector is built
   /// \param  none
   /// \return none
   /// \throw  None
   void buildTerrain( time_t seed );
	
	/// seedTerrainRand returns a seed to use to build terrain
   /// \pre    none
   /// \post   The terrain vector is built
   /// \param  none
   /// \return none
   /// \throw  None
   time_t seedTerrainRand( void );
	
	/// addPlayer adds a player to the players vector
   /// \pre    none
   /// \post   The terrain vector is built
   /// \param  a string for name and a location
   /// \return none
   /// \throw  None
   void addPlayer( std::string name, int loc );
	
	/// moveRight move a player right and consumers fuel
   /// \pre    none
   /// \post   The terrain vector is built
   /// \param  a string for name and a location
   /// \return none
   /// \throw  None
   void moveRight();

	/// moveLeft moves a tank left and consumes fuel
   /// \pre    none
   /// \post   The terrain vector is built
   /// \param  a string for name and a location
   /// \return none
   /// \throw  None
   void moveLeft();
	
// ACCESS and MUTATE
	
	/// modifyTerrain damages the terrain based on power and location of explosion
   /// \pre    a games is started and players are put into their locations
   /// \post   The terrain vector is modified due to explosions
   /// \param  none
   /// \return none
   /// \throw  None
   void modifyTerrain(unsigned int power, int x);
	
	/// dealDamage deals damage to a player based on power and location of explosion 
   /// \pre    none
   /// \post   The terrain vector is built
   /// \param  none
   /// \return none
   /// \throw  None
   void dealDamage(unsigned int power, int x);
	
// INQUIRY
   
	/// y_terrain returns a y based on the x
   /// \pre    A valid Player
   /// \post   none
   /// \param  int containing x
   /// \return an int containing the y information
   /// \throw  None
   int y_terrain( int x );
	
	/// returnTerrain returns the entire terrain vector
	/// \pre    A valid Player
	/// \post   none
	/// \param  none
	/// \return a vect of ints containing the y information
	/// \throw  None
   std::vector<unsigned int> returnTerrain( void);
	
	/// returnTankLocations returns all the tanks location in a vector of ints
	/// \pre    A valid Player
	/// \post   none
	/// \param  none
	/// \return a vector containing all of the locations of the players
	/// \throw  None
   std::vector<int> returnTankLocations(void );
	
	/// playersAlive returns a bool vector of people still alive
	/// \pre    A valid Player
	/// \post   none
	/// \param  none
	/// \return a vector containing true or false based on players life
	/// \throw  None
   std::vector<bool> playersAlive(void );
	
	/// lastAngle returns the last angle of each tank
	/// \pre    A valid Player
	/// \post   none
	/// \param  none
	/// \return a vector containing the players last angle fired
	/// \throw  None
   std::vector<int> lastAngle(void );
	
	/// isTurn returns a bool if it is that player numbers turn
	/// \pre    A valid scorch with at least 2 players
	/// \post   none
	/// \param  none
	/// \return a vector containing the players last angle fired
	/// \throw  None
   bool isTurn(int i );
	
	/// isGameOver returns a bool if the game is over
	/// \pre    A valid scorch has been started
	/// \post   none
	/// \param  none
	/// \return bool if game is over or not
	/// \throw  None
   bool isGameOver();
	
	/// infoString returns info about the game
	/// \pre    A valid Player
	/// \post   none
	/// \param  none
	/// \return a string containing the information for all of the players
	/// \throw  None
   std::string infoString(void );
	

	
// MEMBER VARIABLES
private:
   //Players
	std::vector<Player> mPlayers;
	//Terrain 
	std::vector <unsigned int> mTerrain;
	//mLastAngle 
	std::vector <int> mLastAngle;
	//Turn
	int mTurn;

}; // end of class Card

#endif

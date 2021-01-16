#pragma once

#include <Godot.hpp>
#include <Camera2D.hpp>
#include <Tween.hpp>

#include "../utils/Utils.h"
#include "Direction.h"

/**
 * Represent the player in the game
 * 
 * Can moove according to a direction and a destination on the X axis
 * Animated when standing and mooving
 */
class Camera : public godot::Camera2D {

	//To make godot able to use this class
	GODOT_CLASS(Camera, godot::Camera2D);

public:
	/* CONSTRUCTOR && DESTRUCTOR */

	/**
	 * Constructor, usefull only to create the class and avoid warnings,
	 *		the real initialisation is done in the "_ready" method.
	 */
	Camera();

	/**
	 * Destructor, usefull only to create the class and avoid warnings,
	 *		godot deallocates the memory itself.
	 */
	~Camera();

	/* METHODS */

	//Needed by godot

	/**
	 * Register the methods godot is directly going to call
	 */
	static void _register_methods();
	/**
	 * Needed by godot to create the class, not usefull here
	 *		the initialisation is done in the "_ready" method called after
	 * 
	 */
	void _init();

	/**
	 * Initilisation of the class and the scene here.
	 *		Called after the parent node and all its children entenred a scene.
	 */
	void _ready();

	/**
	 * Called every frame.
	 */
	void _process();

	/**
	 * Determine if the player has entered a new room
	 * 
	 * @return true if the player has entered in a new room
	 */
	bool isPlayerEnteringNewRoom();

	/**
	 * Determine if the player is inside the range where he can change of rooms
	 * 
	 * @return - 0 : if the player isn't inside a change room range
	 *		   - 1 : if the player is inside the cellar change room range
	 *		   - 2 : if the player is inside the living room change room range
	 */
	int isPlayerInsideChangeRoomRange();

	/**
	 * Do a linear interpolation with a tiny bounce at the end to the new camera's position
	 * 
	 * @param changeToCellar : true if the player is entering the cellar room, false otherwise
	 */
	void changeRoom(bool changeToCellar);

	/**
	 * Make the camera follow the player
	 */
	void follow_player();

	/* PROPERTIES */

	godot::Vector2 m_cellarCamPosition;
	/**
	 * Set the camera's position when the player is in the cellar
	 * 
	 * @param newPosition, the new position for the cellar
	 */
	void setCellarCamPosition(godot::Vector2 newPosition);

	/**
	 * Get the camera's position when the player is in the cellar
	 */
	godot::Vector2 getCellarCamPosition();

	godot::Vector2 m_livingRoomCamPosition;
	/**
	 * Set the camera's position when the player is in the living room
	 *
	 * @param newPosition, the new position for the living room
	 */
	void setLivingRoomCamPosition(godot::Vector2 newPosition);

	/**
	 * Get the camera's position when the player is in the living room
	 */
	godot::Vector2 getLivingRoomCamPosition();

	//Represents the duration in s of change room transition
	double m_interpolationDuration;

	/**
	 * Set the duration of the change room transition
	 * 
	 * @param newDuration the new transition's duration
	 */
	void setInterpolationDuration(double newDuration);

	/**
	 * Get the duration of the change room transition
	 * 
	 * @return the transition's duration
	 */
	double getInterpolationDuration();

	/*Represents the x position from where the camera starts to follow the player
		on the left side of the room*/
	int m_startFollowPlayerLeft;

	/**
	 * Set the position from where the camera starts to follow the player
	 *		on the left side of the room
	 * 
	 * @param newPosition, the new position that will be set
	 */
	void setStartFollowPlayerLeft(int newPosition);

	/**
	 * Get the position from where the camera starts to follow the player
	 *		on the left side of the room
	 * 
	 * @return this actual x position
	 */
	int getStartFollowPlayerLeft();

	/*Represents the x position from where the camera starts to follow the player
		on the right side of the room*/
	int m_startFollowPlayerRight;

	/**
	 * Set the position from where the camera starts to follow the player
	 *		on the right side of the room
	 *
	 * @param newPosition, the new position that will be set
	 */
	void setStartFollowPlayerRight(int newPosition);

	/**
	 * Get the position from where the camera starts to follow the player
	 *		on the right side of the room
	 *
	 * @return this actual x position
	 */
	int getStartFollowPlayerRight();

	/* ACCESSORS & MUTATORS */

	/**
	 * Set the player position
	 * 
	 * @param playerPosition : the new player's position
	 */
	void setPlayerPosition(godot::Vector2 playerPosition);

	/**
	 * Set the player direction
	 *
	 * @param playerPosition : the new player's direction
	 */
	void setPlayerDirection(Direction newDirection);

private:
	//Child nodes
	godot::Tween* m_tween;

	godot::Vector2 m_playerPosition;
	Direction m_playerDirection;
	bool m_playerIsInCellar;	//True if the player is in the cellar, false if he is not
};
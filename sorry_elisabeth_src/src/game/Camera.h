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

	GODOT_CLASS(Camera, godot::Camera2D);	// Needed by godot to be able to use this class

public:
	
	Camera();
	~Camera();

	// Register the methods and properties that godot is directly going to call and use
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Called every frame, manage the camera position
	void _process();


	/* PROPERTIES */
	void setCellarCamPosition(const godot::Vector2 newPosition);
	godot::Vector2 getCellarCamPosition() const;

	void setLivingRoomCamPosition(const godot::Vector2 newPosition);
	godot::Vector2 getLivingRoomCamPosition() const;

	void setInterpolationDuration(const double newDuration);
	double getInterpolationDuration() const;

	void setStartFollowPlayerLeft(const int newPosition);
	int getStartFollowPlayerLeft() const;

	void setStartFollowPlayerRight(const int newPosition);
	int getStartFollowPlayerRight() const;


	/* MUTATORS */
	void setPlayerPosition(const godot::Vector2 playerPosition);
	void setPlayerDirection(const Direction newDirection);


	/* CONSTANTS */
	static const int CELLAR_POSITION_X = 0;
	static const int LIVING_ROOM_POSITION_X = 320;

	static const int START_FOLLOW_PLAYER_LEFT_MIN = 0;
	static const int START_FOLLOW_PLAYER_LEFT_MAX = 160;
	static const int START_FOLLOW_PLAYER_RIGHT_MIN = 480;
	static const int START_FOLLOW_PLAYER_RIGHT_MAX = 640;

	static const int CHANGE_ROOM_RANGE = 20; //The range in wich the player is considered in the other room

protected:

	// Determine if the player is curently entering a new room
	const bool isPlayerEnteringNewRoom();

	/**
	 * Determine if the player is inside the range where he can change of rooms
	 *
	 * @return - 0 : if the player isn't inside a change room range
	 *		   - 1 : if the player is inside the cellar change room range
	 *		   - 2 : if the player is inside the living room change room range
	 */
	const int isPlayerInsideChangeRoomRange();

	/**
	 * Do a linear interpolation with a tiny bounce at the end to the new camera's position
	 *
	 * @param changeToCellar : true if the player is entering the cellar room, false otherwise
	 */
	void changeRoom(const bool changeToCellar);

	// Make the camera follow the player
	void follow_player();


	/* MEMBER VARIABLES */

	// Child nodes
	godot::Tween* m_tween;

	godot::Vector2 m_playerPosition;
	Direction m_playerDirection;
	bool m_playerIsInCellar;	//True if the player is in the cellar, false otherwise

	// Properties
	godot::Vector2 m_cellarCamPosition;
	godot::Vector2 m_livingRoomCamPosition;
	double m_interpolationDuration;	// Represents the duration in s of the change room transition
	int m_startFollowPlayerLeft;	// Represents the x position from where the camera starts to follow the player on the left side of the room
	int m_startFollowPlayerRight;	// Represents the x position from where the camera starts to follow the player on the right side of the room
};
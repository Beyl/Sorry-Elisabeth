#pragma once

#include <Godot.hpp>

/**
 * Define methods and constants usefull in all parts of this project
 */
class Utils {

public:

	/*METHODS*/

	/**
	 * Define if the position of the element given in parameter is contained inside the room
	 * 
	 * @param eltPosition, a vector in 2 demensions representing the position of an element
	 * @return true if it's contained inside a room and false otherwise
	 */
	static bool const isInsideRoom(const godot::Vector2 eltPosition);

	/**
	 * Define if the X position of the element given in parameter is contained inside the room
	 *
	 * @overload
	 */
	static bool const isInsideRoomX(const int eltXPosition);

	/**
	 * Define if the Y position of the element given in parameter is contained inside the room
	 *
	 * @overload
	 */
	static bool const isInsideRoomY(const int eltYPosition);

	/*CONSTANTS*/
	//GAME
	static const int PLAYER_START_X = 25;
	static const int PLAYER_START_Y = 100;

	//ROOM
	static const int ROOM_HEIGHT_BEGINNING = 48;
	static const int ROOM_HEIGHT_ENDING = 180;
	static const int ROOM_WIDTH_BEGINNING = -40;
	static const int ROOM_WIDTH_ENDING = 660;

	static const int ROOM1_TRANSITION = 300;	// Go to room 2 when the player's position is greater then that
	static const int ROOM2_TRANSITION = 20;	// Go to room 1 when the player's position is lower then that 

	//CAMERA
	static const int CELLAR_POSITION_X = 0;
	static const int LIVING_ROOM_POSITION_X = 320;

	static const int START_FOLLOW_PLAYER_LEFT_MIN = 0;
	static const int START_FOLLOW_PLAYER_LEFT_MAX = 160;
	static const int START_FOLLOW_PLAYER_RIGHT_MIN = 480;
	static const int START_FOLLOW_PLAYER_RIGHT_MAX = 640;

	//The range (in px) in wich the player's is considered in the other room
	static const int CHANGE_ROOM_RANGE = 20;

	//PLAYER
	static const int MIN_SPEED = 5;
	static const int MAX_SPEED = 500;

	static const int NO_DESTINATION = -500;	// Set when the player doesn't need to move

	static const int NOT_MOOVING_RANGE = 10;	// The range around the player where he does not moove
};
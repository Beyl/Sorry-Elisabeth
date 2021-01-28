#pragma once

#include <Godot.hpp>

/**
 * Define methods and constants usefull in all parts of this project
 */
class Utils {

public:

	/**
	 * Define if the position of the element is contained inside the room range
	 * 
	 * @param eltPosition, a vector in 2 demensions representing the position of the element
	 * @return true if it's contained inside the room range and false otherwise
	 */
	static bool const isInsideRoom(const godot::Vector2 eltPosition);

	/**
	 * Define if the X position of the element is contained inside X the room
	 *
	 * @param eltPosition, the X position of the element
	 * @return true if it's contained inside thre room X range and false otherwise
	 */
	static bool const isInsideRoomX(const int eltXPosition);

	/**
	 * Define if the Y position of the element is contained inside Y the room
	 *
	 * @param eltPosition, the Y position of the element
	 * @return true if it's contained inside thre room Y range and false otherwise
	 */
	static bool const isInsideRoomY(const int eltYPosition);

	/**
	 * Define the screen centered position of an object
	 *
	 * @param objectSize, the size of the object
	 * @return the screen centered position of an object
	 */
	static godot::Vector2 getCenteredPosition(godot::Vector2 objectSize);

	/* CONSTANTS (Coordinates & positions are setted pixels) */

	// SCREEN
	static const int SCREEN_WIDTH = 320;
	static const int SCREEN_HEIGHT = 180;

	// ROOM
	static const int ROOM_HEIGHT_BEGINNING = 30;
	static const int ROOM_HEIGHT_ENDING = 180;
	static const int ROOM_WIDTH_BEGINNING = -40;
	static const int ROOM_WIDTH_ENDING = 660;

	// INTERACTIONS
	static const int MAX_INTERACTIONS_NUMBER = 3;
};
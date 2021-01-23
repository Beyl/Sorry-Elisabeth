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

	/*CONSTANTS (Coordinates & positions are setted pixels) */

	//ROOM
	static const int ROOM_HEIGHT_BEGINNING = 30;
	static const int ROOM_HEIGHT_ENDING = 180;
	static const int ROOM_WIDTH_BEGINNING = -40;
	static const int ROOM_WIDTH_ENDING = 660;
};
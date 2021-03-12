#pragma once

#include <Godot.hpp>

/**
 * Define methods and constants usefull in all parts of this project
 * @version beta
 */
class Utils {

public:

	/**
	 * Define if the position of the element is contained inside an object
	 *
	 * @param eltPosition, the global position of the element
	 * @param objectPosition, the global position of the object
	 * @param objectSize, the size of the object
	 * @return true if the position is contained inside the object and false otherwise
	 */
	static bool isInsideArea(const godot::Vector2 eltPosition, const godot::Vector2 objectPosition, const godot::Vector2 objectSize);

	/**
	 * Define if the position of the element is contained inside an object on the X axis
	 *
	 * @param eltPosition, the global position of the element on the X axis
	 * @param objectPosition, the global position of the object on the X axis
	 * @param objectSize, the height of the object
	 * @return true if the position is contained inside the object on the X axis and false otherwise
	 */
	static bool isInsideObjectX(const real_t eltPositionX, const real_t objectPositionX, const real_t objectSizeX);

	/**
	 * Define if the position of the element is contained inside an object on the Y axis
	 *
	 * @param eltPosition, the global position of the element on the Y axis
	 * @param objectPosition, the global position of the object on the Y axis
	 * @param objectSize, the height of the object
	 * @return true if the position is contained inside the object on the Y axis and false otherwise
	 */
	static bool isInsideObjectY(const real_t eltPositionY, const real_t objectPositionY, const real_t objectSizeY);

	/**
	 * Define if the position of the element is contained inside the room range
	 * 
	 * @param eltPosition, a vector in 2 demensions representing the position of the element
	 * @return true if it's contained inside the room range and false otherwise
	 */
	static bool isInsideRoom(const godot::Vector2 eltPosition);

	/**
	 * Define if the X position of the element is contained inside X the room
	 *
	 * @param eltPosition, the X position of the element
	 * @return true if it's contained inside thre room X range and false otherwise
	 */
	static bool isInsideRoomX(const real_t eltXPosition);

	/**
	 * Define if the Y position of the element is contained inside Y the room
	 *
	 * @param eltPosition, the Y position of the element
	 * @return true if it's contained inside thre room Y range and false otherwise
	 */
	static bool isInsideRoomY(const real_t eltYPosition);

	/**
	 * Define the screen centered position of an object
	 *
	 * @param objectSize, the size of the object
	 * @return the screen centered position of an object
	 */
	static godot::Vector2 getCenteredPosition(const godot::Vector2 objectSize);


	/* CONSTANTS (Coordinates, positions & sizes are setted pixels) */

	// SCREEN
	static const int SCREEN_WIDTH = 320;
	static const int SCREEN_HEIGHT = 180;
	
	// OTHERS
	static const int ASCII_CONVERSION_0 = 48;	// 48 on the ascii table is equal to "0"
	static const int ASCII_CONVERSION_1 = 49;	// 49 on the ascii table is equal to "1"
};
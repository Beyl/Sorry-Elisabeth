#pragma once

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <AnimatedSprite.hpp>

#include "../utils/Utils.h"
#include "Direction.h"

/**
 * Represent the player in the game
 * 
 * Can moove according to a direction and a destination on the X axis
 * Animated when standing and mooving
 */
class Player : public godot::KinematicBody2D {

	//To make godot able to use this class
	GODOT_CLASS(Player, godot::KinematicBody2D);

public:
	/* CONSTRUCTOR && DESTRUCTOR */

	/**
	 * Constructor, usefull only to create the class and avoid warnings,
	 *		the real initialisation is done in the "_ready" method.
	 */
	Player();

	/**
	 * Destructor, usefull only to create the class and avoid warnings,
	 *		godot deallocates the memory itself.
	 */
	~Player();

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
	 * Initilisation of the class and the scene
	 *		called after the parent node and all its children entenred a scene.
	 * 
	 */
	void _ready();

	/**
	 * Called every tic (60 times per seconds).
	 * 
	 */
	void _physics_process();

	/**
	 * Moove the player to the x position given in parameter if it's contained in the room height and width
	 * 
	 * @param xDestination, define the x position where the player will go
	 */
	void mooveTo(int xDestination);
	/**
	 * Change the player's direction
	 * 
	 * @param newDirection, the new direction the player will look at
	 */
	void changeDirection(Direction newDirection);
	/**
	 * Stop the player's movement
	 */
	void stopMooving();

	/* PROPERTIES */

	int m_speed;
	/**
	 * Set the player's speed
	 * 
	 * @param newSpeed, the new speed to set to the player restricted between SPEED_MIN and SPEED_MAX
	 */
	void setSpeed(int newSpeed);

	/**
	 * Return the player's speed
	 * 
	 * @return the player's speed
	 */
	int getSpeed();

	/* ACCESSORS & MUTATORS */

	/**
	 * Return the player's direction
	 *
	 * @return the player's direction
	 */
	Direction getDirection();

	/**
	 * Return the player's x destination
	 *
	 * @return the player's x destination
	 */
	int getXDestination();

private:
	//Child nodes
	godot::AnimatedSprite* m_animSprite;

	Direction m_direction;	// Define where the player is looking
	int m_xDestination;	// Define where the player is going
};
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

	GODOT_CLASS(Player, godot::KinematicBody2D);	// To make godot able to use this class

public:

	Player();
	~Player();

	/**
	 * Register the methods and properties godot is directly going to call
	 */
	static void _register_methods();
	void _init();	// Needed by godot

	// Initialise the class and the godot scene
	void _ready();

	// Called every tic (60 times per seconds), manage player movements and animations
	void _physics_process();

	// Moove the player on the X axis to a given position
	void mooveTo(const int xDestination);

	// Change the actual animated sprite animation with the handbag one
	void takeHandbag();

	/* ACCESSORS */
	const Direction getDirection();
	const int getXDestination();


	/* PROPERTIES */
	void setSpeed(const int newSpeed);
	int getSpeed() const;


	/* CONSTANTS */
	static const int MIN_SPEED = 5;
	static const int MAX_SPEED = 500;
	static const int NO_DESTINATION = -500;	// Set when the player doesn't need to move
	static const int NOT_MOOVING_RANGE = 10;	// The range around the player where he does not moove

protected:

	void changeDirection(const Direction newDirection);
	void stopMooving();


	/* MEMBER VARIABLES */
	//Child nodes
	godot::AnimatedSprite* m_animSprite;

	Direction m_direction;	// Define where the player is looking
	int m_xDestination;	// Define where the player is going
	godot::String m_animationSubName;

	//Properties
	int m_speed;
};
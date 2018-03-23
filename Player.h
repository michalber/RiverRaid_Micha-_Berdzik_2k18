// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#pragma once

#include <cmath>
#include <iostream>
#include <SDL.h>
#include <gl/glew.h>
#include <GL/GLU.h>

#include "vector3d.h"
#include "Missiles.h"
#include "Map.h"

#define RUN_SPEED 10
#define TURN_SPEED 10

class Player 
{
	vector3d loc;

	float playPitch, playYaw;
	float movevel;
	float mousevel;
	bool mi = true;
	bool ismoved;

	int tmpx = 0, tmpy = 0;
	float RotYaw;
	float RotPitch;
	float Health = 10.0;
	float Fuel = 10.0;

public:
	Player();
	~Player();

	Missiles bullets;

	void RenderPlayer(Map *mapa);
	int GetHealth();
	int GetFuel();
	float GetYaw();
	float GetPitch();
	float GetSpeed();
	vector3d getVector();
	vector3d getLocation();

private:
	void lockCamera();
	void moveCamera(float dir);
	void moveCameraUp(float dir);
	void LoadPlayer();
	void Control();
	void UpdateCamera();
	void CheckCollision(Map * mapa);
};


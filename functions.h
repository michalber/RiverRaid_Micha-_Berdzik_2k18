// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#ifndef FUNCTION_H
#define FUNCTION_H

#include <SDL.h>
#include <gl/glew.h>
#include <GLFW\glfw3.h>
#include <SFML\Window.hpp>

#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "objloader.h"
#include "vector3d.h"


void drawCube(float size);
void drawSkybox(float size);	//draw the skybox
void initskybox();	//load the textures
void killskybox();	//delete the textures

void lockCamera();
void moveCamera(float,float);
void moveCameraUp(float,float);
void Control(float,float,bool);
void UpdateCamera();
unsigned int loadTexture(const char*);
float dotproduct(float x1,float y1,float z1,float x2,float y2,float z2);
bool sphereplane(vector3d& sp,vector3d pn,vector3d p1,vector3d p2,vector3d p3,vector3d p4, float r);
bool raysphere(float xc,float yc,float zc,float xd,float yd,float zd,float xs,float ys,float zs,float r);
bool rayplane(const float& nx,float ny,float nz,float x0,float y0,float z0,float xs,float ys,float zs,float xd,float yd,float zd,vector3d p1,vector3d p2,vector3d p3,vector3d p4);
float trianglearea(vector3d p1,vector3d p2,vector3d p3);
bool spheresphere(vector3d c1,float r1,vector3d c2,float r2);
vector3d getcamcoord();
void setcamcoord(float x,float y,float z);
#endif

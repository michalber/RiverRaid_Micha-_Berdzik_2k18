// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#pragma once

#include <gl/glew.h>
#include "vector3d.h"
#include <vector>
#include "SFML\System.hpp"

using namespace std;
using namespace sf;

#define M_PI 3.1415


class Missiles
{

public:
	Missiles();
	~Missiles();

	void Add(vector3d pos,vector3d vec,float,float);
	void update(float);

	void remove(int it);

	void render();

	struct SingleBullet {
		vector3d loc;
		vector3d loc_buff = loc;
		float Yaw;
		float Pitch;
		float speed = 0;

		inline void Make() {			
			glPushMatrix();
			glTranslatef(loc.x,loc.y,loc.z);	//ustalenie pozycji pocz¹tkowej
		
		if (Pitch != 90 && Pitch != -90)
				moveCamera(0.0);
			moveCameraUp(0.0);
		
			glBegin(GL_TRIANGLE_STRIP);

			glColor3f(1.0f, 0.0f, 0.0f);

			glVertex3f(0, 0, 0);
			glVertex3f(-1, -1, 0);
			glVertex3f(0, -1, 1);

			glVertex3f(0, -1, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(1, -1, 0);
			glEnd();
			glPopMatrix();
			
		}

		void moveCamera(float dir)
		{
			float rad = (Yaw + dir)*M_PI / 180.0;
			loc.x -= sin(rad)*(50+speed);
			loc.z -= cos(rad)*(50+speed);
		}

		void moveCameraUp(float dir)
		{
			float rad = (Pitch + dir)*M_PI / 180.0;
			loc.y += sin(rad)*(50+speed);
		}

	};

private:
	sf::Clock timer;
	sf::Time frequency;
	std::vector<SingleBullet> p_bullets;
	std::vector<vector3d> factor;
	bool infinite;
	int ammunition;
};


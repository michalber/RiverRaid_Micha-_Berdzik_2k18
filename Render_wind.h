// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#ifndef RENDER_WIND_H
#define RENDER_WIND_H

#pragma comment(lib,"glu32.lib")

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML/Window.hpp>
#include <gl/glew.h>
#include <GLFW\glfw3.h>
#include <SDL.h>
#include <iostream>

#include "Player.h"

class Render_wind
{

//zmienne ------------------------------------------------------------------------
public:
	//SDL_Renderer* renderer;

private:
	const char *p_name;
	int p_width, p_height;

	SDL_Window *p_window;

	//SDL_Surface* p_screen;
	SDL_GLContext maincontext; /* Our opengl context handle */



// metody -------------------------------------------------------------------------
public:
	Render_wind(const char *name, int width, int height);
	~Render_wind();

	void clear() const;
	void update();
	void close() const;

	void Set_Perspective() const;
	//SDL_Surface GetScreen();

	void LoadingScreen();

	void RenderStatsFuel(Player* player);

	void RenderStatsLife(Player *player);


private:
	void set();
	bool init();

};

#endif //RENDER_WIND_H
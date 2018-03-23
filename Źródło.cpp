// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#pragma region Pierwsza wersja (nieaktywna)
# if 0
/*
#include "Render_wind.h"
#include "PerlinNoise.h"
#include "Map.h"
#include <SDL.h>
#include <math.h>
#include <vector>

#define RES_X 1280
#define RES_Y 720
#define BLOCK 60

#ifdef __WIN32
extern "C"
{
//Enable dedicated graphics
__declspec(dllexport) bool NvOptimusEnablement = true;
__declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
}
#endif // __WIN32

using namespace engine;


std::vector<std::vector<float> > heights;

void loadHeightmap(const char* name)
{
	SDL_Surface* img = SDL_LoadBMP(name);
	if (!img)
	{
		std::cout << "image is not loaded" << std::endl;
		return;
	}

	std::vector<float> tmp;
	for (int i = 0;i<img->h;i+=4)
	{
		tmp.clear();
		for (int j = 0;j<img->w;j+=4)
		{
			Uint32 pixel = ((Uint32*)img->pixels)[i*img->pitch / 4 + j];
			Uint8 r, g, b;	//unsigned char
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			tmp.push_back((float)r / 255.0);	//0.0,1.0
		}
		heights.push_back(tmp);
	}
}
void renderHeightmap(float size, float h)
{
	for (int i = 0;i<heights.size() - 1;i++)
		for (int j = 0;j<heights[0].size() - 1;j++)
		{
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(heights[i][j], heights[i][j], heights[i][j]);
			glVertex3f(i*size, j*size, heights[i][j] * h);
			glVertex3f((i + 1)*size, j*size, heights[i + 1][j] * h);
			glVertex3f(i*size, (j + 1)*size, heights[i][j + 1] * h);
			glVertex3f((i + 1)*size, (j + 1)*size, heights[i + 1][j + 1] * h);
			glEnd();
		}
}

int main(int argc, char* argv[]){

	Render_wind window("Gra", RES_X, RES_Y);
	//Map mapa0(1000, 100);
	loadHeightmap("heightmap.bmp");

	glClearDepth(1.f);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	sf::Clock Clock;

	bool start = 0;
	const int col(1000), row(100);

	int frequency = 6;
	const double fx = 3*col / frequency;
	const double fy = row / frequency;
	std::uint32_t seed = 1000;
	PerlinNoise perlin;
	perlin.reseed(seed);

	
	static float map0[3*col][row];
	for (int y = 0; y < row; y++) {
		for (int x = 0; x < 3*col; x++){
			
				map0[x][y] = 50 * perlin.octaveNoise(x / fy, y / fy, 8) + 40;
				if (y > rand() % 3 + 45 && y < rand() % 3 + 55)
				map0[x][y] = 8 * perlin.octaveNoise(x / fy, y / fy, 4)-10;
		}
	}
	

	bool rotate = true;
	float angle=0;
	float a = 5000;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.f, 1.f, 2.f,5000.0f);//fov, aspect, zNear, zFar



	while (!window.closed()) {
		window.clear();
		
		if (rotate && start) {
			//angle = Clock.getElapsedTime().asSeconds() / 5;
			angle += 0.004;
		}

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) std::cout << "PRESSED!" << std::endl;


		if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window.~Render_wind();	
			return 0;
		}
		if (window.isKeyPressed(GLFW_KEY_W)) {
			if (a < 10000.f)	a += 10.f;
			else a = a;
		}
		else a = a;
		if (window.isKeyPressed(GLFW_KEY_S)) {
			a -= 10.f;
		}
		else a = a;

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glTranslatef(1500.f, 150.f, -600.f);
		glTranslatef(0, 130.f, -800.f);
		glRotatef(90, 0, 0, 1.0);
		glRotatef(40, 0, 1, 0);
		glRotatef(20, 0, 1, 0);

		if (window.isKeyPressed(GLFW_KEY_A)) {
			glRotatef(-10, 1, 0, 0);
		}
		if (window.isKeyPressed(GLFW_KEY_D)) {
			glRotatef(10, 1, 0, 0);
		}
		if (window.isKeyPressed(GLFW_KEY_SPACE) && !start) {
			angle = 0;
			start = 1;
		}

		
		//glRotatef(angle * 50, 1.f, 0.f, 0.f);
		//glRotatef(angle * 30, 0.f, 1.f, 0.f);
		glRotatef(angle * 80, 0.f, 0.f, 1.f);

	//	glTranslatef(94700, 0, 0);

		glLineWidth(1.3f);
		
		if (start) {
			//glTranslatef(angle*-a, 0, 0);
		}
		
		/*
		for (int y = -row/2; y < row/2; y++) {
			glBegin(GL_TRIANGLE_STRIP);//draw some squares
			for (int x = -3*col/2; x < 3*col/2; x++) {
				
					if (heights[x + (3*col / 2)][y + row / 2] < 10)
						glColor3f(0.0f, 0.55f, 0.7f);
					else
						glColor3f(0.8f, 0.8f, 0.8f);

					glVertex3f(x*BLOCK, y*BLOCK, heights[x + (3*col / 2)][y + row / 2]); //vertex 2
					glVertex3f(x*BLOCK, (y + 1)*BLOCK, heights[x + (3*col / 2)][y + 1 + row / 2]); //vertex 1
				
			}
			glEnd();

		}
		
		renderHeightmap(8, 400);
		//glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_BACK, GL_LINE);
		//glDisable(GL_DEPTH_TEST);

		window.update(); 
	}
	return 0;
}
*/
#endif
#pragma endregion 

#pragma region deklaracje

#include <iostream>
#include <vector>
#include <ctime>
#include <thread>

#include <SDL.h>
#include<SDL_mixer.h>
#include <gl/glew.h>

#include "functions.h"
#include "Render_wind.h"
#include "Map.h"
#include "Player.h"
#include "Audio.h"

#pragma comment(lib,"glu32.lib")
#pragma endregion

//uaktywnienie grafiki dedykowanej 
#ifdef __WIN32 
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif // __WIN32


void init(float angle)	
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, 1280.0 / 720.0, 1, 10000000);
	glMatrixMode(GL_MODELVIEW);
	initskybox();
	glEnable(GL_DEPTH_TEST);

	//loadHeightmap("heightmap.bmp",1);
	//loadColormap("colormap.bmp", 1);
	//Loadf(1,80);
}

void display()
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//cam.Control();
	//cam.UpdateCamera();
	drawSkybox(1000);
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_AUDIO);

	Render_wind window("River Raid", 1280, 720);

	glewExperimental = GL_TRUE;
	glewInit();						

	Map mapa(100, 120);
	Player samolot;
	float p = 0;

	int start;
	SDL_Event event;
	bool runningGame = false;
	bool runningLoading = true;
	float angle = 50;
	init(angle);
	bool b = false;

	

	Audio introMusic("Res/intro.mp3");
	Audio gameMusic("Res/gamesong.mp3");

	/*
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("Res/Fonts/rs.ttf", 25);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid(font, "Welcome to Gigi Labs", color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(window.GetRenderer(), surface);
	int texW = 0;
	int texH = 0;	
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	*/


#pragma region W¹tek £adowania
		sf::Thread Load(&Map::LoadAll, &mapa);
		Load.launch();

#pragma region Loading Screen
	introMusic.playMusic();

	while (runningLoading)
	{
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				runningLoading = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					runningLoading = false;
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				break;

			}
		}
		window.clear();

			window.LoadingScreen();
		
		if (!introMusic.IsPlaying() && mapa.Loaded==1) {
			runningLoading = false;
			runningGame = true;
		}

		window.update();
		if (1000.0 / 60 > SDL_GetTicks() - start)
			SDL_Delay(1000.0 / 60 - (SDL_GetTicks() - start));
		//SDL_Delay(1);
	}

#pragma endregion
	Load.wait();
	mapa.LoadVertex();
	Load.terminate();
#pragma endregion


	gameMusic.playMusicInf();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
#pragma region Game
	while (runningGame)
	{
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				runningGame = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					runningGame = false;
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				//cam.mouseIn(true);
				break;
			case SDL_MOUSEBUTTONDOWN:
				//
				break;
			}
		}
		window.clear();
	
		
		glPushMatrix();

			window.RenderStatsFuel(&samolot);
			window.RenderStatsLife(&samolot);
			
			samolot.RenderPlayer(&mapa);
			
			glPushMatrix();
			glTranslated(0, p -= 0.1, 0);
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

			glPushMatrix();
			drawSkybox(1000000);

			mapa.RenderMap();
			glPopMatrix();

			glPushMatrix();
			samolot.bullets.render();
			glPopMatrix();

		glPopMatrix();
	
			

			
		//glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_BACK, GL_LINE);
		window.update();
		if (1000.0 / 100 > SDL_GetTicks() - start)
			SDL_Delay(1000.0 / 100 - (SDL_GetTicks() - start));
		//SDL_Delay(1);
	}
#pragma endregion

	window.close();
	return EXIT_SUCCESS;
}

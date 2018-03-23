// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#pragma once 
#include <SDL.h>
#include <gl/glew.h>
#include <iostream>
#include <math.h>
#include "SFML\System.hpp"
#include "vertexarray.h"

class Map
{

	//zmienne ------------------------------------------------------------
public:

	bool Loaded = 0;

private:

	std::vector<std::vector<float>> heights;
	std::vector<std::vector<std::vector<float>>> colormap;

	GLuint m_positionBuffer;
	GLuint m_vao;
	GLuint colorbuffer;

	float* positions = NULL;
	float* colors = NULL;
	int size;
	int m_meshResolution;

	int p_block;
	int p_height;

		
	//metody ------------------------------------------------------------
public:
	Map(int,int);
	~Map();

	void LoadAllThread();
	void RenderMap();
	void LoadAll();
	float GetValue(int x, int y);
	void LoadVertex();

private:
	void loadHeightmap(const char* name, int step);
	void loadColormap(const char* name, int step);
	void LoadBuffers(int block, int h);
	void LoadPosBuff();
	void LoadMapVao();
	void LoadColorBuff();
};





// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#include "Map.h"

	Map::Map(int block, int height ): p_block(block), p_height(height)
	{
	}


	Map::~Map()
	{
	}

	void Map::LoadAllThread() {
		
	}

	void Map::LoadAll() {
		
		loadHeightmap("heightmap.bmp", 1);
		loadColormap("colormap.bmp", 1);
		LoadBuffers(p_block, p_height);
		LoadVertex();
		Loaded = 1;
	}

	float Map::GetValue(int x, int y)
	{
		return heights[x][y];
	}

	void Map::LoadVertex() {
		LoadPosBuff();
		LoadMapVao();
		LoadColorBuff();
	}

	void Map::LoadPosBuff()
	{
		glGenBuffers(1, &m_positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size, positions, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Map::LoadMapVao()
	{
		glGenVertexArrays(1, &m_vao);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_positionBuffer);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Map::LoadColorBuff()
	{
		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size, colors, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glFinish();
		glColorPointer(3, GL_FLOAT, 0, (char *)NULL);
	}

	void Map::RenderMap() {

		glPushMatrix();
		glTranslated(0, 0, 300);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glBindVertexArray(m_vao);

		glDrawArrays(GL_TRIANGLES, 0, m_meshResolution*m_meshResolution * 2 * 3);

		glBindVertexArray(0);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		
		glPopMatrix();
	}



	void Map::loadHeightmap(const char* name, int step)
	{
		SDL_Surface* img = SDL_LoadBMP(name);
		if (!img)
		{
			std::cout << "image is not loaded" << std::endl;
			return;
		}
		heights.resize(img->h);
		for (int i = 0;i<img->h;i++)
		{
			heights[i].resize(img->w);
		}
		for (int i = 0;i<img->h;i += step)
		{
			for (int j = 0;j<img->w;j += step)
			{
				Uint32 pixel = ((Uint32*)img->pixels)[i*img->pitch / 4 + j];
				Uint8 r, g, b;	//unsigned char
				SDL_GetRGB(pixel, img->format, &r, &g, &b);
				heights[i][j] = (float)r / 255.0;
			}
		}
	}

	void Map::loadColormap(const char* name, int step)
	{
		SDL_Surface* img = SDL_LoadBMP(name);
		if (!img)
		{
			std::cout << "image is not loaded" << std::endl;
			return;
		}

		colormap.resize(img->h);
		for (int i = 0;i<img->h;i++)
		{
			colormap[i].resize(img->w);
			for (int j = 0;j<img->w;j++)
			{
				colormap[i][j].resize(3);
			}
		}

		for (int i = 0;i<img->h;i += step)
		{
			for (int j = 0;j<img->w;j += step)
			{
				Uint32 pixel = ((Uint32*)img->pixels)[i*img->pitch / 4 + j];
				Uint8 r, g, b;
				SDL_GetRGB(pixel, img->format, &r, &g, &b);
				colormap[i][j][0] = (float)r / 255.0;
				colormap[i][j][1] = (float)g / 255.0;
				colormap[i][j][2] = (float)b / 255.0;
			}
		}
	}


	void Map::LoadBuffers(int block, int h) {
		m_meshResolution = heights.size();
		size = m_meshResolution * m_meshResolution * 2 * 3 * 3;

		int divider = block;
		int height = divider*h;

		positions = new float[size]();
		colors = new float[size]();

		double triangleWidth = 2 / m_meshResolution;
		//float startX = -((float)heights.size()*block/2);
		//float startZ = -((float)heights.size()*block/ 2);
		float startX = 0;
		float startZ = 0;
		float x1 = 0;
		float x2 = 0;
		float z1 = 0;
		float z2 = 0;


		int index = 0;
		//For each row
		for (int r = 0; r < heights.size() - 1; r++) {
			//For each column
			for (int c = 0; c < heights[0].size() - 1; c++) {

				x1 = startX + c*divider;
				x2 = startX + (c + 1)*divider;

				z1 = startZ + r*divider;
				z2 = startZ + (r + 1)*divider;
			
				

				//Generate one triangle
				positions[index++] = x1;
					colors[index] = colormap[c][r][1];	//r
				positions[index++] = height*heights[c][r];
					colors[index] = colormap[c][r][2];	//g
				positions[index++] = z1;
					colors[index] = colormap[c][r][0];	//b
					//colors[index+1] = 1;	//alpha



				positions[index++] = x2;
					colors[index] = colormap[c + 1][r + 1][1];
				positions[index++] = height*heights[(c + 1)][(r + 1)];
					colors[index] = colormap[c + 1][r + 1][2];
				positions[index++] = z2;
					colors[index] = colormap[c + 1][r + 1][0];
					//colors[index + 1] = 1;	//alpha

				positions[index++] = x2;
					colors[index] = colormap[c + 1][r][1];
				positions[index++] = height*heights[(c + 1)][r];
					colors[index] = colormap[c + 1][r][2];
				positions[index++] = z1;
					colors[index] = colormap[c + 1][r][0];
					//colors[index + 1] = 1;	//alpha


				//Generate other triangle
				positions[index++] = x1;
					colors[index] = colormap[c][r][1];
				positions[index++] = height*heights[c][r];
					colors[index] = colormap[c][r][2];
				positions[index++] = z1;
					colors[index] = colormap[c][r][0];
					//colors[index + 1] = 1;	//alpha

				positions[index++] = x1;
					colors[index] = colormap[c][r + 1][1];
				positions[index++] = height*heights[c][(r + 1)];
					colors[index] = colormap[c][r + 1][2];
				positions[index++] = z2;
					colors[index] = colormap[c][r + 1][0];
					//colors[index + 1] = 1;	//alpha


				positions[index++] = x2;
					colors[index] = colormap[c + 1][r + 1][1];
				positions[index++] = height*heights[(c + 1)][(r + 1)];
					colors[index] = colormap[c + 1][r + 1][2];
				positions[index++] = z2;
					colors[index] = colormap[c + 1][r + 1][0];
					//colors[index + 1] = 1;	//alpha

			}
		}
	}


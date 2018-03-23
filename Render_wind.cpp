// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 
//------------------------------------------------------------------

#include "Render_wind.h"


	//----------------------------------------------------------------------------------------------
	Render_wind::Render_wind(const char *name, int width, int height) :
		p_name(name), p_width(width), p_height(height)
	{
		if (!init()) {
			SDL_Quit();
			glfwTerminate();
		}
	}
	//----------------------------------------------------------------------------------------------

	Render_wind::~Render_wind()
	{
		close();
	}
	//----------------------------------------------------------------------------------------------
	/*
	SDL_Surface Render_wind::GetScreen() {
		return *p_screen;
	}
*/
	bool Render_wind::init() {

		SDL_Init(SDL_INIT_EVERYTHING);
		set();

		p_window = SDL_CreateWindow(
			"My Game",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			p_width,
			p_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
		glEnable(SDL_WINDOW_ALLOW_HIGHDPI);
		//p_screen = SDL_GetWindowSurface(p_window);


		if (!glfwInit()) {
			std::cout << "Failed to load glfw" << std::endl;
			return false;
		}
		glewExperimental = GL_TRUE;
		if (!glewInit()) {
			std::cout << "Failed to open glew" << std::endl;
			return false;
		}
		else std::cout << "Succes!" << std::endl;

		if (!p_window) {
			glfwTerminate();
			SDL_Quit();
			std::cout << "Failed to open window!" << std::endl;
			return false;
		}

		SDL_GL_SetSwapInterval(1);

		maincontext = SDL_GL_CreateContext(p_window);


		return true;
	}
	//----------------------------------------------------------------------------------------------
	void Render_wind::set() {
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 4);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


		//SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

		

		//renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);
		//SDL_RenderSetLogicalSize(renderer, p_width,p_height);
	}
	
	void Render_wind::clear() const {
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Render_wind::update() {
		SDL_GL_SwapWindow(p_window);
	}

	void Render_wind::Set_Perspective() const {

		gluPerspective(800.f, 1.f, 100.f, 1000.0f);//fov, aspect, zNear, zFar
	}

	void Render_wind::close() const {
		SDL_GL_DeleteContext(maincontext);
		SDL_Quit();
	}
	//----------------------------------------------------------------------------------------------

	
	// metoda ³adowania 

	float ilosc = 0;
	float cx = 1;
	float cy = 1;
	float r = 0.5;
	float r1 = 0.5;
	int num_segments = 0;
	float color = 0.0f;

	void Render_wind::LoadingScreen() {


		glPushMatrix();
		glTranslated(-1, -1, 0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < num_segments; i++)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 

			float x = r * cosf(theta);//calculate the x component 
			float y = r * sinf(theta);//calculate the y component 

			glColor3f(255, color, color);
			glVertex3f(x + cx, y + cy, -10);//output vertex 

		}
		glLineWidth(50);
		glEnd();



		if (ilosc < 100) {
			ilosc += 0.015;
			r += 0.0003;
			color += 0.00035;
		}
		num_segments = ilosc;
		glPopMatrix();

	}

	void Render_wind::RenderStatsFuel(Player* player) {

		glPushMatrix();

		glTranslated(-8, 4.2, -10);
		if((int)player->GetFuel()>0)
		glBegin(GL_QUADS);
		glColor3d(200, 0, 0);

		glVertex3d(0, 0.3, 0);
		glVertex3d(1, 0.3, 0);
		glVertex3d(0.5, 0, 0);
		glVertex3d(0, 0, 0);
		
		glEnd();

		for (int i = 0;i < (int)player->GetFuel();i++) {
			glBegin(GL_QUADS);

			glColor3d(255 - i * 55, i * 55, 0);

			glVertex3d(1 + 0.5*i, 0.3, 0);
			glVertex3d(1.5 + 0.5*i, 0.3, 0);
			glVertex3d(1 + 0.5*i, 0, 0);
			glVertex3d(0.5 + 0.5*i, 0, 0);
			glEnd();
		}



		glPopMatrix();
	}

	void Render_wind::RenderStatsLife(Player* player) {

		glPushMatrix();

		glTranslated(8, 4.2, -10);

		if ((int)player->GetHealth() > 0)
		{
			glBegin(GL_QUADS);
			glColor3d(200, 0, 0);

			glVertex3d(0, 0.3, 0);
			glVertex3d(-1, 0.3, 0);
			glVertex3d(-0.5, 0, 0);
			glVertex3d(0, 0, 0);
			glEnd();
		}

		for (int i = 0;i < (int)player->GetHealth() ;i++) {
			glBegin(GL_QUADS);
			glColor3d(255 - i * 20,0, 0);
			glVertex3d(-1 - 0.5*i, 0.3, 0);
			glVertex3d(-1.5 - 0.5*i, 0.3, 0);
			glVertex3d(-1 - 0.5*i, 0, 0);
			glVertex3d(-0.5 - 0.5*i, 0, 0);
			glEnd();
		}

		

		glPopMatrix();
	}
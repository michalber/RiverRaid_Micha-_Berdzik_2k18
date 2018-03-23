// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#include "Player.h"
#include <iostream>

Player::Player()
{
	playPitch = 0;
	playYaw = 0;
	movevel = 1;
	mousevel = 0.2;
	ismoved = false;
}

Player::~Player()
{
}

void Player::LoadPlayer()
{
	glBegin(GL_TRIANGLE_STRIP);
	
	glColor3f(0.6f,0.0f,0.0f);

	glVertex3f(0,0,0);
	glVertex3f(-5, -12, 0);
	glVertex3f(0, -8, 2);

	glVertex3f(0, -8, 2);
	glVertex3f(0, 0, 0);
	glVertex3f(5, -12, 0);

	glColor3f(0.1f, 0.1f, 0.1f);
	glVertex3f(5, -12, 0);
	glVertex3f(0, -10, 0);
	glVertex3f(0, -8, 2);

	glColor3f(0.1f, 0.1f, 0.1f);
	glVertex3f(0, -8, 2);
	glVertex3f(-5, -12, 0);
	glVertex3f(0, -10, 0);

	glEnd();

}

void Player::RenderPlayer(Map *mapa) {

	Control();
	bullets.update(this->GetSpeed());

	if (loc.x > 0 && loc.x < 150000 && loc.z>0 && loc.z < 150000) {
		CheckCollision(mapa);
	}
	glPushMatrix();
	//ustawienie pozycji
	glTranslatef(0, -8, -45);		// lewo-prawo, góra-gó³, bli¿ej-dalej
	glRotatef(80, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glRotatef(180, 0, 0, 1);
	
	//---------------
	//rotacja wzgledem poruszania sie
	glRotatef(RotPitch, 1, 0, 0);
	glRotatef(-RotYaw, 0, 1, 0);
	//---------------------
	if (playPitch != 90 && playPitch != -90)
		moveCamera(0.0);
	moveCameraUp(0.0);

	LoadPlayer();
	glPopMatrix();
	UpdateCamera();
	
	//std::cout << "Player Y "<<playYaw << std::endl;
	//std::cout << "Player P "<<playPitch << std::endl;
	//std::cout << " " << std::endl;

}

void Player::lockCamera()
{
	if (playPitch>90)
		playPitch = 90;
	if (playPitch<-90)
		playPitch = -90;
	if (playYaw<0.0)
		playYaw = 360.0;
	if (playYaw>360.0)
		playYaw -= 360;
}

void Player::moveCamera(float dir)
{
	float rad = (playYaw + dir)*M_PI / 180.0;
	loc.x -= sin(rad)*movevel;
	loc.z -= cos(rad)*movevel;
}

void Player::moveCameraUp(float dir)
{
	float rad = (playPitch + dir)*M_PI / 180.0;
	loc.y += sin(rad)*movevel;
}

void Player::Control()
{

	int MidX = 1280 / 2;
	int MidY = 720 / 2;

	SDL_ShowCursor(SDL_DISABLE);

	SDL_GetGlobalMouseState(&tmpx, &tmpy);
	playYaw += mousevel*(MidX - tmpx);
	playPitch += mousevel*(MidY - tmpy);
	Fuel-=0.0018;

#pragma region Modulacja Obrotu
	RotPitch += mousevel*(MidY - tmpy);
	if(RotPitch > 30)
		RotPitch = 30;
	if (RotPitch < -20)
		RotPitch = -20;
	RotPitch = RotPitch / 1.2;
	RotYaw += mousevel*(MidX - tmpx);
	if (RotYaw > 35) RotYaw = 35;
	if (RotYaw < -35) RotYaw = -35;
	if ((MidX-tmpx) == 0 && RotYaw < 0) if(RotYaw<=0) RotYaw += 3;
	if ((MidX-tmpx) == 0 && RotYaw > 0) if(RotYaw >= 0) RotYaw -= 3;
#pragma endregion
	
	//lockCamera();
	SDL_WarpMouseGlobal(MidX, MidY);

#pragma region Reakcja na klawisze

	const sf::Uint8* state = SDL_GetKeyboardState(NULL);
	const sf::Uint32 state_mouse = SDL_GetGlobalMouseState(NULL,NULL);

	ismoved = false;
	if (state[SDL_SCANCODE_W])
	{
		movevel += 0.1;
		ismoved = true;
		//if (playPitch != 90 && playPitch != -90)
		//	moveCamera(0.0);
		//moveCameraUp(0.0);
	}
	else if (state[SDL_SCANCODE_S])
	{
		movevel -= 0.1;
		ismoved = true;
		//if (playPitch != 90 && playPitch != -90)
		//	moveCamera(180.0);
		//moveCameraUp(180.0);
	}
	if (state[SDL_SCANCODE_A])
	{
		ismoved = true;
		moveCamera(90.0);
	}
	else if (state[SDL_SCANCODE_D])
	{
		ismoved = true;
		moveCamera(270);
	}
	if (state_mouse && SDL_BUTTON_LEFT) {
		bullets.Add(this->getLocation(),this->getVector(),this->GetYaw(),this->GetPitch());
		//bullets.Add(this->getVector(), this->GetYaw(), this->GetPitch());

	}
#pragma endregion
	
}

void Player::UpdateCamera()
{
	//glRotatef(90, 0, 1, 0);
	glRotatef(-playPitch, 1.0, 0.0, 0.0);
	glRotatef(-playYaw, 0.0, 1.0, 0.0);
	glTranslatef(-loc.x, -loc.y, -loc.z);
}

vector3d Player::getLocation()
{
	return loc;
}

void Player::CheckCollision(Map *mapa) {

	if (loc.x < 10) loc.changeX(10);
	if (loc.z < 10) loc.changeZ(10);


	if ((loc.y / (100*120)) < (mapa->GetValue(floor(loc.x / 100), floor(loc.z / 100)))	) {

		Health-=0.2;
		if (Health < 0) Health = 0;
		
		
		loc.changeY(120*100 * (mapa->GetValue(floor(loc.x / 100), floor(loc.z / 100))));
	}


}

int Player::GetHealth() {
	return Health;
}
int Player::GetFuel() {
	return Fuel;
}
float Player::GetYaw() {
	return playYaw;
}
float Player::GetPitch() {
	return playPitch;
}
float Player::GetSpeed() {
	return movevel;
}
vector3d Player::getVector()
{
	return (vector3d(-cos(playPitch*M_PI / 180.0)*sin(playYaw*M_PI / 180.0), sin(playPitch*M_PI / 180.0), -cos(playPitch*M_PI / 180.0)*cos(playYaw*M_PI / 180.0)+45));
}
// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#include "Missiles.h"

Missiles::Missiles()
{
	frequency = sf::milliseconds(100);
	infinite = true;
	ammunition = 500;
}

Missiles::~Missiles()
{
}

void Missiles::Add(vector3d pos,vector3d vec,float Yaw,float Pitch) {
	SingleBullet a;
	a.loc = pos;
	a.loc_buff = vec;
	a.Yaw = Yaw;
	a.Pitch = Pitch;


	if (timer.getElapsedTime() >= frequency && (ammunition >= 0 || infinite))
	{
		p_bullets.push_back(a);
		factor.push_back(pos);
		timer.restart();
		if (!infinite) ammunition--;
	}
}

void Missiles::update(float vel) {

	for (int i = 0;i < p_bullets.size();i++) {
		p_bullets[i].speed = vel;
		if (abs(p_bullets[i].loc_buff.x - p_bullets[i].loc.x) > 100 ||
			abs(p_bullets[i].loc_buff.y - p_bullets[i].loc.y) > 100 ||
			abs(p_bullets[i].loc_buff.z - p_bullets[i].loc.z) > 100) {
			remove(i);
		}
	}

}
void Missiles::remove(int it)
{
	for (int i = it;i<p_bullets.size() - 1;i++)
	{
		std::swap(p_bullets[i], p_bullets[i + 1]);
	}
	p_bullets.resize(factor.size());
}

void Missiles::render() {
	for (int i = 0; i < p_bullets.size();i++) {
		p_bullets[i].Make();
	}
}

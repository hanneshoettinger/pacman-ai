#include "stdafx.h"
#include "AI.h"

// shadow ghost logic -> set target to pac position
void shadow_logic(Ghosts *shadow, Pac *pacman)
{
	// set shadow to pac pos
	shadow->targetx = pacman->getposx();
	shadow->targety = pacman->getposy();
}

// speedy ghost logic -> set target to pac direction, 4 fields ahead
void speedy_logic(Ghosts *speedy, Pac *pacman)
{
	// speedy target with offset -> offset = direction of pacman
	int OffsetX = pacman->getdirx() * 4;
	int OffsetY = pacman->getdiry() * 4;

	speedy->targetx = pacman->getposx() + OffsetX;
	speedy->targety = pacman->getposy() + OffsetY;
}

// pokey ghost logic -> either pacman location or home tile
void pokey_logic(Ghosts *pokey, Pac *pacman)
{
	// check if pokey is near to pacman
	int dx = pokey->getposx() - pacman->getposx();
	int dy = pokey->getposy() - pacman->getposy();

	// compare if pokey is farther than 8 fields
	int distance = dx * dx + dy * dy;
	if (distance >= (64))
	{
		// set pokey to pac pos
		pokey->targetx = pacman->getposx();
		pokey->targety = pacman->getposy();
	}
	else   // if closer -> send home
	{
		// send home -> southwest corner
		pokey->targetx = 1;
		pokey->targety = 29;
	}
}

// bashful ghost logic -> considers shadow's location and the location of pacman two fields ahead
void bashful_logic(Ghosts *bashful, Ghosts *shadow, Pac *pacman)
{
	// bashful target with offset -> check pacman direction
	int OffsetX = pacman->getdirx() * 2;
	int OffsetY = pacman->getdiry() * 2;

	// so set the first target tile -> the pacman two fields ahead
	int tx = pacman->getposx() + OffsetX;
	int ty = pacman->getposy() + OffsetY;
	// now check shadows position
	int sx = shadow->getposx();
	int sy = shadow->getposy();
	// set the target -> line two fields ahead of pac and line from shadow to this tile, doubled
	bashful->targetx = 2 * tx - sx;
	bashful->targety = 2 * ty - sy;
}

// to check if the next tile is a wall
std::string gamestuff = "ijIJklKLmnMNopOPqrQR.* ";

// calculate next direction
Direction ghostDirection(Ghosts *ghost, char (&GameMap)[28][31], int setdir)
{
	GhostTarget targets[4] = { { Up, INT_MAX },{ Left, INT_MAX },{ Down, INT_MAX },{ Right, INT_MAX } };
	BoardDirection offsets[4] = { { 0, -1 },{ -1, 0 },{ 0, 1 },{ 1, 0 } };

	// calculate distance for all possible directions
	for (int i = 0; i < 4; i++) {
		// get next position of current direction
		int nextDirX = ghost->getposx() + offsets[i].x; 
		int nextDirY = ghost->getposy() + offsets[i].y;

		// check if going into tunnel
		if (nextDirX == -1) { nextDirX = 27; }
		if (nextDirX == 28) { nextDirX = 0; }

		// check if the current direction would lead into a wall, if yes -> continue loop
		if (!(gamestuff.find(GameMap[nextDirX][nextDirY]) != std::string::npos)) {continue;}

		// if next direction is valid, calculate the difference to set distance
		int dx = nextDirX - ghost->targetx;
		int dy = nextDirY - ghost->targety;

		targets[i].distance = (dx * dx + dy * dy);
	}

	//exclude opposite direction
	Direction reverseDir;
	if (ghost->getdirx() == 0 & ghost->getdiry() == -1) { reverseDir = Down; }
	else if (ghost->getdirx() == 1 & ghost->getdiry() == 0) { reverseDir = Left; }
	else if (ghost->getdirx() == 0 & ghost->getdiry() == 1) { reverseDir = Up; }
	else if (ghost->getdirx() == -1 & ghost->getdiry() == 0) { reverseDir = Right; }

	// start with right to calculate shortest direction
	GhostTarget shortest = { Right, INT_MAX };

	//iterate over the possible distances to set best direction
	for (int i = 3; i >= 0; i--) {
		if (targets[i].dir == reverseDir) { continue; }

		if (targets[i].distance <= shortest.distance) {
			shortest.distance = targets[i].distance;
			shortest.dir = targets[i].dir;
		}
	}

	// if flag is set to 1 update the calculated ghosts direction
	if (setdir == 1)
	{
		if (shortest.dir == Up) { ghost->setdir(0, -1); }
		else if (shortest.dir == Down) { ghost->setdir(0, 1); }
		else if (shortest.dir == Left) { ghost->setdir(-1, 0); }
		else if (shortest.dir == Right) { ghost->setdir(1, 0); }
	}
	// return shortest direction...
	return shortest.dir;
}

// very simple PacMan AI
Direction pacDirection(Pac *pac, char(&GameMap)[28][31], Ghosts *shadow, Ghosts *speedy, Ghosts *bashful, Ghosts* pokey)
{
	
	int pacx = pac->getposx();
	int pacy = pac->getposy();

	int shx = pacx - shadow->getposx();
	int shy = pacy - shadow->getposy();

	int spx = pacx - speedy->getposx();
	int spy = pacy - speedy->getposy();

	int bax = pacx - bashful->getposx();
	int bay = pacy - bashful->getposy();

	int pox = pacx - pokey->getposx();
	int poy = pacy - pokey->getposy();

	// calculate the distance from pac to ghosts
	PacTarget pactargetdist[4] = { {shadow,shx*shx +shy*shy},{speedy,spx*spx+spy*spy},{bashful,bax*bax+bay*bay},{pokey,pox*pox+poy*poy} };
	// first update with pokey
	PacTarget shorttarget = {pokey, INT_MAX};
	// calculate which ghosts is close
	for (int i = 3; i >= 0; i--)
	{
		if (pactargetdist[i].distance <= shorttarget.distance)
		{
			shorttarget.distance = pactargetdist[i].distance;
			shorttarget.ghost = pactargetdist[i].ghost;
		}
	}
	
	// set new target considering the closest ghost
	//pac->targetx = shorttarget.ghost->getposx() + 3*shorttarget.ghost->getdirx();
	//pac->targety = shorttarget.ghost->getposy() + 3*shorttarget.ghost->getdiry();
	pac->targetx = rand() % 28 - shorttarget.ghost->getposx();
	pac->targety = rand() % 30 - shorttarget.ghost->getposy();
		 
	// calculate the next direction, like ghosts direction...

	GhostTarget targets[4] = { { Up, INT_MAX },{ Left, INT_MAX },{ Down, INT_MAX },{ Right, INT_MAX } };
	BoardDirection offsets[4] = { { 0, -1 },{ -1, 0 },{ 0, 1 },{ 1, 0 } };

	// calculate distance
	for (int i = 0; i < 4; i++)
	{
		// get next direction
		int nextDirX = pac->getposx() + offsets[i].x;
		int nextDirY = pac->getposy() + offsets[i].y;

		//tunnel
		if (nextDirX == -1) { nextDirX = 27; }
		if (nextDirX == 28) { nextDirX = 0; }

		// check if empty field or other ghost/pac, if not...
		if (!(gamestuff.find(GameMap[nextDirX][nextDirY]) != std::string::npos)) { continue; }

		int dx = nextDirX - pac->targetx;
		int dy = nextDirY - pac->targety;

		targets[i].distance = (dx * dx + dy * dy);
	}

	//exclude opposite direction
	Direction reverseDir;
	if (pac->getdirx() == 0 & pac->getdiry() == -1) { reverseDir = Down; }
	else if (pac->getdirx() == 1 & pac->getdiry() == 0) { reverseDir = Left; }
	else if (pac->getdirx() == 0 & pac->getdiry() == 1) { reverseDir = Up; }
	else if (pac->getdirx() == -1 & pac->getdiry() == 0) { reverseDir = Right; }

	GhostTarget shortest = { Right, INT_MAX };

	//iterate backwards
	for (int i = 3; i >= 0; i--) {
		if (targets[i].dir == reverseDir) { continue; }

		if (targets[i].distance <= shortest.distance) {
			shortest.distance = targets[i].distance;
			shortest.dir = targets[i].dir;
		}
	}

	if (shortest.dir == Up) { pac->setdir(0, -1); }
	else if (shortest.dir == Down) { pac->setdir(0, 1); }
	else if (shortest.dir == Left) { pac->setdir(-1, 0); }
	else if (shortest.dir == Right) { pac->setdir(1, 0); }

	return shortest.dir;
}
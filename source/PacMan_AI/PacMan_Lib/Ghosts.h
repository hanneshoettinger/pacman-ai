#pragma once
class Ghosts
{

private:
	int posx;
	int posy;
	int oldposx;
	int oldposy;
	int dirx;
	int diry;

public:
	Ghosts();
	~Ghosts();

	int getposx() { return posx; };
	int getposy() { return posy; };
	int getoldposx() { return oldposx; };
	int getoldposy() { return oldposy; };
	int getdirx() { return dirx; };
	int getdiry() { return diry; };
	int getnewposx() { return (posx + dirx); };
	int getnewposy() { return (posy + diry); };

	void setpos(int x, int y) { posx = x; posy = y; };
	void setoldpos(int x, int y) { oldposx = x; oldposy = y; };
	void setdir(int dx, int dy) { dirx = dx; diry = dy; };

	int targetx;
	int targety;

	// collider and tunnel function also here
};


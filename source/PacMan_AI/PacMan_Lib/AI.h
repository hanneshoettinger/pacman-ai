#pragma once

typedef struct
{
	int x;
	int y;
} BoardDirection;

typedef enum
{
	Up,
	Down,
	Left,
	Right
} Direction;

typedef struct
{
	Direction dir;
	int distance;
} GhostTarget;

typedef struct
{
	Ghosts *ghost;
	int distance;
} PacTarget;

void shadow_logic(Ghosts *shadow, Pac *pacman);
void speedy_logic(Ghosts *speedy, Pac *pacman);
void pokey_logic(Ghosts *pokey, Pac *pacman);
void bashful_logic(Ghosts *bashful, Ghosts *shadow, Pac *pacman);

Direction ghostDirection(Ghosts *ghost, char (&GameMap)[28][31], int setdir);
Direction pacDirection(Pac *pac, char(&GameMap)[28][31], Ghosts *shadow, Ghosts *speedy, Ghosts *bashful, Ghosts* pokey);
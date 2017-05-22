// PacMan_AI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sprites.h"

// init Standard Map Size
const int mapwidth = 28;
const int mapheight = 31;

int reccounter = 0;

std::string ghoststuff = "klKLmnMNopOPqrQR";
std::string pacstuff = "ijIJ";

// Create Render Windows
sf::RenderWindow window(sf::VideoMode(448, 496), "PacMan - SMFL");

// init GameMode
std::string GameMode;
std::size_t foundState;

// Sprite Object
Sprites sp;

// init GameMap
char GameMap[mapwidth][mapheight];

// Prototypes
void fillGameMap(std::string &boardStr);
void printMap();
void UpdateGhostsTarget();
void UpdateGhostsDirection();
void MoveGhosts();
void MovePac();
void saveBoard();

// init Pacman and Ghosts
Pac pac;
Ghosts shadow;
Ghosts speedy;
Ghosts bashful;
Ghosts pokey;

// Console Color Function
char Color(int color = 7, char Message = ' ') {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return Message;
}

int main(int argc, char *argv[])
{
	// setup the console window********************
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	// setup console windows
	MoveWindow(console, r.left, r.top, 300, 600, TRUE); // 800 width, 100 height

	// INIT -> check Input Arguments and FileIO****
	int check = checkInputs(argc, argv);
	system("CLS");
	if (check == 0) { 
	// set standard value for input
		inputFile = "TestMap.txt";
	}
	// input file from .txt file 
	std::string boardStr = FileIO::getFileContents();
	// check GameMode -> call with reference
	FileIO::checkGameMode(boardStr, GameMode, foundState);
	// fill GameMap with txt Data and set init position of the pac and ghosts
	fillGameMap(boardStr);

	// load the textures and sprites
	sp.InitTextures(); 

	// check which game mode
	if (GameMode == "patrol")
	{
		// go to home corner then patrol
		// send home -> northwest corner
		shadow.targetx = 26;
		shadow.targety = 2;
		// send home -> northwest corner
		speedy.targetx = 1;
		speedy.targety = 1;
		// send home -> southeast corner
		bashful.targetx = 26;
		bashful.targety = 29;
		// send home -> southwest corner
		pokey.targetx = 1;
		pokey.targety = 29;
	}
	else if (GameMode == "escape")
	{
		// escape mode -> reverse dir and set minus position of pac later
		shadow.setdir(shadow.getdirx() * (-1), shadow.getdiry() * (-1));
		speedy.setdir(speedy.getdirx() * (-1), speedy.getdiry() * (-1));
		bashful.setdir(bashful.getdirx() * (-1), bashful.getdiry() * (-1));
		pokey.setdir(pokey.getdirx() * (-1), pokey.getdiry() * (-1));
		// set pac dir
		pac.setdir(pac.getdirx() * (-1), pac.getdiry() * (-1));
	}

	// GameLoop
		//************** AI *********************************************************************
		if (GameMode == "pursuit") {
			// update target location of ghosts
			UpdateGhostsTarget();
		}
		else if (GameMode == "escape")
		{
			// escape mode reverse dir and set minus position of pac
			shadow.targetx = -pac.getposx();
			shadow.targety = -pac.getposy();
			speedy.targetx = -pac.getposx();
			speedy.targety = -pac.getposy();
			bashful.targetx = -pac.getposx();
			bashful.targety = -pac.getposy();
			pokey.targetx = -pac.getposx();
			pokey.targety = -pac.getposy();
		}
		
		// update the direction of the ghosts to target -> every ghost has its own logic
		UpdateGhostsDirection();
		// move pacman automatically with own logic
		MovePac();
		// move ghosts automatically
		MoveGhosts();
		//***************************************************************************************
		// print current map
		printMap();
		// save board to file and update ghosts in board
		saveBoard();

	return 0;
}

// execute ghost logic
void UpdateGhostsTarget()
{
	shadow_logic(&shadow, &pac);

	speedy_logic(&speedy, &pac);

	bashful_logic(&bashful, &shadow, &pac);

	pokey_logic(&pokey, &pac);
}

// update the Direction -> includes collider
void UpdateGhostsDirection()
{
	// check if dead
	if ((pacstuff.find(GameMap[shadow.getposx()][shadow.getposy()]) != std::string::npos)
		| (pacstuff.find(GameMap[speedy.getposx()][speedy.getposy()]) != std::string::npos)
		| (pacstuff.find(GameMap[bashful.getposx()][bashful.getposy()]) != std::string::npos)
		| (pacstuff.find(GameMap[pokey.getposx()][pokey.getposy()]) != std::string::npos)) {
		std::cout << " GAME OVER ";
		window.close();
	}
	// flag -> means to update the direction of the ghost
	ghostDirection(&shadow, GameMap, 1);

	ghostDirection(&speedy, GameMap, 1);

	ghostDirection(&bashful, GameMap, 1);

	ghostDirection(&pokey, GameMap, 1);

	// update Pacman
	pacDirection(&pac, GameMap, &shadow, &speedy, &bashful, &pokey);
}

// Move Ghosts in the World Map
void MoveGhosts()
{
	Ghosts* ghost;   // Pointer of class type
	ghost = &shadow;

	// loop through ghosts 
	for (int i = 0; i < 4; i++)
	{
		if (i == 0) { ghost = &shadow; }
		if (i == 1) { ghost = &speedy; }
		if (i == 2) { ghost = &bashful; }
		if (i == 3) { ghost = &pokey; }

		// set old pos for drawing
		ghost->setoldpos(ghost->getposx(),ghost->getposy());
		
		// check for Game Over
		if (ghost->getposx() == pac.getposx() & ghost->getposy() == pac.getposy()) {
			// stop game
			std::cout << " GAME OVER ";
			window.close();
			break;
		}

		// check if Tunnel and update previous field
		if (ghost->getnewposx() > (mapwidth - 1)) {
			GameMap[ghost->getposx()][ghost->getposy()] = ' ';
			ghost->setpos(-1, 14);
		}
		else if (ghost->getnewposx() < 0) {
			GameMap[ghost->getposx()][ghost->getposy()] = ' ';
			ghost->setpos(28, 14);
		}

		//update ghost character for current direction
		if (ghost->getdirx() == 0 & ghost->getdiry() == 1) {
			GameMap[ghost->getoldposx()][ghost->getoldposy()] = ' '; // change previous 
			switch (i) {
				case 0: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'K'; // update to new pos
					break;
				case 1: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'M'; // update to new pos
					break;
				case 2: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'O'; // update to new pos
					break;
				case 3: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'Q'; // update to new pos
					break;
			}
			// update the position to the new position
			ghost->setpos(ghost->getnewposx(), ghost->getnewposy());
		}
		else if (ghost->getdirx() == 1 & ghost->getdiry() == 0) {
			GameMap[ghost->getoldposx()][ghost->getoldposy()] = ' '; // change previous 
			switch (i) {
			case 0: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'l'; // update to new pos
				break;
			case 1: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'n'; // update to new pos
				break;
			case 2: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'p'; // update to new pos
				break;
			case 3: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'r'; // update to new pos
				break;
			}
			// update the position to the new position
			ghost->setpos(ghost->getnewposx(), ghost->getnewposy());
		}
		else if (ghost->getdirx() == 0 & ghost->getdiry() == -1) {
			GameMap[ghost->getoldposx()][ghost->getoldposy()] = ' '; // change previous 
			switch (i) {
			case 0: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'k'; // update to new pos
				break;
			case 1: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'm'; // update to new pos
				break;
			case 2: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'o'; // update to new pos
				break;
			case 3: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'q'; // update to new pos
				break;
			}
			// update the position to the new position
			ghost->setpos(ghost->getnewposx(), ghost->getnewposy());
		}
		else if (ghost->getdirx() == -1 & ghost->getdiry() == 0) {
			GameMap[ghost->getoldposx()][ghost->getoldposy()] = ' '; // change previous 
			switch (i) {
			case 0: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'L'; // update to new pos
				break;
			case 1: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'N'; // update to new pos
				break;
			case 2: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'P'; // update to new pos
				break;
			case 3: GameMap[ghost->getnewposx()][ghost->getnewposy()] = 'R'; // update to new pos
				break;
			}
			// update the position to the new position
			ghost->setpos(ghost->getnewposx(), ghost->getnewposy());
		}
	}
}

// Move Pacman
void MovePac()
{
	// check if previous field was no ghost and update with empty field
	if (!(ghoststuff.find(GameMap[pac.getposx()][pac.getposy()]) != std::string::npos)) {
		GameMap[pac.getposx()][pac.getposy()] = ' '; // change previous 
	}
	else  //dead
	{
		std::cout << " GAME OVER ";
		window.close();
	}
	
	// check tunnel
	if (pac.getnewposx() > (mapwidth - 1)) {
		pac.setpos(-1, 14);
	}
	else if (pac.getnewposx() < 0) {
		pac.setpos(28, 14);
	}

	//update pac character for the current direction and set new position
	if (pac.getdirx() == 0 & pac.getdiry() == 1) {
		GameMap[pac.getnewposx()][pac.getnewposy()] = 'I';
		pac.setpos(pac.getnewposx(), pac.getnewposy());
	}
	else if (pac.getdirx() == 1 & pac.getdiry() == 0) {
		GameMap[pac.getnewposx()][pac.getnewposy()] = 'j';
		pac.setpos(pac.getnewposx(), pac.getnewposy());
	}
	else if (pac.getdirx() == 0 & pac.getdiry() == -1) {
		GameMap[pac.getnewposx()][pac.getnewposy()] = 'i';
		pac.setpos(pac.getnewposx(), pac.getnewposy());
	}
	else if (pac.getdirx() == -1 & pac.getdiry() == 0) {
		GameMap[pac.getnewposx()][pac.getnewposy()] = 'J';
		pac.setpos(pac.getnewposx(), pac.getnewposy());
	}
}

// fills the GameMap with given input Data
void fillGameMap(std::string &boardStr)
{
	int x = 0;
	int y = 0;
	// fill GameMap -> start at first \n + 1, as written in the MUST-Haves
	std::string::iterator it;
	for (it = boardStr.begin() + (foundState + GameMode.length() + 2); it < boardStr.end(); it++) {
		if (*it == '\n'){
			y++;
			x = 0;
		}
		else if (x < 28){
			GameMap[x][y] = *it;
			// set initial position and direction of the pac and the ghosts
			switch (GameMap[x][y])
			{
				case 'i': 
				case 'j':
				case 'I': 
				case 'J': 
					pac.setpos(x, y);
					if (GameMap[x][y] == 'i'){ pac.setdir(0, -1); }
					else if (GameMap[x][y] == 'j') { pac.setdir(1, 0); }
					else if (GameMap[x][y] == 'I') { pac.setdir(0, 1); }
					else if (GameMap[x][y] == 'J') { pac.setdir(-1, 0); }
					break;
				case 'k': 
				case 'l': 
				case 'K':
				case 'L': 
					shadow.setpos(x, y);
					if (GameMap[x][y] == 'k') { shadow.setdir(0, -1); }
					else if (GameMap[x][y] == 'l') { shadow.setdir(1, 0); }
					else if (GameMap[x][y] == 'K') { shadow.setdir(0, 1); }
					else if (GameMap[x][y] == 'L') { shadow.setdir(-1, 0); }
					break;
				case 'm': 
				case 'n':
				case 'M': 
				case 'N': 
					speedy.setpos(x, y);
					if (GameMap[x][y] == 'm') { speedy.setdir(0, -1); }
					else if (GameMap[x][y] == 'n') { speedy.setdir(1, 0); }
					else if (GameMap[x][y] == 'M') { speedy.setdir(0, 1); }
					else if (GameMap[x][y] == 'N') { speedy.setdir(-1, 0); }
					break;
				case 'o': 
				case 'p': 
				case 'O':
				case 'P':
					bashful.setpos(x, y);
					if (GameMap[x][y] == 'o') { bashful.setdir(0, -1); }
					else if (GameMap[x][y] == 'p') { bashful.setdir(1, 0); }
					else if (GameMap[x][y] == 'O') { bashful.setdir(0, 1); }
					else if (GameMap[x][y] == 'P') { bashful.setdir(-1, 0); }
					break;
				case 'q':
				case 'r':
				case 'Q':
				case 'R':
					pokey.setpos(x, y);
					if (GameMap[x][y] == 'q') { pokey.setdir(0, -1); }
					else if (GameMap[x][y] == 'r') { pokey.setdir(1, 0); }
					else if (GameMap[x][y] == 'Q') { pokey.setdir(0, 1); }
					else if (GameMap[x][y] == 'R') { pokey.setdir(-1, 0); }
					break;
				default:
					break;
			}
			// increment x, can only be max. 27 (GameMap Size...)
			x++;
		}
	}
}
/*black = 0,dark_blue = 1,dark_green = 2,dark_aqua, dark_cyan = 3,
dark_red = 4,dark_purple = 5, dark_pink = 5, dark_magenta = 5,
dark_yellow = 6,dark_white = 7,gray = 8,blue = 9,
green = 10,aqua = 11, cyan = 11,red = 12,purple = 13, pink = 13, magenta = 13,yellow = 14,white = 15*/
// print the world map with color function in command line
void printMap()
{
	// set cursor to position 0,0 to plot everytime over existing board
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 0, 0 };
	SetConsoleCursorPosition(hStdout, position);

	for (int j = 0; j < mapheight; j++)
	{
		for (int i = 0; i < mapwidth; i++)
		{
			switch (GameMap[i][j])
			{
			case 'i': case 'j': case 'I': case 'J':
				std::cout << Color(14, GameMap[i][j]);
				break;
			case 'k': case 'l': case 'K': case 'L':
				std::cout << Color(12, GameMap[i][j]);
				break;
			case 'm': case 'n': case 'M': case 'N':
				std::cout << Color(13, GameMap[i][j]);
				break;
			case 'o': case 'p': case 'O': case 'P':
				std::cout << Color(9, GameMap[i][j]);
				break;
			case 'q': case 'r': case 'Q': case 'R':
				std::cout << Color(6, GameMap[i][j]);
				break;
			case '-':
				std::cout << Color(5, GameMap[i][j]);
				break;
			case '.': case '*':
				std::cout << Color(6, GameMap[i][j]);
				break;
			default:
				std::cout << Color(1, GameMap[i][j]);
				break;
			}
			Color(7,' '); //Sets the color to default
		}
		std::cout << std::endl;
	}
}

// SMFL save Screenshot of Board -> prints the Board with the correct Tiles
void saveBoard()
{
	window.clear();

	Direction check;

	for (int y = 0; y < mapheight; y++)
	{
		for (int x = 0; x < mapwidth; x++)
		{
			switch (GameMap[x][y])
			{
			case 'i':
			case 'j':
			case 'I':
			case 'J':
				if (GameMap[x][y] == 'i') { sp.pacup.setPosition(x * 16, y * 16); window.draw(sp.pacup); }
				else if (GameMap[x][y] == 'j') { sp.pacright.setPosition(x * 16, y * 16); window.draw(sp.pacright); }
				else if (GameMap[x][y] == 'I') { sp.pacdown.setPosition(x * 16, y * 16); window.draw(sp.pacdown); }
				else if (GameMap[x][y] == 'J') { sp.pacleft.setPosition(x * 16, y * 16); window.draw(sp.pacleft); }
				break;
			case 'k':
			case 'l':
			case 'K':
			case 'L':
				// draw old pos
				sp.shadowsprite.setPosition(shadow.getoldposx()*16,shadow.getoldposy()*16);
				window.draw(sp.shadowsprite);

				if (GameMode == "escape")
				{
					sp.escapesprite.setPosition(x * 16, y * 16);
					window.draw(sp.escapesprite);
				}
				else
				{
					sp.shadowsprite.setPosition(x * 16, y * 16);
					window.draw(sp.shadowsprite);

					check = ghostDirection(&shadow, GameMap, 0);  // check only next direction without setting the new dir

					if (check == Up) { sp.eyesup.setPosition(x * 16, y * 16); window.draw(sp.eyesup); }
					else if (check == Right) { sp.eyesright.setPosition(x * 16, y * 16); window.draw(sp.eyesright); }
					else if (check == Down) { sp.eyesdown.setPosition(x * 16, y * 16); window.draw(sp.eyesdown); }
					else if (check == Left) { sp.eyesleft.setPosition(x * 16, y * 16); window.draw(sp.eyesleft); }
				}
				break;
			case 'm':
			case 'n':
			case 'M':
			case 'N':
				// draw old pos
				sp.speedysprite.setPosition(speedy.getoldposx() * 16, speedy.getoldposy() * 16);
				window.draw(sp.speedysprite);

				if (GameMode == "escape")
				{
					sp.escapesprite.setPosition(x * 16, y * 16);
					window.draw(sp.escapesprite);
				}
				else
				{
					sp.speedysprite.setPosition(x * 16, y * 16);
					window.draw(sp.speedysprite);
					check = ghostDirection(&speedy, GameMap, 0);  // check only next direction without setting the new dir

					if (check == Up) { sp.eyesup.setPosition(x * 16, y * 16); window.draw(sp.eyesup); }
					else if (check == Right) { sp.eyesright.setPosition(x * 16, y * 16); window.draw(sp.eyesright); }
					else if (check == Down) { sp.eyesdown.setPosition(x * 16, y * 16); window.draw(sp.eyesdown); }
					else if (check == Left) { sp.eyesleft.setPosition(x * 16, y * 16); window.draw(sp.eyesleft); }
				}
				break;
			case 'o':
			case 'p':
			case 'O':
			case 'P':
				// draw old pos
				sp.bashfulsprite.setPosition(bashful.getoldposx() * 16, bashful.getoldposy() * 16);
				window.draw(sp.bashfulsprite);

				if (GameMode == "escape")
				{
					sp.escapesprite.setPosition(x * 16, y * 16);
					window.draw(sp.escapesprite);
				}
				else
				{
					sp.bashfulsprite.setPosition(x * 16, y * 16);
					window.draw(sp.bashfulsprite);
					check = ghostDirection(&bashful, GameMap, 0);  // check only next direction without setting the new dir

					if (check == Up) { sp.eyesup.setPosition(x * 16, y * 16); window.draw(sp.eyesup); }
					else if (check == Right) { sp.eyesright.setPosition(x * 16, y * 16); window.draw(sp.eyesright); }
					else if (check == Down) { sp.eyesdown.setPosition(x * 16, y * 16); window.draw(sp.eyesdown); }
					else if (check == Left) { sp.eyesleft.setPosition(x * 16, y * 16); window.draw(sp.eyesleft); }
				}
				break;
			case 'q':
			case 'r':
			case 'Q':
			case 'R':
				// draw old pos
				sp.pokeysprite.setPosition(pokey.getoldposx() * 16, pokey.getoldposy() * 16);
				window.draw(sp.pokeysprite);

				if (GameMode == "escape")
				{
					sp.escapesprite.setPosition(x * 16, y * 16);
					window.draw(sp.escapesprite);
				}
				else
				{
					sp.pokeysprite.setPosition(x * 16, y * 16);
					window.draw(sp.pokeysprite);
					check = ghostDirection(&pokey, GameMap, 0);  // check only next direction without setting the new dir

					if (check == Up) { sp.eyesup.setPosition(x * 16, y * 16); window.draw(sp.eyesup); }
					else if (check == Right) { sp.eyesright.setPosition(x * 16, y * 16); window.draw(sp.eyesright); }
					else if (check == Down) { sp.eyesdown.setPosition(x * 16, y * 16); window.draw(sp.eyesdown); }
					else if (check == Left) { sp.eyesleft.setPosition(x * 16, y * 16); window.draw(sp.eyesleft); }
				}
				break;
			case 'G':
				sp.corner_bottom_left.setPosition(x * 16, y * 16);
				window.draw(sp.corner_bottom_left);
				break;
			case 'H':
				sp.corner_bottom_right.setPosition(x * 16, y * 16);
				window.draw(sp.corner_bottom_right);
				break;
			case 'E':
				sp.corner_top_left.setPosition(x * 16, y * 16);
				window.draw(sp.corner_top_left);
				break;
			case 'F':
				sp.corner_top_right.setPosition(x * 16, y * 16);
				window.draw(sp.corner_top_right);
				break;
			case '*':
				sp.big_dot.setPosition(x * 16, y * 16);
				window.draw(sp.big_dot);
				break;
			case '.':
				sp.dot_1.setPosition(x * 16, y * 16);
				window.draw(sp.dot_1);
				break;
			case '>':
				sp.gate_left.setPosition(x * 16, y * 16);
				window.draw(sp.gate_left);
				break;
			case '<':
				sp.gate_right.setPosition(x * 16, y * 16);
				window.draw(sp.gate_right);
				break;
			case '-':
				sp.door_1.setPosition(x * 16, y * 16);
				window.draw(sp.door_1);
				break;
			case '8':
				sp.outercorner_bottom_left.setPosition(x * 16, y * 16);
				window.draw(sp.outercorner_bottom_left);
				break;
			case '7':
				sp.outercorner_bottom_right.setPosition(x * 16, y * 16);
				window.draw(sp.outercorner_bottom_right);
				break;
			case '[':
				sp.outercorner_narrow_bottom_left.setPosition(x * 16, y * 16);
				window.draw(sp.outercorner_narrow_bottom_left);
				break;
			case ']':
				sp.outercorner_narrow_bottom_right.setPosition(x * 16, y * 16);
				window.draw(sp.outercorner_narrow_bottom_right);
				break;
			case '1':
				sp.outerwall_top.setPosition(x * 16, y * 16);
				window.draw(sp.outerwall_top);
				break;
			case '2':
				sp.outerwall_right.setPosition(x * 16, y * 16);
				window.draw(sp.outerwall_right);
				break;
			case '3':
				sp.outerwall_bottom.setPosition(x * 16, y * 16);
				window.draw(sp.outerwall_bottom);
				break;
			case '4':
				sp.outerwall_left.setPosition(x * 16, y * 16);
				window.draw(sp.outerwall_left);
				break;
			case '5':
				sp.outercorner_top_left.setPosition(x * 16, y * 16);
				window.draw(sp.outercorner_top_left);
				break;
			case '6':
				sp.outercorner_top_right.setPosition(x * 16, y * 16);
				window.draw(sp.outercorner_top_right);
				break;
			case '(':
				sp.outercorner_narrow_top_left.setPosition(x * 16, y * 16);
				window.draw(sp.outercorner_narrow_top_left);
				break;
			case ')':
				sp.outercorner_narrow_top_right.setPosition(x * 16, y * 16);
				window.draw(sp.outercorner_narrow_top_right);
				break;
			case 'A':
				sp.wall_top.setPosition(x * 16, y * 16);
				window.draw(sp.wall_top);
				break;
			case 'B':
				sp.wall_right.setPosition(x * 16, y * 16);
				window.draw(sp.wall_right);
				break;
			case 'C':
				sp.wall_bottom.setPosition(x * 16, y * 16);
				window.draw(sp.wall_bottom);
				break;
			case 'D':
				sp.wall_left.setPosition(x * 16, y * 16);
				window.draw(sp.wall_left);
				break;
			case 'a':
				sp.outernose_top_left.setPosition(x * 16, y * 16);
				window.draw(sp.outernose_top_left);
				break;
			case 'b':
				sp.outernose_top_right.setPosition(x * 16, y * 16);
				window.draw(sp.outernose_top_right);
				break;
			case 'c':
				sp.outernose_right_top.setPosition(x * 16, y * 16);
				window.draw(sp.outernose_right_top);
				break;
			case 'd':
				sp.outernose_right_bottom.setPosition(x * 16, y * 16);
				window.draw(sp.outernose_right_bottom);
				break;
			case 'e':
				sp.outernose_bottom_left.setPosition(x * 16, y * 16);
				window.draw(sp.outernose_bottom_left);
				break;
			case 'f':
				sp.outernose_bottom_right.setPosition(x * 16, y * 16);
				window.draw(sp.outernose_bottom_right);
				break;
			case 'g':
				sp.outernose_left_top.setPosition(x * 16, y * 16);
				window.draw(sp.outernose_left_top);
				break;
			case 'h':
				sp.outernose_left_bottom.setPosition(x * 16, y * 16);
				window.draw(sp.outernose_left_bottom);
				break;

			default:
				break;
			}
		}
	}

	// take screenshot of the final GameMap with Tiles
	sf::Image screenshot;
	screenshot = window.capture();
	
	window.display();
	
	sf::Event event;
	while (window.isOpen())
	{
		reccounter++;
		if (reccounter == 1) {
			// save Board only of the first Screenshot when moved once
			screenshot.saveToFile("PacMan_Board_OneStep.png");
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//**************AI***********************
		// check the logic again for test purpose and recall the saveBoard function to test full behaviour of ghosts
		// only for testing...
		if (GameMode == "pursuit") {
			// update target location of ghosts
			UpdateGhostsTarget();
		}
		else if (GameMode == "escape")
		{
			// escape mode reverse dir and set minus position of pac
			shadow.targetx = -pac.getposx();
			shadow.targety = -pac.getposy();
			speedy.targetx = -pac.getposx();
			speedy.targety = -pac.getposy();
			bashful.targetx = -pac.getposx();
			bashful.targety = -pac.getposy();
			pokey.targetx = -pac.getposx();
			pokey.targety = -pac.getposy();
		}

		// update the direction of the ghosts to target
		UpdateGhostsDirection();
		//***************************************
		MovePac();
		// move ghosts with collider function
		MoveGhosts();
		// print current map
		printMap();
		// save board to file
		saveBoard();
	}
}
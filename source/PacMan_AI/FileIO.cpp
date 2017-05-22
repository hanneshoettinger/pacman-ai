#include "stdafx.h"
#include "FileIO.h"
#include "InputParser.h"

FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}

// stream input to string from .gol file
std::string FileIO::getFileContents()
{
	std::ifstream in(inputFile, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// save result of generations to outputfile .gol
void FileIO::saveBoardtoFile(char *boardArr, int &bheight, int &bwidth)
{
	std::ofstream myfile;
	myfile.open(outputFile);

	myfile << bwidth << "," << bheight << "\n";

	for (int rr = 0; rr < bheight; rr++) {
		for (int cc = 0; cc < bwidth; cc++) {
			if (boardArr[rr * bwidth + cc] == 0) {
				myfile << '.';
			}
			else {
				myfile << 'x';
			}
		}
		myfile << "\n";
	}

	myfile.close();
}

// check GameMode
void FileIO::checkGameMode(std::string &boardStr, std::string &GameMode, std::size_t &found)
{
	std::string pursuit = "pursuit";
	std::string patrol = "patrol";
	std::string escape = "escape";
	// check GameMode
	found = boardStr.find(pursuit);
	if (found != std::string::npos) {
		GameMode = pursuit;
	}
	else {
		found = boardStr.find(patrol);
		if (found != std::string::npos) {
			GameMode = patrol;
		}
		else
		{
			found = boardStr.find(escape);
			if (found != std::string::npos) {
				GameMode = escape;
			}
		}
	}
}



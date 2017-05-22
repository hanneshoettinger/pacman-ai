#pragma once
#ifndef FILEIO_H
#define FILEIO_H

class FileIO
{
public:
	FileIO();
	~FileIO();

	// static to call without object
	// input file from .gol file 
	static std::string getFileContents(); //very fast!! 

	static void saveBoardtoFile(char *boardArr, int &bheight, int &bwidth);

	static void checkGameMode(std::string &boardStr, std::string &GameMode, std::size_t &found);

};

#endif
#pragma once
#ifndef INPUTPARSER_H
#define INPUTPARSER_H

// shows how to use command inputs
static void show_usage(char *argv);
// check command line inputs and set global values 
int checkInputs(int argc, char *argv[]);

extern int measureOn;
extern int generations;
extern const int mapwidth;
extern const int mapheight;
extern std::string inputFile;
extern std::string outputFile;

#endif
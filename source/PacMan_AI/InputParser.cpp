#include "stdafx.h"
#include "InputParser.h"

// Standard Values for measureOn and 250 generations to process
int measureOn = 0;
int generations = 250;

std::string inputFile;
std::string outputFile;

// shows how to use command inputs
void show_usage(char *argv)
{
	std::cerr << "Usage: " << argv << " <option(s)> "
		<< "Options:\n"
		<< "\t--help\t\tShow this help message\n"
		<< "\t--load \t\tSpecify the input .txt file\n"
		<< std::endl;
}

// check command line inputs and set global values 
int checkInputs(int argc, char *argv[])
{
	if (argc < 2)
	{
		show_usage(argv[0]);
		return 0;
	}

	// Input Handling
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--help") {
			show_usage(argv[0]);
			return 0;
		}
		else if (arg == "--load") {
			if (i + 1 < argc){
				inputFile = argv[i + 1];
			}
			else{
				return 0;
			}
		}
		else if (arg == "--save") {
			if (i + 1 < argc){
				outputFile = argv[i + 1];
			}
			else{
				return 0;
			}
		}
	}
	return 1;
}
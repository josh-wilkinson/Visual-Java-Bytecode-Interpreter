#pragma once
#include "vm.h"

void parseLine()
{

}

void checkTokens()
{

}

void read_instructions(void)
{
	parseLine();
	checkTokens();
}

void printTextFileContents(std::string filename)
{

	std::string line;

	std::ifstream myfile(filename);

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::cout << line << std::endl;
		}
	}

	myfile.close();

}



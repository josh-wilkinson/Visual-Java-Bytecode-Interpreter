#pragma once
#include "vm.h"

void parseLine(std::string line, int code[256], int &size)
{
	bool isCode = false;

	std::istringstream itemReader;

	std::string item;
	std::string opcodeOperand = "";

	char c;

	for (int i = 0; i < line.length(); i++)
	{
		c = line.at(i);

		if (c == ':') // after line number
		{
			i = i + 2;
			c = line.at(i);
			isCode = true;
		}

		if (isCode)
		{
			//std::cout << c;
			opcodeOperand += c;
		}
	}

	// now parse the opcodeOperand string

	int itemCount = 0;

	//read strings
	itemReader.clear();
	itemReader.str(opcodeOperand);
	while (itemReader.good())
	{
		itemCount++;
		itemReader >> item;
		if (item != "Code:")
		{
			if (itemCount == 1) // item 1: opcode
			{
				// add to array
				code[size] = stringToOpcode(item);
				size++;
			}
			else if (itemCount == 2) // item 2: possible operand
			{
				// add to array
				item.erase(remove(item.begin(), item.end(), '#'), item.end()); //remove # from string
				code[size] = stoi(item);
				size++;
			}
		}
	}	
}

void checkTokens()
{

}

void readInstructions(int code[256], std::string filename, int &size)
{
	// Ignore first line
	// 2: class name + [ { ]
	// 3: class method
	// 4: code marker [ Code: ]
	// 5-7: opcodes
	// 8: blank line
	// 9: method (normally main method)
	// 10: code marker [ Code: ]
	// 11+: opcodes
	// eof: curly bracket [ } ]

	int currentLineNumber = 1;

	std::string line;
	std::string item;

	std::istringstream itemReader;
	std::ifstream myfile(filename);

	bool isCode = false;

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{

			if (isCode)
			{
				parseLine(line, code, size);
				//std::cout << line << std::endl;
			}

			//std::cout << line << std::endl;

			//read strings
			itemReader.clear();
			itemReader.str(line);
			while (itemReader.good())
			{
				itemReader >> item;
				if (item == "Code:")
				{
					isCode = true;
				}
				else if (item == "return")
				{
					isCode = false;
				}
			}

			currentLineNumber++;
		}
	}
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

void printTextFileCode(std::string filename)
{

	std::string line;
	std::string item;

	std::istringstream itemReader;
	std::ifstream myfile(filename);

	bool isCode = false;

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			char c;

			for (int i = 0; i < line.length(); i++)
			{
				c = line.at(i);
				if (c == ':')
				{
					isCode = true;
				}
			}

			//read strings
			itemReader.clear();
			itemReader.str(line);
			while (itemReader.good())
			{
				itemReader >> item;

				if (item == "Code:")
				{
					isCode = false;
				}
				else if (item == "//")
				{
					isCode = false;
				}

				item.erase(remove(item.begin(), item.end(), '#'), item.end()); //remove A from string

				if (isCode)
				{
					std::cout << item << " " << std::endl;
				}
			}

			isCode = false;			
		}
	}
	myfile.close();
}

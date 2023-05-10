#pragma once
#include "vm.h"

void parseLine(std::string line, codeLine code[256], int &size)
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
			opcodeOperand += c; // store everything after the line number that is considered code
		}
	}
	// parse for line number
	std::string lineNum = "";
	for (int i = 0; i < line.length(); i++)
	{
		c = line.at(i);
		
		if (c == ':')
			break;
		lineNum += c;
	}
	lineNum.erase(remove(lineNum.begin(), lineNum.end(), ' '), lineNum.end()); //remove blank spaces from string
	code[size].opcodeNumber = stoi(lineNum);
	// now parse the opcodeOperand string
	int itemCount = 0;
	// read strings
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
				code[size].instruction = stringToOpcode(item);
			}
			else if (itemCount == 2) // item 2: possible operand
			{
				// add to array
				item.erase(remove(item.begin(), item.end(), '#'), item.end()); //remove # from string
				item.erase(remove(item.begin(), item.end(), ','), item.end()); //remove , from string
				code[size].operand1 = stoi(item);
			}
			else if (itemCount == 3)
			{
				// add to array
				if (item != "//") // with '//' denoting a comment
				{
					item.erase(remove(item.begin(), item.end(), '#'), item.end()); //remove # from string
					item.erase(remove(item.begin(), item.end(), ','), item.end()); //remove , from string
					code[size].operand2 = stoi(item);
				}
				else
					break;
			}
			else if (itemCount == 4)
			{
				// add to array
				if (item != "//") // with '//' denoting a comment
				{
					item.erase(remove(item.begin(), item.end(), '#'), item.end()); //remove # from string
					item.erase(remove(item.begin(), item.end(), ','), item.end()); //remove , from string
					code[size].operand3 = stoi(item);
				}
				else
					break;
			}
		}
	}
	size++;
}

void readInstructions(codeLine code[256], std::string filename, int &size)
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
			if (isCode)
			{
				parseLine(line, code, size);
			}
			// read strings
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
		}
	}

	myfile.close();
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

std::string getTextFileCodeString(std::string filename)
{
	std::string returnString = "";
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
					returnString += item + " ";
				}
			}
			if (isCode)
				returnString += "\n";
			isCode = false;
			
		}
	}
	myfile.close();

	return returnString;
}

uint64_t byteToReadableFormat(uint8_t byte)
{
	uint64_t returnValue = byte;
	return returnValue;
}

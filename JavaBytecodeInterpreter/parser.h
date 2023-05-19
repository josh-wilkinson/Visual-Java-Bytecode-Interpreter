#pragma once
#include "vm.h"

void parseCodeLine(std::string line, codeLine code[256], int& size, std::string nameOfMethod)
{
	bool isCode = false;
	std::istringstream itemReader;
	std::string item;
	std::string opcodeOperand = "";
	char c;

	// method name / descriptor
	code[size].methodName = nameOfMethod;

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

	isCode = true;

	// parse for line number
	std::string lineNum = "";
	for (int i = 0; i < line.length(); i++)
	{
		c = line.at(i);

		if (c == 's')
		{
			isCode = false;
			break;
		}

		if (c == ':')
			break;
			
		lineNum += c;
	}
	if (isCode)
	{
		lineNum.erase(remove(lineNum.begin(), lineNum.end(), ' '), lineNum.end()); //remove blank spaces from string
		code[size].opcodeNumber = stoi(lineNum);
	}
	// now parse the opcodeOperand string
	int itemCount = 0;
	// read strings
	itemReader.clear();
	itemReader.str(opcodeOperand);
	while (itemReader.good())
	{
		itemCount++;
		itemReader >> item;
		if (item != "Code:" && item[0] != 's')
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
	if (isCode)
		size++;	
}

void parseConstantPoolLine(std::string line, constantPoolLine cPool[256], int& size)
{
	bool isConstantPool = false;
	std::istringstream itemReader;
	std::string item;
	std::string nameAndItem = "";
	char c;

	for (int i = 0; i < line.length(); i++)
	{
		c = line.at(i);

		if (c == '=') // after line number
		{
			i = i + 2;
			c = line.at(i);
			isConstantPool = true;
		}

		if (isConstantPool)
		{
			nameAndItem += c; // store everything after the line number that is considered code
		}
	}

	// parse for line number
	std::string lineNum = "";
	for (int i = 0; i < line.length(); i++)
	{
		c = line.at(i);

		if (c == '=')
			break;
		lineNum += c;
	}

	lineNum.erase(remove(lineNum.begin(), lineNum.end(), '#'), lineNum.end()); //remove # from string
	lineNum.erase(remove(lineNum.begin(), lineNum.end(), '='), lineNum.end()); //remove = from string
	lineNum.erase(remove(lineNum.begin(), lineNum.end(), ' '), lineNum.end()); //remove blank spaces from string
	cPool[size].constantNumber = stoi(lineNum);

	// now parse the opcodeOperand string
	int itemCount = 0;

	// read strings
	itemReader.clear();
	itemReader.str(nameAndItem);

	cPool[size].constantItem = "";
	while (itemReader.good())
	{
		itemCount++;
		itemReader >> item;
		if (item != "Constant" && item != "pool:" && item != "{")
		{
			if (item == "//")
				break;

			if (itemCount == 1) // item 1: opcode
			{
				// add to array
				cPool[size].constantName = item;
			}
			else if (itemCount >= 2) // item 2: possible operand
			{
				// add to array
				//item.erase(remove(item.begin(), item.end(), '#'), item.end()); //remove # from string
				cPool[size].constantItem += item;
			}
		}
	}
	size++;
}

void readInstructions(codeLine code[256], constantPoolLine constantPool[256], std::string filename, int& sizeOfCodeArray, int& sizeOfConstantPoolArray)
{
	std::string fn;
	std::string line;
	std::string item;
	std::string methodName;

	std::istringstream itemReader;
	std::ifstream myfile(filename);

	int codeCount = 0;
	bool isCode = false;
	bool isConstantPool = false;
	bool isFilename = false;
	bool foundDescriptor = false;

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			if (isCode)
			{
				parseCodeLine(line, code, sizeOfCodeArray, methodName);
			}
			if (isConstantPool)
			{
				parseConstantPoolLine(line, constantPool, sizeOfConstantPoolArray);
			}
			// read strings
			itemReader.clear();
			itemReader.str(line);
			while (itemReader.good())
			{
				itemReader >> item;
				if (item == "Code:")
				{
					codeCount++;
					if (codeCount >= 1)
						isCode = true;
				}
				else if (item == "Constant")
				{
					isConstantPool = true;
				}
				else if (item == "return")
				{
					isCode = false;
				}
				else if (item == fn)
				{
					isConstantPool = false;
				}

				if (foundDescriptor)
				{
					methodName = item;
					foundDescriptor = false;
				}

				if (item == "descriptor:")
				{
					foundDescriptor = true;

				}

				if (isFilename)
				{
					fn = item;
					fn.erase(remove(fn.begin(), fn.end(), '"'), fn.end()); //remove " from string
					fn.erase(remove(fn.begin(), fn.end(), '"'), fn.end()); //remove \ from string
					fn.erase(remove(fn.begin(), fn.end(), ' '), fn.end()); //remove spaces from string
					isFilename = false;
				}

				if (item == "from")
				{
					isFilename = true;
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
	bool isConstantPool = false;

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
				else if (item == "Constant")
				{
					isConstantPool = true;
				}
				else if (item == "//")
				{
					isCode = false;
					isConstantPool = false;
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

#pragma once
#include "vm.h"

void parseLine(std::string line, int code[256], int size)
{
	bool isCode = false;

	std::istringstream itemReader;

	std::string item;
	std::string opcodeOperand = "";

	char c;

	for (int i = 0; i < line.length(); i++)
	{
		c = line.at(i);
		//std::cout << c;
		if (c == ':')
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

	std::cout << opcodeOperand << std::endl;

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
			}
			else if (itemCount == 2) // item 2: possible operand
			{
				// add to array
			}
		}
	}
	std::cout << "Item count: " << itemCount << std::endl;
}

void checkTokens()
{

}

opcode stringToOpcode(const std::string& str)
{
	if (str == "iconst_i") return iconst_i;
	else if (str == "iload") return iload;
	else if (str == "istore") return istore;
	else if (str == "iadd") return iadd;
	else if (str == "iinc") return iinc;
	else if (str == "isub") return isub;
	else if (str == "imul") return imul;
	else if (str == "ishl") return ishl;
	else if (str == "ishr") return ishr;
	else if (str == "if_icmpne") return if_icmpne;
	else if (str == "if_icmpeq") return if_icmpeq;
	else if (str == "if_icmpgt") return if_icmpgt;
	else if (str == "if_cmpge") return if_cmpge;
	else if (str == "if_icmplt") return if_icmplt;
	else if (str == "if_icmple") return if_icmple;
	else if (str == "ifeq") return ifeq;
	else if (str == "ifne") return ifne;
	else if (str == "ifgt") return ifgt;
	else if (str == "ifge") return ifge;
	else if (str == "iflt") return iflt;
	else if (str == "ifle") return ifle;
	else if (str == "invokestatic") return invokestatic;
	else if (str == "invokevirtual") return invokevirtual;
	else if (str == "invokespecial") return invokespecial;
	else if (str == "return") return OP_DONE;
	else	
		return NA;	
}

void read_instructions(int code[256], std::string filename, int size)
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

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			//read strings
			itemReader.clear();
			itemReader.str(line);
			while (itemReader.good())
			{
				itemReader >> item;
				if (item == "Code:")
				{
					parseLine(line, code, size);
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

#include "vm.h"
#include "parser.h"


int main(int argc, char* argv[])
{
	codeLine code[256]; // array of lines of code
	int size = 0; // number of elements in code array

	// Parse text file

	//parseLine("0: iconst_0", code, size);
	readInstructions(code, "Spin.txt", size);

	//for (int i = 0; i < numberOfItems; i++)
		//std::cout << code[i].instruction << ", ";

	for (int i = 0; i < size; i++)
	{
		std::cout << code[i].lineNumber << std::endl;
		std::cout << code[i].instruction << std::endl;
	}

	//std::cout << code[0].instruction;

	// use these for testing
	(void)argc; (void)argv; // tells the compiler to stop complaining about unused variables
	{		
		// interpretResult result = vmInterpret(code);
		
		// assert(result == SUCCESS);
	}

	return 0;
}


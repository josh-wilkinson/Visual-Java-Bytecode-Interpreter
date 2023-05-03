#include "vm.h"
#include "parser.h"


int main(int argc, char* argv[])
{
	int code[256];
	int numberOfItems = 0; // number of elements in code array

	// Parse text file

	//parseLine("       1: invokespecial #1                  // Method java/lang/Object. < init > :()V ", code, size);
	readInstructions(code, "Spin.txt", numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
		std::cout << code[i] << ", ";

	// use these for testing
	(void)argc; (void)argv; // tells the compiler to stop complaining about unused variables
	{		
		// interpretResult result = vmInterpret(code);

		// assert(result == SUCCESS);
	}

	return 0;
}


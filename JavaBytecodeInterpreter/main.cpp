#include "vm.h"
#include "parser.h"


int main(int argc, char* argv[])
{

	// Parse text file
	int code[256];
	int size = 0; // number of elements in code array

	//parseLine("       3: bipush        100", code, size);
	readInstructions(code, "Spin.txt", size);

	for (int i = 0; i < size; i++)
		std::cout << code[i] << " ";
	
	// use these for testing
	(void)argc; (void)argv; // tells the compiler to stop complaining about unused variables
	{
		
		// interpretResult result = vmInterpret(code);

		// assert(result == SUCCESS);
	}

	return 0;
}


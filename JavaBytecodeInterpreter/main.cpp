#include "vm.h"
#include "parser.h"


int main(int argc, char* argv[])
{
	codeLine code[256]; // array of lines of code
	int sizeOfCodeArray = 0; // number of elements in code array

	// Parse text file
	readInstructions(code, "Spin.txt", sizeOfCodeArray);

	uint64_t result = code[0].lineNumber;

	for (int i = 0; i < sizeOfCodeArray; i++)
	{
		std::cout << code[i].lineNumber << std::endl;
		std::cout << code[i].instruction << std::endl;
		std::cout << code[i].operand1 << std::endl;
		std::cout << code[i].operand2 << std::endl;
		std::cout << code[i].operand3 << std::endl;
	}

	// use these for testing
	(void)argc; (void)argv; // tells the compiler to stop complaining about unused variables
	{		
		// interpretResult result = vmInterpret(code);
		
		// assert(result == SUCCESS);
	}

	return 0;
}


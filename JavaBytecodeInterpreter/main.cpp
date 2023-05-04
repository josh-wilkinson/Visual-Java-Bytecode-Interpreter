#include "vm.h"
#include "parser.h"


int main(int argc, char* argv[])
{
	codeLine code[256]; // array of lines of code
	int sizeOfCodeArray = 0; // number of elements in code array

	// Parse text file
	readInstructions(code, "Spin.txt", sizeOfCodeArray);
	/*
	for (int i = 0; i < sizeOfCodeArray; i++)
	{
		std::cout << "Line: " << byteToReadableFormat(code[i].lineNumber) << std::endl;
		std::cout << "Code: " << byteToReadableFormat(code[i].instruction) << std::endl;
		std::cout << "Op.1: " << byteToReadableFormat(code[i].operand1) << std::endl;
		std::cout << "Op.2: " << byteToReadableFormat(code[i].operand2) << std::endl;
		std::cout << "Op.3: " << byteToReadableFormat(code[i].operand3) << std::endl;
		std::cout << std::endl;
	}
	*/
	// use these for testing
	(void)argc; (void)argv; // tells the compiler to stop complaining about unused variables
	{		
		interpretResult result = vmInterpret(code);
		
		assert(result == SUCCESS);

		if (result == SUCCESS)
			std::cout << "Interpreter ran successfully!";
		else if (result == ERROR_UNKNOWN_OPCODE)
			std::cout << "Error: unknown opcode.";
	}

	return 0;
}


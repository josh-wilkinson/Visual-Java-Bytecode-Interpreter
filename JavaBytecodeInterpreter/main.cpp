#include "vm.h"
#include "parser.h"

int main(int argc, char* argv[])
{
	codeLine code[256]; // array of lines of code
	constantPoolLine constantPool[256];
	int sizeOfCodeArray = 0; // number of elements in code array
	int sizeOfCPoolArray = 0;

	// Parse text file
	readInstructions(code, constantPool, "CallTest.opcode", sizeOfCodeArray, sizeOfCPoolArray);
	
	for (int i = 0; i < sizeOfCodeArray; i++)
	{
		std::cout << "Line: " << byteToReadableFormat(code[i].opcodeNumber) << std::endl;
		std::cout << "Code: " << byteToReadableFormat(code[i].instruction) << std::endl;
		std::cout << "Method name: " << code[i].methodName << std::endl;
		//std::cout << "Op.1: " << byteToReadableFormat(code[i].operand1) << std::endl;
		//std::cout << "Op.2: " << byteToReadableFormat(code[i].operand2) << std::endl;
		//std::cout << "Op.3: " << byteToReadableFormat(code[i].operand3) << std::endl;
		std::cout << std::endl;
	}
	
	/*
	for (int i = 0; i < sizeOfCPoolArray; i++)
	{
		std::cout << "Line: " << constantPool[i].constantNumber << std::endl;
		std::cout << "1: " << constantPool[i].constantName << std::endl;
		std::cout << "2: " << constantPool[i].constantItem << std::endl;
		std::cout << std::endl;
	}
	*/
	//std::cout << getTextFileCodeString("Sum.txt");
	

	// use these for testing
	(void)argc; (void)argv; // tells the compiler to stop complaining about unused variables
	{		
		interpretResult result = vmInterpret(code, constantPool, sizeOfCodeArray, sizeOfCPoolArray);
		
		vmReset();

		result = vmInterpret(code, constantPool, sizeOfCodeArray, sizeOfCPoolArray);

		std::cout << "var 0: " << vm.var0 << std::endl;
		std::cout << "var 1: " << vm.var1 << std::endl;
		std::cout << "var 2: " << vm.var2 << std::endl;
		std::cout << "var 3: " << vm.var3 << std::endl;

		assert(result == SUCCESS);

		if (result == SUCCESS)
			std::cout << "Interpreter ran successfully!";
		else if (result == ERROR_UNKNOWN_OPCODE)
			std::cout << "Error: unknown opcode.";
	}
	return 0;
}


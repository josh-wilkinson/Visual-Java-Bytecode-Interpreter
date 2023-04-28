#include "vm.h"
#include "parser.h"





int main(int argc, char* argv[])
{

	// Parse text file
	// std::vector<uint8_t> v = {}; ?vector?
	// uint8_t code[] = {}; ?array?

	printTextFileContents("Spin.txt");
	

	(void)argc; (void)argv; // tells the compiler to stop complaining about unused variables
	{
		
		// interpretResult result = vmInterpret(code);

		// assert(result == SUCCESS);
	}

	return 0;
}


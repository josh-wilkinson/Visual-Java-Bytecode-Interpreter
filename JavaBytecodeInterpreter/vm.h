#pragma once

#define STACK_MAX 256

#include <iostream>
#include <ctype.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

// stack based interpreter
struct
{
	uint8_t* ip;
	int i = 0; // index
	bool steppingThroughCode = false;
	bool finishedExecution = false;
	int elementsInStack = 0;
	int elementsInMethodStack = 0;

	// Fixed-size stack
	uint64_t stack[STACK_MAX];
	uint64_t* stack_top;

	// Fixed-size stack
	uint64_t methodStack[STACK_MAX];
	uint64_t* method_stack_top;

	// Registers
	uint64_t var0;
	uint64_t var1;
	uint64_t var2;
	uint64_t var3;
	// bool to check if a register is being used
	bool usingVar0 = false;
	bool usingVar1 = false;
	bool usingVar2 = false;
	bool usingVar3 = false;
} vm;

// structure for every line in the program
struct codeLine
{
	uint64_t opcodeNumber, instruction, operand1, operand2, operand3;
	// String (method name)
	std::string methodName;
};

struct constantPoolLine
{
	uint64_t constantNumber;
	std::string constantName;
	std::string constantItem;
};

// opcodes enumerator
typedef enum
{
	aload,
	aload_0,
	aload_1,
	aload_2,
	aload_3,
	bipush,
	getstatic,
	iadd,
	iconst_0,
	iconst_1,
	iconst_2,
	iconst_3,
	iconst_4,
	iconst_5,
	idiv,
	if_icmpne,
	if_icmpeq,
	if_icmpgt,
	if_icmplt,
	if_icmple,
	if_icmpge,
	ifeq,
	ifne,
	ifgt,
	ifge,
	iflt,
	ifle,
	iinc,
	iload,
	iload_0,
	iload_1,
	iload_2,
	iload_3,
	invokespecial,
	invokestatic,
	invokevirtual,
	imul,
	isub,
	ishl,
	ishr,
	istore,
	istore_0,
	istore_1,
	istore_2,
	istore_3,
	ldc,
	GOTO,
	OP_DONE, // stop execution
	NA = 257 // default - opcode does not exist
} opcode;

typedef enum interpretResult
{
	SUCCESS,
	SUCCESSFUL_STEP,
	ERROR_DIVISION_BY_ZERO,
	ERROR_UNKNOWN_OPCODE
} interpretResult;

void vmReset()
{
	std::cout << "Reset VM state" << std::endl;
	vm = decltype(vm){ NULL };
	vm.stack_top = vm.stack;
	vm.method_stack_top = vm.methodStack;
}

// virtual machine stack functions
void vmStackPush(uint64_t value)
{
	vm.elementsInStack++;
	*vm.stack_top = value;
	vm.stack_top++; // next space in memory
}

uint64_t vmStackPop(void)
{
	vm.elementsInStack--;
	vm.stack_top--; // previous space in memory
	return *vm.stack_top;
}

// stack functions for method locations in the program array
void methodStackPush(uint64_t value)
{
	vm.elementsInMethodStack++;
	*vm.method_stack_top = value;
	vm.method_stack_top++; // next space in memory
}

uint64_t methodStackPop(void)
{
	vm.elementsInMethodStack--;
	vm.method_stack_top--; // previous space in memory
	return *vm.method_stack_top;
}

void jumpToOpcodeNumber(codeLine program[], int index, bool branching, int size) // same as GOTO
{
	uint64_t lineNum = program[index].operand1;

	// beginningOfMethod - say if we have multiple methods in the program array, then to get to the start of the method we need to subract the opcode number (e.g. 7) into the index.
	int beginningOfMethod = index - program[index].opcodeNumber;

	if (beginningOfMethod < 0)
		beginningOfMethod = 0;
	for (int j = beginningOfMethod; j < size; j++)
	{
		if (program[j].opcodeNumber == lineNum)
		{
			vm.i = j;
			branching = true;
			break;
		}
	}
}

// interpreter code
interpretResult vmInterpret(codeLine program[256], constantPoolLine cPool[256], int sizeOfCodeArray, int sizeOfConstantPoolArray) // program goes through code here
{
	if (!vm.steppingThroughCode)
	{
		vmReset();
	}

	bool branching = false;
	bool methodCalling = false;
	int beginningOfMethod;
	int counter = 0;
	uint64_t value1;
	uint64_t value2;
	std::string utf8;

	std::cout << "Interpreter started" << std::endl;
	do
	{
		uint8_t instruction = program[vm.i].instruction;
		branching = false;
		methodCalling = false;
		counter = program[vm.i].instruction;
		std::cout << "Counter: " << vm.i << std::endl;
		switch (instruction)
		{
			// All of the opcode instructions are implemented here!
		case aload:
			break;
		case aload_0:
			break;
		case aload_1:
			break;
		case aload_2:
			break;
		case aload_3:
			break;
		case bipush:
			vmStackPush(program[vm.i].operand1);
			break;
		case getstatic:
			break;
		case iadd:
			value1 = vmStackPop();
			value2 = vmStackPop();
			vmStackPush(value1 + value2);
			break;
		case iconst_0:
			vmStackPush(0);
			break;
		case iconst_1:
			vmStackPush(1);
			break;
		case iconst_2:
			vmStackPush(2);
			break;
		case iconst_3:
			vmStackPush(3);
			break;
		case iconst_4:
			vmStackPush(4);
			break;
		case iconst_5:
			vmStackPush(5);
			break;
		case idiv:
			value1 = vmStackPop();
			value2 = vmStackPop();
			vmStackPush(value2 / value1);
			break;
		case if_icmpne:
			value1 = vmStackPop();
			value2 = vmStackPop();
			std::cout << "?: " << value2 << " != " << value1 << std::endl;
			if (value2 != value1)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case if_icmpeq:
			value1 = vmStackPop();
			value2 = vmStackPop();
			std::cout << "?: " << value2 << " == " << value1 << std::endl;
			if (value2 == value1)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case if_icmpgt:
			value1 = vmStackPop();
			value2 = vmStackPop();
			std::cout << "?: " << value2 << " > " << value1 << std::endl;
			if (value2 > value1)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case if_icmplt:
			value1 = vmStackPop();
			value2 = vmStackPop();
			std::cout << "?: " << value2 << " < " << value1 << std::endl;
			if (value2 < value1)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case if_icmple:
			value1 = vmStackPop();
			value2 = vmStackPop();
			std::cout << "?: " << value2 << " <= " << value1 << std::endl;
			if (value2 <= value1)
			{
				uint64_t lineNum = program[vm.i].operand1;

				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case if_icmpge:
			value1 = vmStackPop();
			value2 = vmStackPop();
			std::cout << "?: " << value2 << " >= " << value1 << std::endl;
			if (value2 >= value1)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}

			break;
		case ifeq:
			value1 = vmStackPop();
			std::cout << "?: " << value1 << " is 0 " << std::endl;
			if (value1 == 0)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case ifne:
			value1 = vmStackPop();
			std::cout << "?: " << value1 << " is not 0 " << std::endl;
			if (value1 != 0)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case ifgt:
			value1 = vmStackPop();
			std::cout << "?: " << value1 << " is > 0 " << std::endl;
			if (value1 > 0)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case ifge:
			value1 = vmStackPop();
			std::cout << "?: " << value1 << " is >= 0 " << std::endl;
			if (value1 >= 0)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case iflt:
			value1 = vmStackPop();
			std::cout << "?: " << value1 << " is < 0 " << std::endl;
			if (value1 < 0)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case ifle:
			value1 = vmStackPop();
			std::cout << "?: " << value1 << " is <= 0 " << std::endl;
			if (value1 <= 0)
			{
				uint64_t lineNum = program[vm.i].operand1;
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
				{
					if (program[j].opcodeNumber == lineNum)
					{
						vm.i = j;
						branching = true;
						break;
					}
				}
			}
			break;
		case iinc:
			switch (program[vm.i].operand1)
			{
			case 0:
				value1 = vm.var0;
				value2 = program[vm.i].operand2;
				vm.var0 = value1 + value2;
				break;
			case 1:
				value1 = vm.var1;
				value2 = program[vm.i].operand2;
				vm.var1 = value1 + value2;
				break;
			case 2:
				value1 = vm.var2;
				value2 = program[vm.i].operand2;
				vm.var2 = value1 + value2;
				break;
			case 3:
				value1 = vm.var3;
				value2 = program[vm.i].operand2;
				vm.var3 = value1 + value2;
				break;
			}
			break;
		case iload:
			// format: opcode operand
			// different way to iload_0 to iload_3
			break;
		case iload_0:
			value1 = vm.var0;
			vmStackPush(value1);
			break;
		case iload_1:
			value1 = vm.var1;
			vmStackPush(value1);
			break;
		case iload_2:
			value1 = vm.var2;
			vmStackPush(value1);
			break;
		case iload_3:
			value1 = vm.var3;
			vmStackPush(value1);
			break;
		case invokespecial:
			// Find the main method in the code array and jump to that
			//methodCalling = true;			
			utf8 = "([Ljava/lang/String;)V";
			for (int j = 0; j < sizeOfCodeArray; j++)
			{
				if (program[j].methodName == utf8)
				{
					vm.i = j - 1;
					std::cout << "FOUND METHOD " << utf8 << std::endl;
					break;
				}
			}
			break;
		case invokestatic:
			// Find the method in the code array and jump to that
			methodCalling = true;
			value1 = program[vm.i].operand1;
			value2 = vm.i;
			// getting method name called, e.g. java/lang/Object."<init>":()V
			utf8 = cPool[value1 + 4].constantItem;
			for (int j = 0; j < sizeOfCodeArray; j++)
			{
				if (program[j].methodName == utf8)
				{
					methodStackPush(value2);
					vm.i = j;
					std::cout << "FOUND METHOD " << utf8 << std::endl;
					break;
				}
			}
			break;
			break;
		case invokevirtual:
			value1 = vmStackPop();
			value2 = program[vm.i].operand1 + 3;
			// invoke virtual method
			// check for PrintStream, then output to console
			utf8 = cPool[value2].constantItem;
			if (utf8 == "print")
				std::cout << cPool[value1].constantItem;
			else if (utf8 == "println")
				std::cout << cPool[value1].constantItem << std::endl;
			break;
		case imul:
			value1 = vmStackPop();
			value2 = vmStackPop();
			vmStackPush(value2 * value1);
			break;
		case isub:
			vmStackPush(vmStackPop() - vmStackPop());
			break;
		case ishl:
			value1 = vmStackPop();
			value2 = vmStackPop();
			//uint64_t result = value2 >> value1;
			//vmStackPush(result);
			break;
		case ishr:
			value1 = vmStackPop();
			value2 = vmStackPop();
			//uint64_t result = value2 << value1;
			//vmStackPush(result);
			break;
		case istore:
			// format: opcode operand
			// different way to istore_0 to istore_3
			switch (program[vm.i].operand1)
			{
			case 0:
				value1 = vmStackPop();
				vm.var1 = value1;
				vm.usingVar0 = true;
				break;
			case 1:
				value1 = vmStackPop();
				vm.var1 = value1;
				vm.usingVar1 = true;
				break;
			case 2:
				value1 = vmStackPop();
				vm.var2 = value1;
				vm.usingVar2 = true;
				break;
			case 3:
				value1 = vmStackPop();
				vm.var3 = value1;
				vm.usingVar3 = true;
				break;
			}
			break;
		case istore_0:
			value1 = vmStackPop();
			vm.var0 = value1;
			vm.usingVar0 = true;
			break;
		case istore_1:
			value1 = vmStackPop();
			vm.var1 = value1;
			vm.usingVar1 = true;
			break;
		case istore_2:
			value1 = vmStackPop();
			vm.var2 = value1;
			vm.usingVar2 = true;
			break;
		case istore_3:
			value1 = vmStackPop();
			vm.var3 = value1;
			vm.usingVar3 = true;
			break;
		case ldc:
			value1 = program[vm.i].operand1;
			vmStackPush(value1);
			break;
		case GOTO:
			beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
			for (int j = beginningOfMethod; j < sizeOfCodeArray; j++)
			{
				if (program[j].opcodeNumber == program[vm.i].operand1)
				{
					vm.i = j;
					branching = true;
					break;
				}
				else if (program[j].instruction == OP_DONE)
					break;
			}
			break;
		case OP_DONE:
			if (program[vm.i].methodName == "([Ljava/lang/String;)V")
			{
				vm.finishedExecution = true;
				return SUCCESS;
			}
			else
			{
				std::cout << "JUMPING FROM " << vm.i;
				value1 = methodStackPop() + 1;
				vm.i = value1;
				methodCalling = true;
				std::cout << " TO " << vm.i << std::endl;
			}
			//std::cout << program[vm.i].methodName << std::endl;
			break;			
		case NA:
			vm.finishedExecution = true;
			return ERROR_UNKNOWN_OPCODE;
			break;
		default:
			vm.finishedExecution = true;
			std::cout << "Unknown opcode!!" << std::endl;
			return ERROR_UNKNOWN_OPCODE;
			break;
		}
		if (!branching && !methodCalling)
			vm.i++;
	} while (!vm.steppingThroughCode);

	if (vm.steppingThroughCode)
		return SUCCESSFUL_STEP;
	else
	{
		vm.finishedExecution = true;
		return SUCCESS;
	}

}

opcode stringToOpcode(const std::string& str)
{
	std::map<std::string, opcode> mp =
	{
		{"aload", aload},
		{"aload_0", aload_0},
		{"aload_1", aload_1},
		{"aload_2", aload_2},
		{"aload_3", aload_3},
		{"bipush", bipush},
		{"getstatic", getstatic},
		{"iadd", iadd},
		{"iconst_0", iconst_0},
		{"iconst_1", iconst_1},
		{"iconst_2", iconst_2},
		{"iconst_3", iconst_3},
		{"iconst_4", iconst_4},
		{"iconst_5", iconst_5},
		{"idiv", idiv},
		{"if_icmpne", if_icmpne},
		{"if_icmpeq", if_icmpeq},
		{"if_icmpgt", if_icmpgt},
		{"if_icmpge", if_icmpge},
		{"if_icmplt", if_icmplt},
		{"if_icmple", if_icmple},
		{"ifeq", ifeq},
		{"ifne", ifne},
		{"ifgt", ifgt},
		{"ifge", ifge},
		{"iflt", iflt},
		{"ifle", ifle},
		{"iinc", iinc},
		{"iload", iload},
		{"iload_0", iload_0},
		{"iload_1", iload_1},
		{"iload_2", iload_2},
		{"iload_3", iload_3},
		{"invokespecial", invokespecial},
		{"invokestatic", invokestatic},
		{"invokevirtual", invokevirtual},
		{"imul", imul},
		{"isub", isub},
		{"ishl", ishl},
		{"ishr", ishr},
		{"istore", istore},
		{"istore_0", istore_0},
		{"istore_1", istore_1},
		{"istore_2", istore_2},
		{"istore_3", istore_3},
		{"ldc", ldc},
		{"goto", GOTO},
		{"return", OP_DONE},
	};
	if (mp.count(str) > 0) // if value exists in map
		return mp[str];
	else
		return NA;
}




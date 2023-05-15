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
	
	// Fixed-size stack
	uint64_t stack[STACK_MAX];
	uint64_t* stack_top;

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
	uint8_t opcodeNumber, instruction, operand1, operand2, operand3;
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
	iadd,
	iconst_0,
	iconst_1,
	iconst_2,
	iconst_3,
	iconst_4,
	iconst_5,
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
}

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
interpretResult vmInterpret(codeLine program[256], int size) // program goes through code here
{
	if (!vm.steppingThroughCode)
	{
		vmReset();
	}
	
	bool branching = false;
	
	int beginningOfMethod;
	int counter = 0;
	uint64_t value1;
	uint64_t value2;

	std::cout << "Interpreter started" << std::endl;	
	do 
	{
		uint8_t instruction = program[vm.i].instruction;
		branching = false;
		counter = program[vm.i].opcodeNumber;
		std::cout << "Counter: " << counter << std::endl;		
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
			case if_icmpne:
				value1 = vmStackPop();
				value2 = vmStackPop();
				std::cout << "?: " << value2 << " != " << value1 << std::endl;
				if (value2 != value1)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case if_icmpeq:
				value1 = vmStackPop();
				value2 = vmStackPop();
				std::cout << "?: " << value2 << " == " << value1 << std::endl;
				if (value2 == value1)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case if_icmpgt:
				value1 = vmStackPop();
				value2 = vmStackPop();
				std::cout << "?: " << value2 << " > " << value1 << std::endl;
				if (value2 > value1)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case if_icmplt:
				value1 = vmStackPop();
				value2 = vmStackPop();
				std::cout << "?: " << value2 << " < " << value1 << std::endl;
				if (value2 < value1)
				{					
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case if_icmple:
				value1 = vmStackPop();
				value2 = vmStackPop();
				std::cout << "?: " << value2 << " <= " << value1 << std::endl;
				if (value2 <= value1)
				{
					uint64_t lineNum = program[vm.i].operand1;

					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case if_icmpge:
				value1 = vmStackPop();
				value2 = vmStackPop();
				std::cout << "?: " << value2 << " >= " << value1 << std::endl;
				if (value2 >= value1)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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

				break;
			case ifeq:
				value1 = vmStackPop();
				std::cout << "?: " << value1 << " is 0 " << std::endl;
				if (value1 == 0)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case ifne:
				value1 = vmStackPop();
				std::cout << "?: " << value1 << " is not 0 " << std::endl;
				if (value1 != 0)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case ifgt:
				value1 = vmStackPop();
				std::cout << "?: " << value1 << " is > 0 " << std::endl;
				if (value1 > 0)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case ifge:
				value1 = vmStackPop();
				std::cout << "?: " << value1 << " is >= 0 " << std::endl;
				if (value1 >= 0)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case iflt:
				value1 = vmStackPop();
				std::cout << "?: " << value1 << " is < 0 " << std::endl;
				if (value1 < 0)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case ifle:
				value1 = vmStackPop();
				std::cout << "?: " << value1 << " is <= 0 " << std::endl;
				if (value1 <= 0)
				{
					uint64_t lineNum = program[vm.i].operand1;
					beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
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
				break;
			case invokestatic:
				break;
			case invokevirtual:
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
			case GOTO:
				beginningOfMethod = program[vm.i].opcodeNumber - program[vm.i].opcodeNumber;
				for (int j = beginningOfMethod; j < size; j++)
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
				vm.finishedExecution = true;
				return SUCCESS;
			case NA:
				vm.finishedExecution = true;
				return ERROR_UNKNOWN_OPCODE;
			default:
				vm.finishedExecution = true;
				return ERROR_UNKNOWN_OPCODE;
				break;
		}		
		if (!branching)
			vm.i++;
	}	while (!vm.steppingThroughCode);
	
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
		{"iadd", iadd},
		{"iconst_0", iconst_0},
		{"iconst_1", iconst_1},
		{"iconst_2", iconst_2},
		{"iconst_3", iconst_3},
		{"iconst_4", iconst_4},
		{"iconst_5", iconst_5},
		{"if_icmpne", if_icmpne},
		{"if_icmpeq", if_icmpeq},
		{"if_icmpgt", if_icmpgt},
		{"if_icmpge", if_icmpge},
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
		{"goto", GOTO},
		{"return", OP_DONE},
	};
	if (mp.count(str) > 0) // if value exists in map
		return mp[str];
	else
		return NA;	
}




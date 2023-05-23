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

	// Fixed-size method return locations stack
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
	// Console output
	std::string currentOutput = "";
} vm;

// structure for every line in the program
struct codeLine
{
	uint64_t opcodeNumber, instruction, operand1, operand2, operand3;
	std::string methodName; // method this line of code belongs to...
	bool breakPoint = false; // does this line have a break point?
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
	ireturn,
	NA = 257 // default - opcode does not exist
} opcode;

typedef enum interpretResult
{
	SUCCESS,
	SUCCESSFUL_STEP,
	ERROR_DIVISION_BY_ZERO,
	ERROR_UNKNOWN_OPCODE,
	BREAKPOINT
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

void branch(codeLine program[256], int sizeOfCodeArray, int beginningOfMethod, int endOfMethod, bool& branching)
{
	for (int i = 0; i < sizeOfCodeArray; i++)
	{
		if (program[i].methodName == program[vm.i].methodName)
		{
			beginningOfMethod = i;
			break;
		}
	}

	for (int i = beginningOfMethod; i < sizeOfCodeArray; i++)
	{
		if (program[i].methodName != program[vm.i].methodName)
		{
			endOfMethod = i - 1;
			break;
		}
	}

	for (int j = beginningOfMethod; j < endOfMethod; j++)
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
}

void shiftLeft()
{
	uint64_t tempRegister0 = vm.var0;
	uint64_t tempRegister1 = vm.var1;
	uint64_t tempRegister2 = vm.var2;
	uint64_t tempRegister3 = vm.var3;
	bool tempUsingVar0 = vm.usingVar0;
	bool tempUsingVar1 = vm.usingVar1;
	bool tempUsingVar2 = vm.usingVar2;
	bool tempUsingVar3 = vm.usingVar3;
	vm.var0 = tempRegister1;
	vm.var1 = tempRegister2;
	vm.var2 = tempRegister3;
	vm.var3 = tempRegister0;
	vm.usingVar0 = tempUsingVar1;
	vm.usingVar1 = tempUsingVar2;
	vm.usingVar2 = tempUsingVar3;
	vm.usingVar3 = tempUsingVar0;
}

void parseConstantItemPositions(std::string utf8, uint64_t& value1, uint64_t& value2)
{

	std::string tempString = "";

	utf8.erase(remove(utf8.begin(), utf8.end(), '#'), utf8.end()); //remove # from string

	for (int j = 0; j <= utf8.size(); j++)
	{
		char c;
		if (j < utf8.size())
			c = utf8.at(j);
		else
			c = utf8.at(j - 1);
		if (c == ':' || c == '.')
		{
			value1 = stoi(tempString);
			tempString = "";
		}
		else if (j == utf8.size())
		{
			value2 = stoi(tempString);
			break;
		}
		else
			tempString += c;
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
	int beginningOfMethod = 0;
	int endOfMethod = sizeOfCodeArray;
	int counter = 0;
	uint64_t value1;
	uint64_t value2;
	uint64_t value3;
	uint64_t value4;
	std::string utf8;

	std::cout << "Interpreter started" << std::endl;
	do
	{
		uint8_t instruction = program[vm.i].instruction;
		branching = false;
		methodCalling = false;
		counter = program[vm.i].instruction;
		std::cout << "Counter: " << vm.i << std::endl;

		if (program[vm.i].breakPoint)
			break;

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
			if (value2 != value1)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case if_icmpeq:
			value1 = vmStackPop();
			value2 = vmStackPop();
			if (value2 == value1)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case if_icmpgt:
			value1 = vmStackPop();
			value2 = vmStackPop();
			if (value2 > value1)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case if_icmplt:
			value1 = vmStackPop();
			value2 = vmStackPop();
			if (value2 < value1)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case if_icmple:
			value1 = vmStackPop();
			value2 = vmStackPop();
			if (value2 <= value1)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case if_icmpge:
			value1 = vmStackPop();
			value2 = vmStackPop();
			if (value2 >= value1)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}

			break;
		case ifeq:
			value1 = vmStackPop();
			if (value1 == 0)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case ifne:
			value1 = vmStackPop();
			if (value1 != 0)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case ifgt:
			value1 = vmStackPop();
			if (value1 > 0)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case ifge:
			value1 = vmStackPop();
			if (value1 >= 0)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case iflt:
			value1 = vmStackPop();
			if (value1 < 0)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			}
			break;
		case ifle:
			value1 = vmStackPop();
			if (value1 <= 0)
			{
				branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
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
		case iload: // loads a register variable into the stack
			// format: opcode operand
			// different way to iload_0 to iload_3
			switch (program[vm.i].operand1)
			{
			case 0:
				value1 = vm.var0;
				vmStackPush(value1);
				break;
			case 1:
				value1 = vm.var1;
				vmStackPush(value1);
				break;
			case 2:
				value1 = vm.var2;
				vmStackPush(value1);
				break;
			case 3:
				value1 = vm.var3;
				vmStackPush(value1);
				break;
			}
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
			utf8 = "main([Ljava/lang/String;)V";
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
			value2 = vm.i; // current positon in the program array
			utf8 = cPool[value1-1].constantItem;
			parseConstantItemPositions(utf8, value3, value4);
			// value4 contains the string location to the name and type of the method
			utf8 = cPool[value4-1].constantItem;
			parseConstantItemPositions(utf8, value3, value4);
			// value 3 is the index of the name
			// value 4 is the index of the type
			utf8 = cPool[value3 - 1].constantItem + cPool[value4 - 1].constantItem; // method name and descriptor

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
			for (int j = 0; j <= vm.elementsInStack; j++)
				vmStackPop();
			shiftLeft();
			break;
		case invokevirtual:
			value1 = vmStackPop();
			value2 = program[vm.i].operand1 + 3;
			// invoke virtual method
			// check for PrintStream, then output to console
			utf8 = cPool[value2].constantItem;
			if (utf8 == "print")
				vm.currentOutput += cPool[value1].constantItem;
			else if (utf8 == "println")
				vm.currentOutput += cPool[value1].constantItem + "\n";
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
			branch(program, sizeOfCodeArray, beginningOfMethod, endOfMethod, branching);
			break;
		case OP_DONE:
			if (program[vm.i].methodName == "main([Ljava/lang/String;)V")
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
		case ireturn:
			if (program[vm.i].methodName == "main([Ljava/lang/String;)V")
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

	if (program[vm.i].breakPoint)
		return BREAKPOINT;

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
		{"ireturn", ireturn},
	};
	if (mp.count(str) > 0) // if value exists in map
		return mp[str];
	else
		return NA;
}

std::string opcodeToString(uint64_t str)
{
	std::map<uint64_t, std::string> mp =
	{
		{aload, "aload"},
		{aload_0, "aload_0"},
		{aload_1, "aload_1"},
		{aload_2, "aload_2"},
		{aload_3, "aload_3"},
		{bipush, "bipush"},
		{getstatic, "getstatic"},
		{iadd, "iadd"},
		{iconst_0, "iconst_0"},
		{iconst_1, "iconst_1"},
		{iconst_2, "iconst_2"},
		{iconst_3, "iconst_3"},
		{iconst_4, "iconst_4"},
		{iconst_5, "iconst_5"},
		{idiv, "idiv"},
		{if_icmpne, "if_icmpne"},
		{if_icmpeq, "if_icmpeq"},
		{if_icmpgt, "if_icmpgt"},
		{if_icmpge, "if_icmpge"},
		{if_icmplt, "if_icmplt"},
		{if_icmple, "if_icmple"},
		{ifeq, "ifeq"},
		{ifne, "ifne"},
		{ifgt, "ifgt"},
		{ifge, "ifge"},
		{iflt, "iflt"},
		{ifle, "ifle"},
		{iinc, "iinc"},
		{iload, "iload"},
		{iload_0, "iload_0"},
		{iload_1, "iload_1"},
		{iload_2, "iload_2"},
		{iload_3, "iload_3"},
		{invokespecial, "invokespecial"},
		{invokestatic, "invokestatic"},
		{invokevirtual, "invokevirtual"},
		{imul, "imul"},
		{isub, "isub"},
		{ishl, "ishl"},
		{ishr, "ishr"},
		{istore, "istore"},
		{istore_0, "istore_0"},
		{istore_1, "istore_1"},
		{istore_2, "istore_2"},
		{istore_3, "istore_3"},
		{ldc, "ldc"},
		{GOTO, "goto"},
		{OP_DONE, "return"},
		{ireturn, "ireturn"},
	};
	if (mp.count(str) > 0) // if value exists in map
		return mp[str];
	else
		return "NA";
}

void eraseSubStr(std::string& mainStr, const std::string& toErase)
{
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);
	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}


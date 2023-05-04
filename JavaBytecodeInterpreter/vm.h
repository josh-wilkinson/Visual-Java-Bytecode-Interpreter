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

	// Fixed-size stack
	uint64_t stack[STACK_MAX];
	uint64_t* stack_top;

	// A single register containing the result
	uint64_t result;
} vm;

// structure for every line in the program
struct codeLine
{
	uint8_t lineNumber, instruction, operand1 = 0, operand2 = 0, operand3 = 0;
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
	if_cmpge,
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
	*vm.stack_top = value;
	vm.stack_top++; // next space in memory
}

uint64_t vmStackPop(void)
{
	vm.stack_top--; // previous space in memory
	return *vm.stack_top;
}

// interpreter code
interpretResult vmInterpret(uint8_t* program) // program goes through code here
{
	vmReset();

	std::cout << "Starting Interpreter..." << std::endl;
	vm.ip = program; // current opcode instruction
	
	for (;;)
	{
		uint8_t instruction = *vm.ip;
		switch (instruction)
		{
			// All of the opcode instructions are implemented here!
			case OP_DONE:
				return SUCCESS;
			case NA:
				return ERROR_UNKNOWN_OPCODE;
			default:
				return ERROR_UNKNOWN_OPCODE;
		}
	}	

	return SUCCESS;
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
		{"if_cmpge", if_cmpge},
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
	};

	if (mp.count(str) > 0) // if value exists in map
		return mp[str];
	else
		return NA;	
}




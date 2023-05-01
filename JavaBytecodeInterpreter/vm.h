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

// opcodes enumerator
typedef enum
{
	iconst_i,
	iload,
	istore,
	iadd,
	iinc,
	isub,
	imul,
	ishl,
	ishr,
	bipush, // added 01/05
	if_icmpne,
	if_icmpeq,
	if_icmpgt,
	if_cmpge,
	if_icmplt,
	if_icmple,
	if_icmpge, // added 01/05
	ifeq,
	ifne,
	ifgt,
	ifge,
	iflt,
	ifle,
	invokestatic,
	invokevirtual,
	invokespecial, // added 30/04
	/* stop execution */
	OP_DONE,
	NA = 257
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
			default:
				return ERROR_UNKNOWN_OPCODE;
		}
	}	

	return SUCCESS;
}

opcode stringToOpcode(const std::string& str)
{
	if (str == "iconst_i") return iconst_i;
	else if (str == "iload") return iload;
	else if (str == "istore") return istore;
	else if (str == "iadd") return iadd;
	else if (str == "iinc") return iinc;
	else if (str == "isub") return isub;
	else if (str == "imul") return imul;
	else if (str == "ishl") return ishl;
	else if (str == "ishr") return ishr;
	else if (str == "bipush") return bipush;
	else if (str == "if_icmpne") return if_icmpne;
	else if (str == "if_icmpeq") return if_icmpeq;
	else if (str == "if_icmpgt") return if_icmpgt;
	else if (str == "if_cmpge") return if_cmpge;
	else if (str == "if_icmplt") return if_icmplt;
	else if (str == "if_icmple") return if_icmple;
	else if (str == "if_icmpge") return if_icmpge;
	else if (str == "ifeq") return ifeq;
	else if (str == "ifne") return ifne;
	else if (str == "ifgt") return ifgt;
	else if (str == "ifge") return ifge;
	else if (str == "iflt") return iflt;
	else if (str == "ifle") return ifle;
	else if (str == "invokestatic") return invokestatic;
	else if (str == "invokevirtual") return invokevirtual;
	else if (str == "invokespecial") return invokespecial;
	else if (str == "return") return OP_DONE;
	else
		return NA;
}


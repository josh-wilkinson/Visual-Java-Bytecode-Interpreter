#pragma once

#define STACK_MAX 256

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <vector>

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
	if_icmpne,
	if_icmpeq,
	if_icmpgt,
	if_cmpge,
	if_icmplt,
	if_icmple,
	ifeq,
	ifne,
	ifgt,
	ifge,
	iflt,
	ifle,
	invokestatic,
	invokevirtual,
	/* stop execution */
	OP_DONE
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

uint64_t vmStackPop()
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


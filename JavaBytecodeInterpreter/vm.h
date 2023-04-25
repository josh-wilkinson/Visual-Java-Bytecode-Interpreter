#pragma once

#define STACK_MAX 256

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

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

} opcode;

typedef enum interpretResult
{
	SUCCESS,
	ERROR_DIVISION_BY_ZERO,
	ERROR_UNKNOWN_OPCODE
} interpretResult;

void vmReset()
{

}

void vmStackPush()
{

}

uint64_t vmStackPop()
{
	return NULL;
}

// interpreter code
interpretResult vmInterpret()
{
	vmReset();

	return SUCCESS;
}


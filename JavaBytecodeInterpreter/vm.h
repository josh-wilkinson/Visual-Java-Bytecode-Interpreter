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

	// Registers
	uint64_t var0;
	uint64_t var1;
	uint64_t var2;
	uint64_t var3;
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
interpretResult vmInterpret(codeLine program[256], int size) // program goes through code here
{
	vmReset();
	int i = 0;
	std::cout << "Interpreter started" << std::endl;
	int counter = 0;
	for (;;)
	{
		uint8_t instruction = program[i].instruction;
		i++;
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
				break;
			case iadd:
				vmStackPush(vmStackPop() + vmStackPop());
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
				break;
			case if_icmpeq:
				break;
			case if_icmpgt:
				break;
			case if_cmpge:
				break;
			case if_icmplt:
				break;
			case if_icmple:
				break;
			case if_icmpge:
				break;
			case ifeq:
				break;
			case ifne:
				break;
			case ifgt:
				break;
			case ifge:
				break;
			case iflt:
				break;
			case ifle:
				break;
			case iinc:
				break;
			case iload:
				// format: opcode operand
				// different way to iload_0 to iload_3
				break;
			case iload_0:
				vmStackPush(vm.var0);
				break;
			case iload_1:
				vmStackPush(vm.var1);
				break;
			case iload_2:
				vmStackPush(vm.var2);
				break;
			case iload_3:
				vmStackPush(vm.var3);
				break;
			case invokespecial:
				break;
			case invokestatic:
				break;
			case invokevirtual:
				break;
			case imul:
				vmStackPush(vmStackPop() * vmStackPop());
				break;
			case isub:
				vmStackPush(vmStackPop() - vmStackPop());
				break;
			case ishl:
				break;
			case ishr:
				break;
			case istore:
				// format: opcode operand
				// different way to istore_0 to istore_3
				break;
			case istore_0:
				vm.var0 = vmStackPop();
				break;
			case istore_1:
				vm.var1 = vmStackPop();
				break;
			case istore_2:
				vm.var2 = vmStackPop();
				break;
			case istore_3:
				vm.var3 = vmStackPop();
				break;
			case GOTO:
				for (int j = 0; j < size; j++)
				{
					if (program[j].lineNumber == program[i].operand1)
					{
						i = j;
						break;
					}
				}
				break;

			case OP_DONE:
				return SUCCESS;
			case NA:
				return ERROR_UNKNOWN_OPCODE;
			default:
				break;
		}
		counter++;
		std::cout << "Counter: " << counter << std::endl;
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
		{"return", OP_DONE},
	};

	if (mp.count(str) > 0) // if value exists in map
		return mp[str];
	else
		return NA;	
}





#pragma once

#include "core.h"

// call convention
// - push : arg..N
// - push : retval
// - push : func id
// - call : get id from top, set top = retn ip
// - >> pop : arg..N
// - >> ...
// - >> retn top-1 (top is retval)
// - cont here


struct VM
{
	enum BC
	{
		BC_HALT = 0,

		// stack[top] = arg;
		// top++;
		BC_PUSH_INT,
		BC_PUSH_FLOAT,
		BC_PUSH_STRING,
		BC_PUSH_FUNC,
		BC_PUSH_PTR,

		// top--;
		// stack[top + arg] = stack[top];
		BC_POP_INT,
		BC_POP_FLOAT,
		BC_POP_STRING,
		BC_POP_FUNC,
		BC_POP_PTR,

		// stack[top] = stack[top + arg];
		// top++;
		BC_DUP,

		// stack[top] = &stack[top + arg];
		// top++;
		BC_ADDR,

		// stack[top] = &stack[top + arg];
		// top++;
		BC_LOAD,

		// *stack[top + arg] = stack[top];
		BC_STORE,

		// stack[top] = ip;
		// ip = stack[top-1];
		// top++;
		BC_CALL,

		// ip = stack[top];
		// top--;
		BC_RETN,

		// stack[top + arg] = stack[top - 1] + stack[top - 2]
		// top--;
		// top--;
		BC_ADD_INT,
		BC_SUB_INT,
		BC_MUL_INT,
		BC_DIV_INT,
		BC_MOD_INT,

		// stack[top + arg] = stack[top - 1] + stack[top - 2]
		// top--;
		// top--;
		BC_ADD_FLOAT,
		BC_SUB_FLOAT,
		BC_MUL_FLOAT,
		BC_DIV_FLOAT,
		BC_MOD_FLOAT,

		// breakpoint
		BC_BRK,

		// debug info
		BC_DUMP_STACK,
		BC_DUMP_CODE,
	};

	enum TY
	{
		TY_INT,
		TY_FLOAT,
		TY_STRING,
		TY_FUNC,
		TY_PTR,
	};

	struct INST
	{
		BC bc;
		int32_t arg;
	};

	struct FRAME
	{
		INST* insts;
	};
	
	struct StackDebugInfo
	{
		int id;
		int offset;
		BC bc;

		union {
			void* arg_void;
			int arg_int;
			float arg_float;
			char* arg_str;
		};
	};

	struct FunctionDebugInfo
	{
		int fid;
		int offset;
		INST* insts;
		int count;
		const char* name;
	};

	mem8* _memblock;
	mem8* _stack;
	INST* _code;
	mem8* _data;

	int _top;
	int _ip;
	int* _ftable;
	int _fcount;

	StackDebugInfo* _stack_debug_info;
	FunctionDebugInfo* _function_debug_info;

	void init();
	void release();

	void step();
	void exec(INST inst);

	void execn(INST* insts, int count);

	void run();

	const char* bcstr(BC bc);
	int size(TY type);

	void print_stack(int count = 0);
	void print_code(int count = 0);
	void print_data(int count = 0);
};

#include <iostream>
#include <cstdio>
#include <cstring>
#include "Bytecodes.hpp"
using namespace std;

class VM {
	// data: is data memory or global memory. the size is passed to the constructor.
	int * data; // This could be pass to constructor.
	int * code;
	int stack[100]; // Arbitrary size set. *Check what value this could be.

	int ip;
	int sp = -1; // Begin below the stack.
	int fp;

	int TRUE = 1;
	int FALSE = 0;
	int datasize;

	public:
	bool trace = false;
	string output = "";

	VM(int* program, int startPoint, int datasize_) {
		code = program;
		ip = startPoint;
		data = (int*)malloc(sizeof(int)*datasize);
		datasize = datasize_;
	}

	void cpu() {
		bool running = true;
		while (running) {
			int opcode = code[ip]; // fetch.
			if (trace) printf("%-25s", disassemble(opcode));

			ip++;
			int v, a, addr; // aux
			string output = "";
			
			bool print = false;
			switch (opcode) {
				case HALT:
					running = false;
					break;
				case ICONST:
					v = code[ip];
					ip++;
					sp++;
					stack[sp] = v; // push to the stack.
					break;
				case PRINT:
					v = stack[sp];
					sp--; // pop on the stack.
					if (!trace) printf("%d ", v);
					break;
				case GSTORE:
					v = stack[sp];
					sp--;
					addr = code[ip];
					ip++;
					data[addr] = v;
					break;
				case GLOAD:
					addr = code[ip];
					ip++;
					sp++;
					stack[sp] = data[addr];
					break;
				case BR:
					ip = code[ip++];
					break;
				case IADD:
					v = stack[sp--];
					a = stack[sp--];
					stack[++sp] = a + v;
					break;
				case BRT:
					addr = code[ip++];
					if (stack[sp--] == TRUE) ip = addr;
					break;
				case ILT:
					a = stack[sp--];
					v = stack[sp--];
					stack[++sp] = (a < v) ? TRUE : FALSE;
					break;
			}

			if (trace) printf("%-25s", dumpStackMemory());
			if (trace) printf("%-30s\n", dumpDataMemory());
			
		}
		if (trace) dumpDataMemory2();
		if (trace) cout << "Output:\n" << output << endl;
		else cout << endl;

	}

	char * dumpDataMemory() {
			  char * buffer = (char*)malloc(sizeof(char)*50);
			  string tmp = "";
			  for (int i=0; i<datasize; i++) {
					tmp += to_string(data[i]) + " ";
			  }
			  sprintf(buffer, "data = [ %s]", tmp.c_str());
			  return buffer;
	}

	void dumpDataMemory2() {
			  cout << "Data Memory:\n";
			  for (int i=0; i<datasize; i++) {
					printf("%04d: %d\n", i, data[i]);
			  }
	}

	char * dumpStackMemory() {
			  char * buffer = (char*)malloc(sizeof(char)*40);
			  string tmp = "";
			  for (int i=0; i<=sp; i++) {
					tmp += to_string(stack[i]) + " ";
			  }
			  sprintf(buffer, "stack = [ %s]", tmp.c_str());
			  return buffer;
	}

	char * disassemble(int opcode) {
			char * out = (char*)malloc(sizeof(char)*40);
			char aux[10] = "";
			Instructions inst = instr[opcode];
			sprintf(out, "%04d: [%d] %-7s ", ip, opcode, instr[opcode].get_name().c_str());
			if (inst.get_nOpnds() == 1)
					sprintf(aux, "%d", code[ip+1]);
			else if (inst.get_nOpnds() == 2)
					sprintf(aux, "%d %d", code[ip+1], code[ip+2]);
			else if (inst.get_nOpnds() == -1) {
				output += to_string(stack[sp]) + " ";
				sprintf(aux, "[%d]", stack[sp]);
			}
			strcat(out, aux);
			return out;
	}
};



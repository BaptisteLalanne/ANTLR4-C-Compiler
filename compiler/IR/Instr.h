#include "../SymbolTable.h"

#include <iostream>
#include <algorithm>
#include <list>

class BasicBlock;

/* The class for one instruction */
class Instr {
 
	public:

		typedef enum {
			ldconst,
			copy,
            aff,
			rmem,
			wmem,
			wparam,
			rparam,
			call,
			cmp_eq,
			cmp_neq,
			cmp_lt,
			cmp_gt,
			op_or,
			op_xor,
			op_and,
			op_add,
			op_sub,
			op_mul,
			op_div,
			op_mod,
			op_not,
			op_minus,
			ret,
			prologue,
			conditional_jump,
			absolute_jump
		} Operation;

		Instr(BasicBlock* bb, Instr::Operation op, vector<string> params, SymbolTable* sT);

		void generateASM(ostream &o); 

		static unordered_map<string, string> AMD86_paramRegisters;

		Operation getOp() { return op; };

        vector<string> getParams() { return params; };

		bool propagateConst(bool needsDefinition, list<Instr*>::iterator it, list<Instr*> instrList);

		bool checkNeedForLoadConst(varStruct *s1, varStruct *s2, varStruct *s3, list<Instr*>::iterator it, list<Instr*> instrList, Instr::Operation op);

		SymbolTable* getSymbolTable(){ return symbolTable; };
	private:

		/* The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
		BasicBlock* bb; 

		/* The operator of the instruction */
		Operation op;

		/* The associated symbol table*/
		SymbolTable* symbolTable;

		/* For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
		vector<string> params; 
		// if you subclass Instr, each Instr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design.

};
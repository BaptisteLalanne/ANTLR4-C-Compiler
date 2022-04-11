#include "../SymbolTable.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <list>

class BasicBlock;

/* The class for one instruction */
class Instr {
 
	public:

		/* All allowed operations */
		typedef enum {
			ldconst,
			decl,
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
			cmp_eqlt,
			cmp_eqgt,
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
            op_plus_equal,
            op_sub_equal,
            op_mult_equal,
            op_div_equal,
			ret,
			prologue,
			conditional_jump,
			absolute_jump
		} Operation;

		/* Constructor */
		Instr(BasicBlock* bb, Instr::Operation op, vector<string> params, SymbolTable* sT);

		/* Generate the ASM code corresponding to the Instruction */
		void generateASM(ostream &o); 

		/* Try to propagate the constants in the operation */
		bool propagateConst(bool needsDefinition, list<Instr*>::iterator it, list<Instr*> instrList);

		/* Check if it is needed to load a constant before an operation (for example var + const, where const hasn't been loaded by the ASM code) */
		/* This is also where we simplify trivial operations such as +0 or *1 */
		bool checkNeedForLoadConst(varStruct *s1, varStruct *s2, varStruct *s3, list<Instr*>::iterator it, list<Instr*> instrList, Instr::Operation op);

		/* Accessors */
		SymbolTable* getSymbolTable(){ return symbolTable; };
		Operation getOp() { return op; };
        vector<string> getParams() { return params; };

		/* Static map containing the AMD86 parameter register names (for each type, int or char)*/
		static unordered_map<string, vector<string>> AMD86_paramRegisters;

	private:

		/* The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
		BasicBlock* bb; 

		/* The operator of the instruction */
		Operation op;

		/* The associated symbol table*/
		SymbolTable* symbolTable;

		/* Params of the instructions (typically src, dest, tmpVar) */
		vector<string> params; 


};
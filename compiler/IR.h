#ifndef IR_H
#define IR_H

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

// Declarations from the parser -- replace with your own
#include "SymbolTable.h"

class BasicBlock;
class CFG;
class DefFonction;

//! The class for one 3-address instruction
class Instr {
 
   public:

	/** The instructions themselves -- feel free to subclass instead */
	typedef enum {
		ldconst,
		copy,
		rmem,
		wmem,
		call,
		cmp_eq,
		cmp_neq,
		cmp_lt,
		cmp_le,
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
		ret
	} Operation;

	/* Constructor */
	Instr(BasicBlock* bb, Operation op, vector<string> params);
	
	/** Actual code generation */
	void generateASM(ostream &o); /* x86 assembly code generation for this IR instruction */
	
	
 private:

	BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
	Operation op;
	vector<string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
	// if you subclass Instr, each Instr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design.

	varStruct getSymbol(string name);

};






/**  The class for a basic block */

/* A few important comments.
	 Instr has no jump instructions.
	 cmp_* instructions behaves as an arithmetic two-operand instruction (add or mult),
	  returning a boolean value (as an int)

	 Assembly jumps are generated as follows:
	 BasicBlock::gen_asm() first calls Instr::gen_asm() on all its instructions, and then 
		    if  exit_true  is a  nullptr, 
            the epilogue is generated
        else if exit_false is a nullptr, 
          an unconditional jmp to the exit_true branch is generated
				else (we have two successors, hence a branch)
          an instruction comparing the value of test_var_name to true is generated,
					followed by a conditional branch to the exit_false branch,
					followed by an unconditional branch to the exit_true branch
	 The attribute test_var_name itself is defined when converting 
  the if, while, etc of the AST  to IR.

Possible optimization:
     a cmp_* comparison instructions, if it is the last instruction of its block, 
       generates an actual assembly comparison 
       followed by a conditional jump to the exit_false branch
*/
class BasicBlock {

	public:

		BasicBlock(CFG* cfg, string label);
		void generateASM(ostream &o); /* x86 assembly code generation for this basic block (very simple) */
		void addInstr(Instr::Operation op, vector<string> params);

		// Getter CFG 
		CFG* getCFG(){return cfg;};

	protected:

		// No encapsulation whatsoever here. Feel free to do better.
		BasicBlock* exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */ 
		BasicBlock* exit_false; /**< pointer to the next basic block, false branch. If nullptr, the basic block ends with an unconditional jump */
		string label; /**< label of the BB, also will be the label in the generated code */
		CFG* cfg; /** < the CFG where this block belongs */
		vector<Instr*> instrList; /** < the instructions themselves. */
		string test_var_name;  /** < when generating IR code for an if(expr) or while(expr) etc, store here the name of the variable that holds the value of expr */
 
};


/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
	 The entry block is the one with the same label as the AST function name.
	   (it could be the first of bbs, or it could be defined by an attribute value)
	 The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG {

	public:

		CFG(SymbolTable& st) : symbolTable(st) {};
		void createBB(BasicBlock* bb); 

		// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
		void generateASM(ostream& o);
		string IR_reg_to_asm(string reg); /* helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
		void gen_asm_prologue(ostream& o); // TODO: we could include them in gen_asm()
		void gen_asm_epilogue(ostream& o);
		BasicBlock* getCurrentBB() const;
		// Getter symbolTable
		SymbolTable& getSymbolTable(){return symbolTable;};

	protected:

		BasicBlock* currentBB;
		vector<BasicBlock*> bbList; /* all the basic blocks of this CFG */
		SymbolTable& symbolTable;

		

};


#endif

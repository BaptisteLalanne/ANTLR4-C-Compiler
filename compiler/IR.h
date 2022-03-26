#ifndef IR_H
#define IR_H

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include "SymbolTable.h"

class BasicBlock;
class CFG;
class DefFonction;

/* The class for one instruction */
class Instr {
 
   public:

	typedef enum {
		ldconst,
		copy,
		rmem,
		wmem,
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
		epilogue
	} Operation;

	Instr(BasicBlock* bb, Instr::Operation op, vector<string> params);

	void generateASM(ostream &o); 
	
	
 private:

	/* The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
	BasicBlock* bb; 

	/* The operator of the instruction */
	Operation op;

	/* For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
	vector<string> params; 
	// if you subclass Instr, each Instr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design.

	/* Symbol table accessors */
	varStruct getSymbol(string name);
	bool hasSymbol(string name);
	SymbolTable& getSymbolTable();


};

/**  The class for a basic block */
class BasicBlock {

	public:

		BasicBlock(CFG* cfg, string label);
		~BasicBlock();

		void generateASM(ostream &o); 
		void addInstr(Instr::Operation op, vector<string> params);

		CFG* getCFG() { return cfg; };

	protected:

		/* Pointer to the next basic block, true branch. If nullptr, return from procedure */ 
		BasicBlock* exit_true;  

		/* Pointer to the next basic block, false branch. If nullptr, the basic block ends with an unconditional jump */
		BasicBlock* exit_false; 

		/* Label of the BB, also will be the label in the generated code */
		string label; 

		/* The CFG this block belongs to */
		CFG* cfg; 

		/* The instructions themselves */
		vector<Instr*> instrList; 

		/* When generating IR code for an if(expr) or while(expr) etc, store here the name of the variable that holds the value of expr */
		string test_var_name;  
 
};


/** The class for the control flow graph, also includes the symbol table */

/* 
A few important comments:
	The entry block is the one with the same label as the AST function name.
	(it could be the first of bbs, or it could be defined by an attribute value)
	The exit block is the one with both exit pointers equal to nullptr.
	(again it could be identified in a more explicit way)
*/
class CFG {

	public:

		CFG(SymbolTable& st);
		~CFG();

		void createBB(); 
		BasicBlock* getCurrentBB();
		void setCurrentBB(BasicBlock* bb);

		void generateASM(ostream& o);

		SymbolTable& getSymbolTable() { return symbolTable; };

	protected:

		/* Generate ASM prologue and epilogues */
		void generateASMPrologue(ostream& o);
		void generateASMEpilogue(ostream& o);
		
		/* The list of basic blocks */
		vector<BasicBlock*> bbList; 

		/* The current basic block*/
		BasicBlock* currentBB;

		/* The associated symbol table*/
		SymbolTable& symbolTable;

};


#endif

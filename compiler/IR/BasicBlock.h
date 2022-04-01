#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

#include "../SymbolTable.h"
#include "Instr.h"

class CFG;

using namespace std;

/**  The class for a basic block */
class BasicBlock {

	public:

		BasicBlock(CFG* cfg, string label);
		~BasicBlock();

		void generateASM(ostream &o); 
		void addInstr(Instr::Operation op, vector<string> params, SymbolTable* sT);
		void optimization();
		CFG* getCFG() { return cfg; };
        bool lookForCopyInstr(string varName);
		void setExitTrue(BasicBlock* bb);
		BasicBlock* getExitTrue();
		void setExitFalse(BasicBlock* bb);
		BasicBlock* getExitFalse();
        vector<Instr*> getInstrList() { return instrList; };
		string getLabel();
		void setTestVarName(string n) { testVarName = n; }
		string getTestVarName() { return testVarName; }
		/* Symbol table accessors */
		varStruct getSymbol(string name);
	

	protected:

		/* Pointer to the next basic block, true branch. If nullptr, return from procedure */ 
		BasicBlock* exit_true = nullptr;  

		/* Pointer to the next basic block, false branch. If nullptr, the basic block ends with an unconditional jump */
		BasicBlock* exit_false = nullptr; 

		/* Label of the BB, also will be the label in the generated code */
		string label; 

		/* The CFG this block belongs to */
		CFG* cfg; 

		/* The instructions themselves */
		vector<Instr*> instrList; 

		/* When generating IR code for an if(expr) or while(expr) etc, store here the name of the variable that holds the value of expr */
		string testVarName;  
 
};
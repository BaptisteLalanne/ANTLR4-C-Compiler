#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <initializer_list>
#include <unordered_set>
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
		bool evaluateConstInstr(list<Instr*>::iterator it);
		bool evaluateTrivialOperationInstr(list<Instr*>::iterator it);
        int lookForAffInstr(string varName, unordered_set<BasicBlock*> & bbVisited,int countAffect = 0);
		void setExitTrue(BasicBlock* bb);
		BasicBlock* getExitTrue();
		void setExitFalse(BasicBlock* bb);
		BasicBlock* getExitFalse();
		void setTestVarName(string n) { testVarName = n; }
		string getTestVarName() { return testVarName; }
        list<Instr*> getInstrList() { return instrList; };
		string getLabel();
		CFG* getCFG() { return cfg; };

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
		list<Instr*> instrList; 

		/* When generating IR code for an if(expr) or while(expr) etc, store here the name of the variable that holds the value of expr */
		string testVarName;  
 
};
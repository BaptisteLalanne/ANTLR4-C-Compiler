#ifndef CFG_H
#define CFG_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <initializer_list>
#include "BasicBlock.h"

class CFG {

	public:

		CFG();
		~CFG();
		
		BasicBlock* createBB(); 
		BasicBlock* getCurrentBB();
		void setCurrentBB(BasicBlock* bb);

		void generateASM(ostream& o);
		void optimizeIR();
		void optimizeASM(stringstream& iS, ostream& oS);
		void initStandardFunctions(SymbolTable* st);

		bool getOptimized() { return optimized; };
		void setOptimized(bool o) { optimized=o; };

	protected:

		/* Generate ASM for standard functions */
		void generateStandardFunctions(ostream& o);
		void generatePutchar(ostream& o);
		void generateGetchar(ostream& o);

		/* Generate ASM prologue and epilogues */
		void generateASMPrologue(ostream& o);
		void generateASMEpilogue(ostream& o);
		
		/* The list of basic blocks */
		vector<BasicBlock*> bbList; 

		/* Option to add optimization */
		bool optimized;

		/* The current basic block*/
		BasicBlock* currentBB;

		/* Helper functions to split a stream in sublines*/
		vector<string> splitString(string str, string separator);
	
	private:

		bool mustWritePutchar = false;
		bool mustWriteGetchar = false;
};

#endif
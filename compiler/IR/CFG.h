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

		/* Constructor / Destructor */
		CFG();
		~CFG();
		
		/* Generate the ASM code corresponding to the CFG*/
		void generateASM(ostream& o);

		/* Create a new Basic Block */
		BasicBlock* createBB(); 
		
		/* Optimize the Instructions of the CFG */
		void optimizeIR();

		/* Optimize the generated ASM code (contained in iS), to be put into oS */
		void optimizeASM(stringstream& iS, ostream& oS);

		/* Initialize standard functions (putchar, getchar...) */
		void initStandardFunctions(SymbolTable* st);

		/* Accessors */
		bool getOptimized() { return optimized; };
		void setOptimized(bool o) { optimized=o; };
		BasicBlock* getCurrentBB();
		void setCurrentBB(BasicBlock* bb);

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
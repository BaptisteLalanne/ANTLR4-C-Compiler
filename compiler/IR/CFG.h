#ifndef CFG_H
#define CFG_H

#include <vector>
#include <string>
#include <iostream>
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

		void optimize();

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
};

#endif
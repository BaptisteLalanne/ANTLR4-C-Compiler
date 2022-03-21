/*************************************************************************
                          PLD Compiler : IR
                          -----------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

//---- Implementation of class <IR> (file IR.cpp) ------/

#include "IR.h"
#include <iostream>

using namespace std;


/* --------------------------------------------------------------------- */
BasicBlock::BasicBlock(CFG* cfg, string label) : cfg(cfg), label(label) { }

void BasicBlock::addInstr(Instr::Operation op, vector<string> params) {

	// Create Instr, add it to the list
	Instr* instr = new Instr(this, op, params);
	instrList.add(instr);

}

/* --------------------------------------------------------------------- */
CFG::CFG() {
	createBB();
}

BasicBlock* CFG::getCurrentBB() const {
	return currentBB;
}

voic CFG::createBB() {

	// Generate BB name
	string bbName = "bb" + to_string(bbList.size());

	// Create BB, add it to the list
	BasicBlock* bb = new BasicBlock(this, bbName);
	bbList.add(bb);

}

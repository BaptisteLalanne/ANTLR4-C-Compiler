/*************************************************************************
                          PLD Compiler : CFG
                          -----------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/


#include "CFG.h"


using namespace std;

CFG::CFG() {
	setCurrentBB(createBB());
}

CFG::~CFG() {
	for (BasicBlock* bb : bbList) {
		delete bb;
	}
}

BasicBlock* CFG::createBB() {
	string bbName = "bb" + to_string(bbList.size());
	BasicBlock* bb = new BasicBlock(this, bbName);
	bbList.push_back(bb);
	currentBB = bb;
	return bb;
}

void CFG::generateASM(ostream& o) {
	generateASMPrologue(o);
	for (BasicBlock* bb : bbList) {
		bb->generateASM(o);
	}
	generateASMEpilogue(o);
}

void CFG::optimize() {
	for (BasicBlock* bb : bbList) {
		bb->optimization();
	}
}

void CFG::generateASMPrologue(ostream& o) {
	o << ".text" << endl;
}
void CFG::generateASMEpilogue(ostream& o) {
}

BasicBlock* CFG::getCurrentBB() {
	return currentBB;
}
void CFG::setCurrentBB(BasicBlock* bb) {
	currentBB = bb;
}
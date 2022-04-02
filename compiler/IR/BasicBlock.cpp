/*************************************************************************
                          PLD Compiler : BasicBlock
                          -----------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/


#include "BasicBlock.h"
#include <algorithm>

using namespace std;


BasicBlock::BasicBlock(CFG* cfg, string label) : cfg(cfg), label(label) { }

BasicBlock::~BasicBlock() {
	for (Instr* i : instrList) {
		delete i;
	}
}

void BasicBlock::optimization() {
	
	// Erase instructions where constants can be propagated
	instrList.erase(remove_if(instrList.begin(), instrList.end(), 
	[this](Instr* i) { 
        bool deleteInstr = false;
        // If this is a copy instruction, check if there is another copy instruction with the same variable at the left
        vector<string> params = i->getParams(); 
        if (i->getOp() == Instr::aff) {
            string varName = params[1];
            bool needsDefinition = (this->loofForAffInstr(varName) > 1);
            // If there is no other copy with the same variable, we can try to propagate
			deleteInstr = i->propagateConst(needsDefinition);
        }  
        else {
            deleteInstr = i->propagateConst(false);
        }
        return deleteInstr;
    }), instrList.end());
	
	// Erase trivial operational instructions
	
	// Erase redundant copies

}

int BasicBlock::loofForAffInstr(string varName, int countAffect) {

	for (Instr* i : instrList) {
        if(i->getOp() == Instr::aff && i->getParams()[1] == varName) {
			countAffect++;
        }
    }

	if (exit_true && countAffect <= 1) {
		countAffect += exit_true->loofForAffInstr(varName, countAffect);
	} 
    if (exit_false && countAffect <= 1) {
		countAffect += exit_false->loofForAffInstr(varName, countAffect);
	}

	return countAffect;
}

void BasicBlock::addInstr(Instr::Operation op, vector<string> params, SymbolTable* sT) {
	Instr* instr = new Instr(this, op, params, sT);
	instrList.push_back(instr);
}

void BasicBlock::generateASM(ostream &o) {
	cout << label << ":" << endl;
	for (Instr* i : instrList) {
		i->generateASM(o);
	}
}

void BasicBlock::setExitTrue(BasicBlock* bb) {
	this->exit_true = bb;
}

BasicBlock* BasicBlock::getExitTrue(){
	return this->exit_true;
}

void BasicBlock::setExitFalse(BasicBlock* bb) {
	this->exit_false = bb;
}

BasicBlock* BasicBlock::getExitFalse(){
	return this->exit_false;
}

string BasicBlock::getLabel(){
	return this->label;
}
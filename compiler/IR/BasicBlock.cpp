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
        bool canPropagate = false;
        // If this is a copy instruction, check if there is another copy instruction with the same variable at the left
        vector<string> params = i->getParams(); 
        if (i->getOp() == Instr::copy) {
            string varName = params[0];
            bool needsDefinition = this->lookForCopyInstr(varName);
            // If there is no other copy with the same variable, we can try to propagate
            if(!needsDefinition) {
                canPropagate = i->propagateConst();
            }
        }  
        else {
            canPropagate = i->propagateConst();
        }
        return canPropagate;
    }), instrList.end());
	
	// Erase trivial operational instructions
	
	// Erase redundant copies

}

bool BasicBlock::lookForCopyInstr(string varName) {
    
	bool needsDefinition = false;

	for (Instr* i : instrList) {
        if(i->getOp() == Instr::aff) {
            needsDefinition = true;
        }
    }

	if (exit_true && !needsDefinition) {
		needsDefinition = exit_true->lookForCopyInstr(varName);
	} 
    if (exit_false && !needsDefinition) {
		needsDefinition = exit_false->lookForCopyInstr(varName);
	}
	
	return needsDefinition;
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
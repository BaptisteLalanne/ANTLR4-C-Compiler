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

bool BasicBlock::evaluateConstInstr(list<Instr*>::iterator it) {
	bool deleteInstr = false;
	Instr* i = *it;
	// If this is a aff instruction, check if there is another aff instruction with the same variable at the left
	vector<string> params = i->getParams(); 
	if (i->getOp() == Instr::aff) {
		string varName = params[1];
		unordered_set<BasicBlock*> bbVisited;
		bool needsDefinition = (this->lookForAffInstr(varName,bbVisited) > 1);
		// If there is no other aff with the same variable, we can propagate (and eventually delete)
		deleteInstr = i->propagateConst(needsDefinition, it, instrList);
	}  
	else {
		deleteInstr = i->propagateConst(false, it, instrList);
	}
	return deleteInstr;
}

bool BasicBlock::evaluateTrivialOperationInstr(list<Instr*>::iterator it) {
	bool deleteInstr = false;
	Instr* i = *it;
	SymbolTable* sT = i->getSymbolTable();
	vector<string> params = i->getParams(); 
	// If this is a trivial operation (add or sub 0, mul 1, div by 1), delete the instruction 
	varStruct* s1;
	varStruct* s2;
	switch(i->getOp()) {
		case Instr::op_add:
		case Instr::op_sub:
			s1 = sT->getVar(params[0]);
			s2 = sT->getVar(params[1]);
			if ((s1->constPtr && *s1->constPtr == 0) || (s2->constPtr && *s2->constPtr == 0)) {
				deleteInstr = true;
			}
			break;
		case Instr::op_mul:
			s1 = sT->getVar(params[0]);
			s2 = sT->getVar(params[1]);
			if ((s1->constPtr && *s1->constPtr == 1) || (s2->constPtr && *s2->constPtr == 1)) {
				deleteInstr = true;
			}
			break;
		case Instr::op_div:
			s2 = sT->getVar(params[1]);
			if (s2->constPtr && *s2->constPtr == 1) {
				deleteInstr = true;
			}
			break;
	}
	return deleteInstr;
}

void BasicBlock::optimization() {
	
	list<Instr*>::iterator it;
	
	it = instrList.begin();
	while(it != instrList.end()) {
		bool deleteConstInstr = evaluateConstInstr(it);
		if(deleteConstInstr) {
			it = instrList.erase(it);
		}
		else ++it;
	}
}

int BasicBlock::lookForAffInstr(string varName, unordered_set<BasicBlock*> & bbVisited, int countAffect) {
	bbVisited.insert(this);
	for (Instr* i : instrList) {
        if(i->getOp() == Instr::aff && i->getParams()[1] == varName) {
			countAffect++;
        }
    }
	if (exit_true && countAffect <= 1 && bbVisited.find(exit_true) == bbVisited.end()) {
		countAffect += exit_true->lookForAffInstr(varName, bbVisited, countAffect);
	} 
    if (exit_false && countAffect <= 1 && bbVisited.find(exit_false) == bbVisited.end()) {
		countAffect += exit_false->lookForAffInstr(varName, bbVisited, countAffect);
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
	/*if (exit_false) {
		cout << "	cmpl    $0, " << testVarMemoryOffset << "(%rbp)" << endl;
		cout << "	je    " << exit_false->label << endl;
	}
	if (exit_true){
		cout << "	jmp    " << this->exit_true->label << endl;
	}*/
}

/*
void BasicBlock::generateASM(ostream &o) {
	cout << label << ":" << endl;
	for (Instr* i : instrList) {
		i->generateASM(o);
	}
	if (exit_false) {
		cout << "	cmpl    $0, " << getSymbol(test_var_name).memoryOffset << "(%rbp)" << endl;
		cout << "	je    " << exit_false->label << endl;
	}
	if (exit_true){
		cout << "	jmp    " << this->exit_true->label << endl;
	}
}
*/

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
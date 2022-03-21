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

void CFG::createBB() {

	// Generate BB name
	string bbName = "bb" + to_string(bbList.size());

	// Create BB, add it to the list
	BasicBlock* bb = new BasicBlock(this, bbName);
	bbList.add(bb);

}

void Instr::generateASM(ostream &o) {
	// TODO: generate ASM for one instruction

	/*
		ldconst,
		copy,
		add,
		sub,
		mul,
		rmem,
		wmem,
		call,
		ret,
		cmp_eq,
		cmp_lt,
		cmp_le

		copy var1 var2
		copy var1 $3
		copy var1 'a
	*/


	switch (op) {
		case call:
			string param1 = params.at(0);
			o << ".globl " << param1 << endl;
			o << param1 <<":"<<endl;
			o << "pushq	%rbp"<<endl;
			o << "movq	%rsp, %rbp"<<endl;
			break;
		case ret:
			o << "popq	%rbp"<<endl;
			o << "ret"<<endl;
			break;
		case ldconst:
			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);

			// get variables
			varStruct firstVar = getSymbol(param1);
			// varStruct secondVar = getSymbol(param2);
			
			if (param2[0] == '\'') {
				char tmp = param2[1];
			} else if (param2[0] == '$') {
				for (int i = 0; i<param2.size();i++){
					 = param2[i];
				}
					
			} else {
				// error
			}

			
			break;
		case copy:

			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);

			// get variables
			varStruct firstVar = getSymbol(param1);
			varStruct secondVar = getSymbol(param2);

			// get offsets
			int var1Offset = firstVar.memoryOffset;
			int var2Offset = secondVar.memoryOffset;

			// Write assembly instructions
			o << "	movl	" << var2Offset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << var1Offset << "(%rbp)" << endl;
	
			break;
		case add:

			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);
			string param3 = params.at(2);

			// check if second param is a const
			if (param3[0] == '\'') {
				// const char
			} else if (param2[0] == '$') {
				// const int
			} else {
				// not a const

				// get variables
				varStruct firstVar = getSymbol(param1);
				varStruct secondVar = getSymbol(param2);

				// get offsets
				int var1Offset = firstVar.memoryOffset;
				int var2Offset = secondVar.memoryOffset;

				o << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
				o << "	addl	" << var2Offset << "(%rbp), %eax" << endl;
			}
			
			break;
		case sub:
		
			break;
		case mul:
		
			break;
		case rmem: // read memory
			
			break;
		case wmem: // write memory
		
			break;
		case call:
			// not yet implemented
			break;
		case cmp_eq:

			break;
		case cmp_lt:

			break;
		case cmp_le:

			break;

	}
	
}

void BasicBlock::generateASM(ostream &o) {
	// TODO: parse instructions, generate ASM for each instruction
}

void CFG::generateASM(ostream& o) {
	gen_asm_prologue();

	// TODO: parse blocks, generate ASM for each block
	

	gen_asm_epilogue();
}

varStruct Instr::getSymbol(string name) {
	return this->bb->getCFG()->getSymbolTable().getVar(name);
}
int voiture = 10;

void CFG::gen_asm_prologue(ostream& o) {
	o << ".text" << endl;
}

void CFG::gen_asm_epilogue(ostream& o) {
}
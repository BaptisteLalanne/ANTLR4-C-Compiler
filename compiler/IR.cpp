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
		cmp_eq,
		cmp_lt,
		cmp_le

		copy var1 var2
		copy var1 $3
		copy var1 'a
	*/



	switch (op) {

		case ldconst:

			// Get params
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

		case op_add:

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

		case op_xor:

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	xorl	" <<  getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;

		case op_and:

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	andl	" <<  getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;

		case op_mul:

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	imull	" << getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;

		case op_div:

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cltd" << endl;
			o << "	idivl	" << getSymbol(var2).memoryOffset << "(%rbp)" << endl; 
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;

		case op_mod:

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cltd" << endl;
			o << "	idivl	" << getSymbol(var2).memoryOffset << "(%rbp)" << endl; 
			o << "	movl	%edx, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;

		case op_not:

			// Get params
			string var = params.at(0);
			string tmp = params.at(1);

			// Write ASM
			o << "	cmpl	$0, " << getSymbol(var).memoryOffset << "(%rbp)" << endl;
			o << "	sete	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;

		case op_minus:

			// Get params
			string var = params.at(0);
			string tmp = params.at(1);

			// Write ASM
			o << "	movl	" << getSymbol(var).memoryOffset << "(%rbp), %eax" << endl;
			o << "	negl	%eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;

		case rmem: 
			// not yet implemented
			break;

		case wmem: 
			// not yet implemented
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
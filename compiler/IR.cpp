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
	instrList.push_back(instr);

}

void BasicBlock::generateASM(ostream &o) {
	for (Instr* i : instrList) {
		i->generateASM(o);
	}
}

BasicBlock* CFG::getCurrentBB() {
	return currentBB;
}

/* --------------------------------------------------------------------- */
CFG::CFG(SymbolTable& st) : symbolTable(st) {
	createBB();
}

void CFG::createBB() {

	// Generate BB name
	string bbName = "bb" + to_string(bbList.size());

	// Create BB, add it to the list
	BasicBlock* bb = new BasicBlock(this, bbName);
	bbList.push_back(bb);

}

void CFG::generateASM(ostream& o) {
	gen_asm_prologue(o);
	for (BasicBlock* bb : bbList) {
		bb->generateASM(o);
	}
	gen_asm_epilogue(o);
}

void CFG::gen_asm_prologue(ostream& o) {
	o << ".text" << endl;
}

void CFG::gen_asm_epilogue(ostream& o) {
}

/* --------------------------------------------------------------------- */
Instr::Instr(BasicBlock* bb, Instr::Operation op, vector<string> params) : bb(bb), op(op), params(params) {}

varStruct Instr::getSymbol(string name) {
	return this->bb->getCFG()->getSymbolTable().getVar(name);
}

bool Instr::hasSymbol(string name) {
	return this->bb->getCFG()->getSymbolTable().hasVar(name);
}

void Instr::generateASM(ostream &o) {

	switch (op) {

		case Instr::call:
		{
			string param1 = params.at(0);

			o << ".globl " << param1 << endl;
			o << param1 << ":" << endl;
			o << "pushq	%rbp" << endl;
			o << "movq	%rsp, %rbp" << endl;

			break;
		}

		case Instr::ret:
		{

			// Get params
			string param1 = params.at(0);

			// if var exists
			if (hasSymbol(param1)) {
				varStruct var = getSymbol(param1);
				o << "	movl	" << var.memoryOffset << "(%rbp), %eax"<< endl;
			}
			// if it is a const
			else {
				int constValue;
				if (param1[0] == '\'') {
					constValue = int(param1[1]);
				} else if (param1[0] == '$') {
					constValue = stoi(param1.substr(1,param1.size()-1));	
				} else {
					// error
				}
				o << "	movl	$" << constValue << ", %eax" << endl;
			}

			o << "popq	%rbp"<<endl;
			o << "ret"<<endl;

			break;
		}

		case Instr::ldconst:
		{
			// Get params
			string param1 = params.at(0);
			string param2 = params.at(1);

			// get variables
			varStruct firstVar = getSymbol(param1);
			
			int constValue;
			if (param2[0] == '\'') {
				constValue = int(param2[1]);
			} else if (param2[0] == '$') {
				constValue = stoi(param2.substr(1,param2.size()-1));	
			} else {
				// error
			}

			int var1Offset = firstVar.memoryOffset;

			// Write assembly instructions
			o << "	movl	$" << constValue << ", %eax" << endl;
			o << "	movl	%eax, " << var1Offset << "(%rbp)" << endl;

			break;
		}

		case Instr::copy:
		{
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
		}

		case Instr::op_add:
		{
			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);
			string param3 = params.at(2);

			// get variables
			varStruct firstVar = getSymbol(param1);
			varStruct secondVar = getSymbol(param2);
			varStruct thirdVar = getSymbol(param3);

			// get offsets
			int var1Offset = firstVar.memoryOffset;
			int var2Offset = secondVar.memoryOffset;
			int var3Offset = thirdVar.memoryOffset;

			o << "	movl	" << var2Offset << "(%rbp), %eax" << endl;
			o << "	addl	" << var3Offset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << var1Offset << "(%rbp)" << endl;
			
			break;
		}

		case Instr::op_sub:
		{
			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);
			string param3 = params.at(2);

			// get variables
			varStruct firstVar = getSymbol(param1);
			varStruct secondVar = getSymbol(param2);
			varStruct thirdVar = getSymbol(param3);

			// get offsets
			int var1Offset = firstVar.memoryOffset;
			int var2Offset = secondVar.memoryOffset;
			int var3Offset = thirdVar.memoryOffset;

			o << "	movl	" << var2Offset << "(%rbp), %eax" << endl;
			o << "	subl	" << var3Offset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << var1Offset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_xor:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	xorl	" <<  getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_and:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	andl	" <<  getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_mul:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	imull	" << getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_div:
		{
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
		}

		case Instr::op_or:
		{
			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);
			string param3 = params.at(2);

			// get variables
			varStruct var1 = getSymbol(param1);
			varStruct var2 = getSymbol(param2);
			varStruct tmp = getSymbol(param3);

			int var1Offset = var1.memoryOffset;
			int var2Offset = var2.memoryOffset;
			//Do Or
			o << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
			o << "	orl	" << var2Offset << "(%rbp), %eax" << endl;
			
			o << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
			
			break;
		}

		case Instr::op_mod:
		{
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
		}

		case Instr::op_not:
		{
			// Get params
			string var = params.at(0);
			string tmp = params.at(1);

			// Write ASM
			o << "	cmpl	$0, " << getSymbol(var).memoryOffset << "(%rbp)" << endl;
			o << "	sete	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_minus:
		{
			// Get params
			string var = params.at(0);
			string tmp = params.at(1);

			// Write ASM
			o << "	movl	" << getSymbol(var).memoryOffset << "(%rbp), %eax" << endl;
			o << "	negl	%eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::rmem: 
			// not yet implemented
			break;

		case Instr::wmem: 
			// not yet implemented
			break;

		case Instr::cmp_eq:
		{
			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);
			string param3 = params.at(2);

			// get variables
			varStruct var1 = getSymbol(param1);
			varStruct var2 = getSymbol(param2);
			varStruct tmp = getSymbol(param3);

			int var1Offset = var1.memoryOffset;
			int var2Offset = var2.memoryOffset;

			o << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
			o << "	cmpl	" << var2Offset << "(%rbp), %eax" << endl;
			o << "	sete	%al" << endl;

			o << "	movzbl	%al, %eax" << endl;

			// Write expression result (which is in %eax) in new var
			o << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_neq:
		{
			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);
			string param3 = params.at(2);

			// get variables
			varStruct var1 = getSymbol(param1);
			varStruct var2 = getSymbol(param2);
			varStruct tmp = getSymbol(param3);

			int var1Offset = var1.memoryOffset;
			int var2Offset = var2.memoryOffset;

			o << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
			o << "	cmpl	" << var2Offset << "(%rbp), %eax" << endl;
			o << "	setne	%al" << endl;

			o << "	movzbl	%al, %eax" << endl;

			// Write expression result (which is in %eax) in new var
			o << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_lt:
		{
			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);
			string param3 = params.at(2);

			// get variables
			varStruct var1 = getSymbol(param1);
			varStruct var2 = getSymbol(param2);
			varStruct tmp = getSymbol(param3);

			int var1Offset = var1.memoryOffset;
			int var2Offset = var2.memoryOffset;

			o << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
			o << "	cmpl	" << var2Offset << "(%rbp), %eax" << endl;
			o << "	setl	%al" << endl;

			o << "	movzbl	%al, %eax" << endl;

			// Write expression result (which is in %eax) in new var
			o << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_gt:
		{
			// get param
			string param1 = params.at(0);
			string param2 = params.at(1);
			string param3 = params.at(2);

			// get variables
			varStruct var1 = getSymbol(param1);
			varStruct var2 = getSymbol(param2);
			varStruct tmp = getSymbol(param3);

			int var1Offset = var1.memoryOffset;
			int var2Offset = var2.memoryOffset;

			o << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
			o << "	cmpl	" << var2Offset << "(%rbp), %eax" << endl;
			o << "	setg	%al" << endl;

			o << "	movzbl	%al, %eax" << endl;

			// Write expression result (which is in %eax) in new var
			o << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;

			break;
		}

	}
	
}
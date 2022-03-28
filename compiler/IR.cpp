/*************************************************************************
                          PLD Compiler : IR
                          -----------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

#include "IR.h"
#include <iostream>

using namespace std;

unordered_map<string, string> Instr::AMD86_paramRegisters = {{"0", "%edi"}, {"1", "%esi"}, {"2", "%edx"}, {"3", "%ecx"}, {"4", "%r8d"}, {"5", "%r9d"}};

/* --------------------------------------------------------------------- */
//------------- Implementation of class <CFG> (file IR.cpp) --------------/
/* --------------------------------------------------------------------- */

CFG::CFG() {
	createBB();
}

CFG::~CFG() {
	for (BasicBlock* bb : bbList) {
		delete bb;
	}
}

void CFG::createBB() {
	string bbName = "bb" + to_string(bbList.size());
	BasicBlock* bb = new BasicBlock(this, bbName);
	bbList.push_back(bb);
	currentBB = bb;
}

void CFG::generateASM(ostream& o) {
	generateASMPrologue(o);
	for (BasicBlock* bb : bbList) {
		bb->generateASM(o);
	}
	generateASMEpilogue(o);
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

/* --------------------------------------------------------------------- */
//--------- Implementation of class <BasicBlock> (file IR.cpp) -----------/
/* --------------------------------------------------------------------- */

BasicBlock::BasicBlock(CFG* cfg, string label) : cfg(cfg), label(label) { }

BasicBlock::~BasicBlock() {
	for (Instr* i : instrList) {
		delete i;
	}
}

void BasicBlock::addInstr(Instr::Operation op, vector<string> params, SymbolTable* sT) {
	Instr* instr = new Instr(this, op, params, sT);
	instrList.push_back(instr);
}

void BasicBlock::generateASM(ostream &o) {
	for (Instr* i : instrList) {
		i->generateASM(o);
	}
}

/* --------------------------------------------------------------------- */
//------------ Implementation of class <Instr> (file IR.cpp) -------------/
/* --------------------------------------------------------------------- */

Instr::Instr(BasicBlock* bb, Instr::Operation op, vector<string> params, SymbolTable* sT) : bb(bb), op(op), params(params), symbolTable(sT) {}

void Instr::generateASM(ostream &o) {

	switch (op) {

		case Instr::ldconst:
		{
			o << "# OP: LDCONST" << endl;

			// Get params
			string constant = params.at(0);
			string var = params.at(1);

			o << "# constant:" << constant << endl; 
			o << "# var: " << var << endl;

			// Get constant value
			int constValue;
			string movInstr;
			bool isChar = (constant[0] == '\'');
			bool isInt = (constant[0] == '$');
			//bool isChar = (symbolTable->getVar(var).varType == "char");
			//bool isInt = (symbolTable->getVar(var).varType == "int");
			
			if (isChar) {
				//constValue = int(constant[1]);
				constValue = stoi(constant.substr(1,constant.size()-1));
				movInstr = "movb	%al";
			} 
			else if (isInt) {
				constValue = stoi(constant.substr(1,constant.size()-1));
				movInstr = "movl	%eax";
			}

			// Write ASM instructions
			o << "	movl	$" << constValue << ", %eax" << endl;
			o << "	" << movInstr << ", " << symbolTable->getVar(var).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::copy:
		{
			o << "# OP: COPY" << endl;

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);

			varStruct s1 = symbolTable->getVar(var1);
			varStruct s2 = symbolTable->getVar(var2);

			o << "# var1: " << var1 << "(" << s1.varType << ")" << endl;
			o << "# var2: " << var2 << "(" << s2.varType << ")" << endl;

			string movInstr1, movInstr2;
			string reg1, reg2;

			// var2 = var1

			if (s2.varType == "int" && s1.varType == "int") {
				// int = int : movl
				movInstr1 = "movl";
				reg1 = "eax";
				movInstr2 = "movl";
				reg2 = "eax";
			} else if (s2.varType == "char" && s1.varType == "char") {
				// char = char : movb
				movInstr1 = "movb";
				reg1 = "al";
				movInstr2 = "movb";
				reg2 = "al";
			} else if (s2.varType == "char" && s1.varType == "int") {
				// char = int : movb
				movInstr1 = "movb";
				reg1 = "al";
				movInstr2 = "movb";
				reg2 = "al";
			} else if (s2.varType == "int" && s1.varType == "char") {
				// int = char : movzbl
				movInstr1 = "movzbl";
				reg1 = "eax";
				movInstr2 = "movl";
				reg2 = "eax";
			}

			// Write ASM instructions
			o << "	" << movInstr1 << "	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %" << reg1 << endl;
			o << "	" << movInstr2 << "	%" << reg2 << ", " << symbolTable->getVar(var2).memoryOffset << "(%rbp)" << endl;

	
			break;
		}

		case Instr::rmem: 
		{
			o << "# OP: RMEM" << endl;
			// not yet implemented
			break;
		}

		case Instr::wmem: 
		{
			// not yet implemented
			break;
		}

		case Instr::op_add:
		{
			o << "# OP: ADD" << endl;

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			o << "# var1: " << var1 << "(" << symbolTable->getVar(var1).varType << ")" << endl;
			o << "# var2: " << var2 << "(" << symbolTable->getVar(var2).varType << ")" << endl;

			varStruct vs1 = symbolTable->getVar(var1);
			varStruct vs2 = symbolTable->getVar(var2);

			// move data to registers
			string movInstr1 = SymbolTable::typeOpeMoves.at(vs1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(vs2.varType);

			o << "	" << movInstr1 << "	" << vs1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << vs2.memoryOffset << "(%rbp), %edx" << endl;

			o << "	addl	%edx, %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			// Write ASM instructions
			/*
			o << "	movl	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	addl	" <<  symbolTable->getVar(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;
			*/
			
			break;
		}

		case Instr::op_sub:
		{

			o << "# OP: SUB" << endl;

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			/*
			o << "	movl	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	subl	" <<  symbolTable->getVar(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;
			*/

			varStruct vs1 = symbolTable->getVar(var1);
			varStruct vs2 = symbolTable->getVar(var2);

			// move data to registers
			string movInstr1 = SymbolTable::typeOpeMoves.at(vs1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(vs2.varType);

			o << "	" << movInstr1 << "	" << vs1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << vs2.memoryOffset << "(%rbp), %edx" << endl;

			o << "	subl	%edx, %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_xor:
		{
			o << "# OP: XOR" << endl;

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			/*
			o << "	movl	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	xorl	" <<  symbolTable->getVar(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;
			*/

			varStruct vs1 = symbolTable->getVar(var1);
			varStruct vs2 = symbolTable->getVar(var2);

			// move data to registers
			string movInstr1 = SymbolTable::typeOpeMoves.at(vs1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(vs2.varType);

			o << "	" << movInstr1 << "	" << vs1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << vs2.memoryOffset << "(%rbp), %edx" << endl;

			o << "	xorl	%edx, %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_and:
		{
			o << "# OP: AND" << endl;

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			o << "	movl	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	andl	" <<  symbolTable->getVar(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_mul:
		{
			o << "# OP: MUL" << endl;

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			/*
			o << "	movl	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	imull	" << symbolTable->getVar(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;
			*/
			varStruct vs1 = symbolTable->getVar(var1);
			varStruct vs2 = symbolTable->getVar(var2);

			// move data to registers
			string movInstr1 = SymbolTable::typeOpeMoves.at(vs1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(vs2.varType);

			o << "	" << movInstr1 << "	" << vs1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << vs2.memoryOffset << "(%rbp), %edx" << endl;

			o << "	imull	%edx, %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_div:
		{
			o << "# OP: DIV" << endl;
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			/*
			o << "	movl	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cltd" << endl;
			o << "	idivl	" << symbolTable->getVar(var2).memoryOffset << "(%rbp)" << endl; 
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;
			*/
			varStruct vs1 = symbolTable->getVar(var1);
			varStruct vs2 = symbolTable->getVar(var2);

			// move data to registers
			string movInstr1 = SymbolTable::typeOpeMoves.at(vs1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(vs2.varType);

			o << "	" << movInstr1 << "	" << vs1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << vs2.memoryOffset << "(%rbp), %ebx" << endl;

			o << "	cltd" << endl;
			o << "	idivl	%ebx" << endl; 
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_or:
		{
			o << "# OP: OR" << endl;
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			o << "	movl	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	orl	" <<  symbolTable->getVar(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;
			
			break;
		}

		case Instr::op_mod:
		{
			o << "# OP: MOD" << endl;
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			/*
			o << "	movl	" << symbolTable->getVar(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cltd" << endl;
			o << "	idivl	" << symbolTable->getVar(var2).memoryOffset << "(%rbp)" << endl; 
			o << "	movl	%edx, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;
			*/
			varStruct vs1 = symbolTable->getVar(var1);
			varStruct vs2 = symbolTable->getVar(var2);

			// move data to registers
			string movInstr1 = SymbolTable::typeOpeMoves.at(vs1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(vs2.varType);

			o << "	" << movInstr1 << "	" << vs1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << vs2.memoryOffset << "(%rbp), %ebx" << endl;

			o << "	cltd" << endl;
			o << "	idivl	%ebx" << endl; 
			o << "	movl	%edx, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_not:
		{
			o << "# OP: NOT" << endl;
			// Get params
			string var = params.at(0);
			string tmp = params.at(1);

			varStruct s1 = symbolTable->getVar(var);
			varStruct s2 = symbolTable->getVar(tmp);
			string movInstr1 = SymbolTable::typeOpeMoves.at(s1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2.varType);

			// Write ASM instructions
			o << "	" << movInstr1 << "	" << s1.memoryOffset << "(%rbp), %eax" << endl;

			// Write ASM instructions
			o << "	cmpl	$0, %eax" << endl;
			o << "	sete	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	" << movInstr2 << "	%eax, " << s2.memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_minus:
		{
			o << "# OP: MINUS" << endl;
			// Get params
			string var = params.at(0);
			string tmp = params.at(1);

			varStruct s1 = symbolTable->getVar(var);
			varStruct s2 = symbolTable->getVar(tmp);
			string movInstr1 = SymbolTable::typeOpeMoves.at(s1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2.varType);

			// Write ASM instructions
			o << "	" << movInstr1 << "	" << s1.memoryOffset << "(%rbp), %eax" << endl;

			// Write ASM instructions
			o << "	movl	" << symbolTable->getVar(var).memoryOffset << "(%rbp), %eax" << endl;
			o << "	negl	%eax" << endl;
			o << "	" << movInstr2 << "	%eax, " << s2.memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_eq:
		{
			o << "# OP: ==" << endl;
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct s1 = symbolTable->getVar(var1);
			varStruct s2 = symbolTable->getVar(var2);

			string movInstr1 = SymbolTable::typeOpeMoves.at(s1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2.varType);

			// Write ASM instructions
			o << "	" << movInstr1 << "	" << s1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << s2.memoryOffset << "(%rbp), %edx" << endl;
			o << "	cmpl	%edx, %eax" << endl;
			o << "	sete	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_neq:
		{
			o << "# OP: !=" << endl;

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct s1 = symbolTable->getVar(var1);
			varStruct s2 = symbolTable->getVar(var2);

			string movInstr1 = SymbolTable::typeOpeMoves.at(s1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2.varType);

			// Write ASM instructions
			o << "	" << movInstr1 << "	" << s1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << s2.memoryOffset << "(%rbp), %edx" << endl;
			o << "	cmpl	%edx, %eax" << endl;
			o << "	setne	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_lt:
		{
			o << "# OP: <" << endl;

			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct s1 = symbolTable->getVar(var1);
			varStruct s2 = symbolTable->getVar(var2);

			string movInstr1 = SymbolTable::typeOpeMoves.at(s1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2.varType);

			// Write ASM instructions
			o << "	" << movInstr1 << "	" << s1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << s2.memoryOffset << "(%rbp), %edx" << endl;
			o << "	cmpl	%edx, %eax" << endl;
			o << "	setl	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_gt:
		{
			o << "# OP: >" << endl;
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct s1 = symbolTable->getVar(var1);
			varStruct s2 = symbolTable->getVar(var2);

			string movInstr1 = SymbolTable::typeOpeMoves.at(s1.varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2.varType);

			// Write ASM instructions
			o << "	" << movInstr1 << "	" << s1.memoryOffset << "(%rbp), %eax" << endl;
			o << "	" << movInstr2 << "	" << s2.memoryOffset << "(%rbp), %edx" << endl;
			o << "	cmpl	%edx, %eax" << endl;
			o << "	setg	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::prologue:
		{
			o << "# OP: PROLOGUE" << endl;
			// Get param
			string label = params.at(0);

			// f we're constructing the main function
			if (label == "main") { 
				o << ".globl " << label << endl;
			}

			// Write ASM instructions
			o << label << ":" << endl;
			o << "	pushq 	%rbp " << endl;
			o << "	movq 	%rsp, %rbp" << endl;

			// If we're constructing a function AR
			if (label != "main") {
				// Get the memory size needed to store the function's local variables (must be multiple of 16)
				int memSize = symbolTable->getFuncMemorySpace();
				o << "	subq 	$" << memSize << ", %rsp" << endl;
			}

			break;
		}

		case Instr::epilogue:
		{
			o << "# OP: EPILOGUE" << endl;
			o << "	leave" << endl;
			o << "	ret" << endl;
			break;
		}

		case Instr::call:
		{
			o << "# OP: CALL" << endl;
			// Get params
			string label = params.at(0);
			string tmp = params.at(1);

			// Write ASM instructions
			o << "	call 	" << label << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::wparam: 
		{
			o << "# OP: WPARAM" << endl;
			// Get params
			string var = params.at(0);
			string paramNum = params.at(1);

			// Get param register
			string reg = Instr::AMD86_paramRegisters[paramNum];

			// Write ASM instructions
			o << "	movl	" << symbolTable->getVar(var).memoryOffset << "(%rbp), " << reg << endl;

			break;
		}

		case Instr::rparam: 
		{
			o << "# OP: RPARAM" << endl;
			// Get params
			string var = params.at(0);
			string paramNum = params.at(1);

			// Get param register
			string reg = Instr::AMD86_paramRegisters[paramNum];

			// Write ASM instructions
			o << "	movl	" << reg << ", " << symbolTable->getVar("^" + var).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::ret:
		{
			o << "# OP: RET" << endl;
			// Get params
			string param1 = params.at(0);

			// If we're returning a var
			if (symbolTable->hasVar(param1)) {
				varStruct var = symbolTable->getVar(param1);
				o << "	movl	" << var.memoryOffset << "(%rbp), %eax"<< endl;
			}

			// If we're returning a const
			else {
				int constValue;
				bool isChar = (param1[0] == '\'');
				bool isInt = (param1[0] == '$');
				if (isChar) {
					constValue = int(param1[1]);
				} 
				else if (isInt) {
					constValue = stoi(param1.substr(1,param1.size()-1));	
				}
				o << "	movl	$" << constValue << ", %eax" << endl;
			}

			// Note: the actual return is handled by the epilogue
			
			break;
		}

	}
	
}
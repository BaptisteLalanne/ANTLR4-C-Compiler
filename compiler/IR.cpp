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

/* --------------------------------------------------------------------- */
//------------ Implementation of class <Instr> (file IR.cpp) -------------/
/* --------------------------------------------------------------------- */

Instr::Instr(BasicBlock* bb, Instr::Operation op, vector<string> params, SymbolTable* sT) : bb(bb), op(op), params(params), symbolTable(sT) {}

void Instr::generateASM(ostream &o) {

	switch (op) {

		case Instr::ldconst:
		{
			// Get params
			string constant = params.at(0);
			string var = params.at(1);

			// Get constant value
			int constValue;
			string movInstr;
			bool isChar = (constant[0] == '\'');
			bool isInt = (constant[0] == '$');
			
			if (isChar) {
				constValue = stoi(constant.substr(1,constant.size()-1));
				movInstr = "movb";
			} 
			else if (isInt) {
				constValue = stoi(constant.substr(1,constant.size()-1));
				movInstr = "movl";
			}

			// Write ASM instructions
			o << "	" << movInstr << "	$" << constValue << ", " << symbolTable->getVar(var)->memoryOffset << "(%rbp)" \
			  << "		# load " << constValue << " into " << var << endl;

			break;
		}

		case Instr::copy:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);

			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);

			string movInstr1, movInstr2;
			string reg1, reg2;

			// var2 = var1

			if (s2->varType == "int" && s1->varType == "int") {
				// int = int : movl
				movInstr1 = "movl";
				reg1 = "eax";
				movInstr2 = "movl";
				reg2 = "eax";
			} else if (s2->varType == "char" && s1->varType == "char") {
				// char = char : movb
				movInstr1 = "movb";
				reg1 = "al"; 
				movInstr2 = "movb";
				reg2 = "al";
			} else if (s2->varType == "char" && s1->varType == "int") {
				// char = int : movb
				movInstr1 = "movb";
				reg1 = "al";
				movInstr2 = "movb";
				reg2 = "al";
			} else if (s2->varType == "int" && s1->varType == "char") {
				// int = char : movzbl
				movInstr1 = "movzbl";
				reg1 = "eax";
				movInstr2 = "movl";
				reg2 = "eax";
			}
			
			// Write ASM instructions
			o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %" << reg1 \
			<< "		# load " << var1 << " into " << "%" << reg1 << endl;
			o << "	" << movInstr2 << "	%" << reg2 << ", " << s2->memoryOffset << "(%rbp)" \
			<< "		# load " << "%" << reg2 << " into " << var2 << endl;

			break;
		}

		case Instr::rmem: 
		{
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
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const 
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr + *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				// move data to registers
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var1 << " into " << "%eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" \
				<< "		# load " << var2 << " into " << "%edx" << endl;

				o << "	addl	%edx, %eax" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}
			break;
		}

		case Instr::op_sub:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const 
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr - *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				// move data to registers
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var1 << " into " << "%eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" \
				<< "		# load " << var2 << " into " << "%edx" << endl;

				o << "	subl	%edx, %eax" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}
			break;
		}

		case Instr::op_xor:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr ^ *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				// move data to registers
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var1 << " into " << "%eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" \
				<< "		# load " << var2 << " into " << "%edx" << endl;

				o << "	xorl	%edx, %eax" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}

			break;
		}

		case Instr::op_mul:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr * *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				// move data to registers
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var1 << " into " << "%eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" \
				<< "		# load " << var2 << " into " << "%edx" << endl;

				o << "	imull	%edx, %eax" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}

			break;
		}

		case Instr::op_div:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);
			// Check if const 
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr / *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				// move data to registers
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var1 << " into " << "%eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" \
				<< "		# load " << var2 << " into " << "%edx" << endl;

				o << "	cltd" << endl;
				o << "	idivl	" << s2->memoryOffset << "(%rbp)" << endl; 
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}
			break;
		}

		case Instr::op_mod:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// move data to registers
			string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

			// Check if const 
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr % *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var1 << " into " << "%eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" \
				<< "		# load " << var2 << " into " << "%edx" << endl;

				o << "	cltd" << endl;
				o << "	idivl	%ebx" << endl; 
				o << "	movl	%edx, " << s3->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}
			break;
		}

		case Instr::op_and:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);
			
			// Write ASM instructions
			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const 
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr & *s2->constPtr;
				s3->constPtr = new int(res);
				// Write ASM instructions
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				o << "	movl	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var1 << " into " << "%eax" << endl;
				o << "	andl	" <<  s2->memoryOffset << "(%rbp), %eax" \
				<< "		# and(" << var2 << ", " << "%eax)" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}
			
			break;
		}

		case Instr::op_or:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const 
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr | *s2->constPtr;
				s3->constPtr = new int(res);
				// Write ASM instructions
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				o << "	movl	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var1 << " into " << "%eax" << endl;
				o << "	orl	" <<  s2->memoryOffset << "(%rbp), %eax" \
				<< "		# or(" << var2 << ", " << "%eax)" << endl;
				o << "	movl	%eax, " << symbolTable->getVar(tmp)->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}
			break;
		}

		case Instr::op_not:
		{
			// Get params
			string var = params.at(0);
			string tmp = params.at(1);


			varStruct* s1 = symbolTable->getVar(var);
			varStruct* s2 = symbolTable->getVar(tmp);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);
			
			// Check if const 
			if(s1->constPtr) {
				int res = !(*s1->constPtr);
				s2->constPtr = new int(res);
				o << "	" << movInstr2 << "	$" << SymbolTable::getCast(s2->varType,res) << ", " << s2->memoryOffset << "(%rbp)" << endl;
			} else {
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				// Write ASM instructions
				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var << " into " << "%eax" << endl;

				// Write ASM instructions
				o << "	cmpl	$0, %eax" << endl;
				o << "	sete	%al" << endl;
				o << "	movzbl	%al, %eax" << endl;
				o << "	" << movInstr2 << "	%eax, " << s2->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}
			break;
		}

		case Instr::op_minus:
		{
			// Get params
			string var = params.at(0);
			string tmp = params.at(1);

			varStruct* s1 = symbolTable->getVar(var);
			varStruct* s2 = symbolTable->getVar(tmp);
			string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

			// Check if const
			if(s1->constPtr){
				int res = -(*s1->constPtr);
				s2->constPtr = new int(res);
				o << "	" << movInstr2 << "	$" << SymbolTable::getCast(s2->varType,res) << ", " << s2->memoryOffset << "(%rbp)" << endl;
			} else {
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				
				// Write ASM instructions
				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" \
				<< "		# load " << var << " into " << "%eax" << endl;
				o << "	negl	%eax" << endl;
				o << "	" << movInstr2 << "	%eax, " << s2->memoryOffset << "(%rbp)" \
				<< "		# load " << "%eax" << " into " << tmp << endl;
			}
			break;
		}

		case Instr::cmp_eq:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr == *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				// Write ASM instructions
				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" << endl;
				o << "	cmpl	%edx, %eax" << endl;
				o << "	sete	%al" << endl;
				o << "	movzbl	%al, %eax" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" << endl;
			}

			break;
		}

		case Instr::cmp_neq:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr != *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				// Write ASM instructions
				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" << endl;
				o << "	cmpl	%edx, %eax" << endl;
				o << "	setne	%al" << endl;
				o << "	movzbl	%al, %eax" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" << endl;
			}

			break;
		}

		case Instr::cmp_lt:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr < *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				// Write ASM instructions
				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" << endl;
				o << "	cmpl	%edx, %eax" << endl;
				o << "	setl	%al" << endl;
				o << "	movzbl	%al, %eax" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" << endl;
			}

			break;
		}

		case Instr::cmp_gt:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			varStruct* s1 = symbolTable->getVar(var1);
			varStruct* s2 = symbolTable->getVar(var2);
			varStruct* s3 = symbolTable->getVar(tmp);

			// Check if const
			if(s1->constPtr && s2->constPtr) {
				int res = *s1->constPtr > *s2->constPtr;
				s3->constPtr = new int(res);
				o << "	movl	$" << res << ", " << s3->memoryOffset << "(%rbp)" << endl;
			} else {
				string movInstr1 = SymbolTable::typeOpeMoves.at(s1->varType);
				string movInstr2 = SymbolTable::typeOpeMoves.at(s2->varType);

				// Write ASM instructions
				o << "	" << movInstr1 << "	" << s1->memoryOffset << "(%rbp), %eax" << endl;
				o << "	" << movInstr2 << "	" << s2->memoryOffset << "(%rbp), %edx" << endl;
				o << "	cmpl	%edx, %eax" << endl;
				o << "	setg	%al" << endl;
				o << "	movzbl	%al, %eax" << endl;
				o << "	movl	%eax, " << s3->memoryOffset << "(%rbp)" << endl;
			}
			break;

		}

		case Instr::prologue:
		{
			// Get param
			string label = params.at(0);

			o << endl;
			o << ".globl " << label << endl;
			o << ".type	" << label << ", @function" << endl;

			// Write ASM instructions
			o << label << ":" << endl << endl;
			o << "	pushq 	%rbp " << endl;
			o << "	movq 	%rsp, %rbp" << endl;

			// Get the memory size needed to store the function's local variables (must be multiple of 16)
			int memSize = symbolTable->getMemorySpace();
			int remainder = memSize % 16;
			memSize += (remainder > 0) ? 16 - remainder : 0;
			o << "	subq 	$" << memSize << ", %rsp" << endl;

			o << endl;

			break;
		}

		case Instr::epilogue:
		{
			o << endl;
			o << "	movq %rbp, %rsp" << endl;
			o << "	popq %rbp" << endl;
			o << "	ret" << endl;
			break;
		}

		case Instr::call:
		{
			// Get params
			string label = params.at(0);
			string tmp = params.at(1);

			// Write ASM instructions
			o << "	call 	" << label << endl;
			o << "	movl	%eax, " << symbolTable->getVar(tmp)->memoryOffset << "(%rbp)" \
			  << "		# load " << "%eax" << " into " << tmp << endl;

			break;
		}

		case Instr::wparam: 
		{
			// Get params
			string var = params.at(0);
			string paramNum = params.at(1);

			// Get param register
			string reg = Instr::AMD86_paramRegisters[paramNum];
			varStruct* s1 = symbolTable->getVar(var);
			
			// Check if const 
			if(s1->constPtr){
				o << "	movl	$" << *s1->constPtr << ", " << reg \
				  << "		# load " << var << " into " << "%" << reg << endl;
			} else {
				// Write ASM instructions
				o << "	movl	" << s1->memoryOffset << "(%rbp), " << reg \
				<< "		# load " << var << " into " << "%" << reg << endl;
			}

			break;
		}

		case Instr::rparam: 
		{
			// Get params
			string var = params.at(0);
			string paramNum = params.at(1);

			// Get param register
			string reg = Instr::AMD86_paramRegisters[paramNum];

			// Write ASM instructions
			o << "	movl	" << reg << ", " << symbolTable->getVar(var)->memoryOffset << "(%rbp)" \
			  << "		# load " << "%" << reg << " into " << "^" + var << endl;

			break;
		}

		case Instr::ret:
		{
			// Get params
			string param1 = params.at(0);

			// If we're returning a var
			if (symbolTable->hasVar(param1)) {
				varStruct* s1 = symbolTable->getVar(param1);
				if(s1->constPtr){
					o << "	movl	$" << *s1->constPtr << ", %eax" << endl;
				} else {
					o << "	movl	" << s1->memoryOffset << "(%rbp), %eax"<< endl;
				}
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
				o << "	movl	$" << constValue << ", %eax" \
				  << "		# load " << constValue << " into " << "%eax" << endl;
			}

			// Note: the actual return is handled by the epilogue
			
			break;
		}

		case Instr::conditional_jump:
		{
			// Get params
			string testVarName = params.at(0);
			string falseExitBlockLabel = params.at(1);
			string trueExitBlockLabel = params.at(2);

			// Write ASM instructions
			o << "	cmpl    $0, " << symbolTable->getVar(testVarName)->memoryOffset << "(%rbp)" \
			  << "	# cmp(0, " << testVarName << ")" << endl;
			o << "	je    " << falseExitBlockLabel << endl;
			o << "	jmp    " << trueExitBlockLabel << endl;

			break;
		}

		case Instr::absolute_jump:
		{
			// Get params
			string blockLabel = params.at(0);

			// Write ASM instructions
			o << "	jmp    " << blockLabel << endl;

			break;
		}

	}
	
}
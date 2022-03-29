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

CFG::CFG(SymbolTable& st) : symbolTable(st) {
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
	//currentBB = bb;
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

varStruct BasicBlock::getSymbol(string name) {
	return cfg->getSymbolTable().getVar(name);
}

void BasicBlock::addInstr(Instr::Operation op, vector<string> params) {
	Instr* instr = new Instr(this, op, params);
	instrList.push_back(instr);
}

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

void BasicBlock::setTestVarName(string test_var_name) {
	this->test_var_name = test_var_name;
}

/* --------------------------------------------------------------------- */
//------------ Implementation of class <Instr> (file IR.cpp) -------------/
/* --------------------------------------------------------------------- */

Instr::Instr(BasicBlock* bb, Instr::Operation op, vector<string> params) : bb(bb), op(op), params(params) {}

varStruct Instr::getSymbol(string name) {
	return this->bb->getCFG()->getSymbolTable().getVar(name);
}
bool Instr::hasSymbol(string name) {
	return this->bb->getCFG()->getSymbolTable().hasVar(name);
}
SymbolTable& Instr::getSymbolTable() {
	return this->bb->getCFG()->getSymbolTable(); 
}

void Instr::generateASM(ostream &o) {

	cout << "#generateASM : display Map : "<<endl;
			this->bb->getCFG()->getSymbolTable().displayVarMap();

	switch (op) {

		case Instr::ldconst:
		{
			// Get params
			string constant = params.at(0);
			string var = params.at(1);
			
			// Get constant value
			int constValue;
			bool isChar = (constant[0] == '\'');
			bool isInt = (constant[0] == '$');
			if (isChar) {
				constValue = int(constant[1]);
			} 
			else if (isInt) {
				constValue = stoi(constant.substr(1,constant.size()-1));	
			}

			// Write ASM instructions
			o << "	movl	$" << constValue << ", %eax" << endl;
			o << "	movl	%eax, " << getSymbol(var).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::copy:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);

			cout << "#getSymbol(var1) : " << getSymbol(var1).varName << ", " << getSymbol(var1).memoryOffset << endl;
			cout << "#getSymbol(var2) : " << getSymbol(var2).varName << ", " << getSymbol(var2).memoryOffset << endl;

			// Write ASM instructions
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(var2).memoryOffset << "(%rbp)" << endl;
	
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

			// Write ASM instructions
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	addl	" <<  getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;
			
			break;
		}

		case Instr::op_sub:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	subl	" <<  getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_xor:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
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

			// Write ASM instructions
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

			// Write ASM instructions
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

			// Write ASM instructions
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cltd" << endl;
			o << "	idivl	" << getSymbol(var2).memoryOffset << "(%rbp)" << endl; 
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::op_or:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	orl	" <<  getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;
			
			break;
		}

		case Instr::op_mod:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
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

			// Write ASM instructions
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

			// Write ASM instructions
			o << "	movl	" << getSymbol(var).memoryOffset << "(%rbp), %eax" << endl;
			o << "	negl	%eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_eq:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cmpl	" << getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	sete	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_neq:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cmpl	" << getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	setne	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_lt:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cmpl	" << getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	setl	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::cmp_gt:
		{
			// Get params
			string var1 = params.at(0);
			string var2 = params.at(1);
			string tmp = params.at(2);

			// Write ASM instructions
			cout << "#getSymbol(var1) : " << getSymbol(var1).varName << ", " << getSymbol(var1).memoryOffset << endl;
			cout << "#getSymbol(var2) : " << getSymbol(var2).varName << ", " << getSymbol(var2).memoryOffset << endl;
			cout << "#getSymbol(tmp) : " << getSymbol(tmp).varName << ", " << getSymbol(tmp).memoryOffset << endl;
			o << "	movl	" << getSymbol(var1).memoryOffset << "(%rbp), %eax" << endl;
			o << "	cmpl	" << getSymbol(var2).memoryOffset << "(%rbp), %eax" << endl;
			o << "	setg	%al" << endl;
			o << "	movzbl	%al, %eax" << endl;
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::prologue:
		{
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
				int memSize = getSymbolTable().getFuncMemorySpace(label);
				o << "	subq 	$" << memSize << ", %rsp" << endl;
			}

			break;
		}

		case Instr::epilogue:
		{
			o << "	leave" << endl;
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
			o << "	movl	%eax, " << getSymbol(tmp).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::wparam: 
		{
			// Get params
			string var = params.at(0);
			string paramNum = params.at(1);

			// Get param register
			string reg = Instr::AMD86_paramRegisters[paramNum];

			// Write ASM instructions
			o << "	movl	" << getSymbol(var).memoryOffset << "(%rbp), %eax" << endl;
			o << "	movl	%eax, " << reg << endl;

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
			o << "	movl	" << reg << ", %eax" << endl; 
			o << "	movl	%eax, " << getSymbol(var).memoryOffset << "(%rbp)" << endl;

			break;
		}

		case Instr::ret:
		{
			// Get params
			string param1 = params.at(0);

			// If we're returning a var
			if (hasSymbol(param1)) {
				varStruct var = getSymbol(param1);
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
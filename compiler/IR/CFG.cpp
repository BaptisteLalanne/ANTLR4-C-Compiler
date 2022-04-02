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
	string bbName = ".bb" + to_string(bbList.size());
	BasicBlock* bb = new BasicBlock(this, bbName);
	bbList.push_back(bb);
	currentBB = bb;
	return bb;
}

void CFG::generateASM(ostream& o) {
	generateASMPrologue(o);
	generateStandardFunctions(o);
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


void CFG::generateStandardFunctions(ostream& o) {
	this->generatePutchar(o);
	this->generateGetchar(o);
}

void CFG::generatePutchar(ostream& o) {
	o << "putchar:" << endl;
	o << "	pushq 	%rbp" << endl;
	o << "	movq 	%rsp, %rbp" << endl;
	o << "	pushq	%rdi" << endl;
	o << "	mov     $1, %rax" << endl;
	o << "	mov     $1, %rdi" << endl;
	o << "	mov     %rsp, %rsi" << endl;
	o << "	mov     $1, %rdx" << endl;
	o << "	syscall" << endl;
	o << "	add     $8, %rsp" << endl;
	o << "	movl	$1, %eax" << endl;
	o << "	leave" << endl;
	o << "	ret" << endl << endl;
}

void CFG::generateGetchar(ostream& o) {
	o << "getchar:" << endl;
	o << "	pushq 	%rbp" << endl;
	o << "	movq	%rsp, %rbp" << endl;
	o << "	xor		%eax, %eax" << endl;
	o << "	xor		%edi, %edi" << endl;
	o << "	movq	8(%rsp), %r8" << endl;
	o << "	lea		8(%rsp), %rsi" << endl;
	o << "	movl	$1, %edx" << endl;
	o << "	syscall" << endl;
	o << "	movzbl	8(%rsp), %eax" << endl;
	o << "	movq	%r8, 8(%rsp)" << endl;
	o << "	leave" << endl;
	o << "	ret" << endl << endl;
}

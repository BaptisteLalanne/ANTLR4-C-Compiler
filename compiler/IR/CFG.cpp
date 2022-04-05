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
	optimized=false;
}

CFG::~CFG() {
	for (BasicBlock* bb : bbList) {
		delete bb;
	}
}

void CFG::initStandardFunctions(SymbolTable* st) {
	funcStruct* sPutchar = st->getFunc("putchar");
	funcStruct* sGetchar = st->getFunc("getchar");

	this->mustWritePutchar = sPutchar->isCalled;
	this->mustWriteGetchar = sGetchar->isCalled;
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

void CFG::optimizeIR() {
	for (BasicBlock* bb : bbList) {
		bb->optimizeIR();
	}
}

void CFG::optimizeASM(stringstream& iS, ostream& oS) {
	
	vector<string> outputLines;
	string previousSrc = "";
	string previousDest = "";
	string previousInstr = "";
	string previousJump = "null";

	// Fetch lines
	string line;
	while (getline(iS, line)) {
		
		// Fetch args
		vector<string> args = splitString(line, "\t");
		
		// If this is a bb declaration
		if (args[0].find(".bb") != string::npos) {
			// If it corresponds to the jump previously visited
			if (args[0].find(previousJump) != string::npos) {
				// Remove last instruction from stack (which was a jump to this)
				outputLines.pop_back();
			}
		}

		// If this is instruction has no arguments, keep moving
		if (args.size() < 2) {
			outputLines.push_back(line);
			continue;
		}
	
		// Fetch other arguments
		string currInstr = args[1];

		// If this is a movl instruction
		if (currInstr == "movl" || currInstr == "movb") {
			// Fetch params
			vector<string> params = splitString(args[2], ", ");
			// If previous instruction was movl, but with swapped params
			if (currInstr == previousInstr && params[0] == previousDest && params[1] == previousSrc) {
				// Remove last instruction from stack 
				outputLines.pop_back();
				// Only skip this one if this is a var to reg & reg to var case
				if (previousDest[0] == '%' && previousSrc[0] != '%') {
					continue;
				}
			}
			// Store previous params
			previousSrc = params[0];
			previousDest = params[1];
		}

		// If this is a jump instruction
		if (currInstr == "jmp") {
			// Fetch params
			vector<string> params = splitString(args[2], "\t");
			// Store previous jump
			previousJump = params[0];
		}
		else {
			previousJump = "null";
		}

		// Store previous instructions
		previousInstr = currInstr;

		// Save current instruction on stack
		outputLines.push_back(line);

	}

	// Iterate through stack and put them in output stream
	for (string line : outputLines) {
		oS << line << endl;
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
	if (this->mustWritePutchar) {
		this->generatePutchar(o);
	}

	if (this->mustWriteGetchar) {
		this->generateGetchar(o);
	}
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

vector<string> CFG::splitString(string str, string separator) {
    vector<string> lines;
	size_t pos = 0;
	string line;
	while ((pos = str.find(separator)) != string::npos) {
		line = str.substr(0, pos);
		lines.push_back(line);
		str.erase(0, pos + separator.length());
	}
	lines.push_back(str);
	return lines;
}
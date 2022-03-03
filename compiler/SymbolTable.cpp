#include "SymbolTable.h"

using namespace std;

unordered_map<type, int> SymbolTable::typeSizes = {{INT, 4}, {CHAR, 1}};

bool SymbolTable::hasVar(string name) {
	return varMap.contains(name);
}

bool SymbolTable::hasFunc(string name) {
	return funcMap.contains(name);
}

varStruct SymbolTable::getVar(string name) {
	return varMap[name];
}

funcStruct SymbolTable::getFunc(string name) {
	return funcMap[name];
}

void SymbolTable::addVar(string name, type vT, scope vS) {
	struct varStruct s;
	stackPointer -= typeSizes[vT];
	s.memoryOffset = stackPointer;
	s.varType = vT;
	s.varScope = vS;
	varMap[name] = s;
}

void SymbolTable::addFunc(string name, type rT, int nbP, list<type> pT, string c) {
	struct funcStruct s;
	stackPointer = 0;
	s.returnType = rT;
	s.nbParameters = nbP;
	s.parameterTypes = pT;
	s.code = c;
	funcMap[name] = s;
}
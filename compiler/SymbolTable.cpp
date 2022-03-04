#include "SymbolTable.h"
#include <iostream>

using namespace std;

unordered_map<string, int> SymbolTable::typeSizes = {{"int", 4}, {"char", 1}};

bool SymbolTable::hasVar(string name) {
	return varMap.find(name) != varMap.end();
}

bool SymbolTable::hasFunc(string name) {
	return funcMap.find(name) != funcMap.end();
}

varStruct SymbolTable::getVar(string name) {
	return varMap[name];
}

funcStruct SymbolTable::getFunc(string name) {
	return funcMap[name];
}

void SymbolTable::addVar(string name, string vT, string vS) {
	struct varStruct s;
	stackPointer -= typeSizes[vT];
	s.memoryOffset = stackPointer;
	s.varType = vT;
	s.varScope = vS;
	varMap[name] = s;
}

void SymbolTable::addFunc(string name, string rT, int nbP, list<string> pT, string c) {
	struct funcStruct s;
	stackPointer = 0;
	s.returnType = rT;
	s.nbParameters = nbP;
	s.parameterTypes = pT;
	s.code = c;
	funcMap[name] = s;
}
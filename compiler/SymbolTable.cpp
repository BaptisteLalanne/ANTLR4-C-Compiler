/*************************************************************************
                          PLD Compiler : SymbolTable
                          ---------------------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

//---- Implementation of class <SymbolTable> (file SymbolTable.cpp) ------/
#include "SymbolTable.h"
#include <iostream>

using namespace std;

unordered_map<string, int> SymbolTable::typeSizes = {{"int", 4}, {"char", 1}};
unordered_map<string, string> SymbolTable::typeOpeMoves = {{"int", "movl"}, {"char", "movzbl"}};
varStruct SymbolTable::dummyVarStruct = {"", 0, "", 0, false, false, false};

int SymbolTable::hasVar(string name) {
	bool hasVarInOwnMap = varMap.find(name) != varMap.end();
	bool hasVarInParentMap = (parentSymbolTable != nullptr && parentSymbolTable->hasVar(name) > 0);
	int level = 0;
	if (hasVarInOwnMap) level = 1;
	else if (hasVarInParentMap) level = 2;
	return level;
}

int SymbolTable::hasParam(string name) {
	return hasVar("^"+name);
}

bool SymbolTable::hasFunc(string name) {
	bool hasFuncInOwnMap = funcMap.find(name) != funcMap.end();
	bool hasFuncInParentMap = (parentSymbolTable != nullptr && parentSymbolTable->hasFunc(name));
	return hasFuncInOwnMap || hasFuncInParentMap;
}

varStruct* SymbolTable::getVar(string name, bool searchParents) {
	if (hasParam(name)) {
		return getVar("^"+name);
	}

	bool hasVarInOwnMap = varMap.find(name) != varMap.end();
	if (hasVarInOwnMap) {
		return &varMap[name];
	}
	else if(searchParents) {
		return parentSymbolTable->getVar(name);
	} else {
		return nullptr;
	}

}

funcStruct* SymbolTable::getFunc(string name) {

	bool hasFuncInOwnMap = funcMap.find(name) != funcMap.end();
	if (hasFuncInOwnMap) {
		return &funcMap[name];
	}
	else {
		return parentSymbolTable->getFunc(name);
	}
	
}

int SymbolTable::getMemorySpace() {

	int memSize = 0;

	// Compute memory size of own symbol table
	for (auto v : varMap) {
		memSize += typeSizes[v.second.varType];
	}

	// Add memory size of child symbol tables
	for (SymbolTable* sT : childSymbolTables) {
		memSize += sT->getMemorySpace();
	}

	return memSize;

}

void SymbolTable::addVar(string name, string vT, int vL, int* constPtr) {
	stackPointer -= typeSizes[vT];
	struct varStruct s = {
		name,
		stackPointer,
		vT,
		vL,
		false,
		true,
		false,
		constPtr
	};
	varMap[name] = s;
}

void SymbolTable::addFunc(string name, string rT, int nP, vector<string> pT, vector<string> pN, int fL) {
	struct funcStruct s = {
		name,
		rT,
		nP,
		pT,
		pN,
		fL,
		false
	};
	funcMap[name] = s;
}

SymbolTable* SymbolTable::getParent() { 
	return parentSymbolTable; 
}

bool SymbolTable::hasReturned() { 
	return returned; 
}

void SymbolTable::setReturned(bool r) {
	returned = r;
}

int SymbolTable::getStackPointer() {
	return stackPointer; 
}

void SymbolTable::setStackPointer(int s) { 
	stackPointer = s; 
}

void SymbolTable::checkUsedVariables(ErrorHandler& eH) {
	for (auto v : varMap) {
		if (!v.second.isUsed) {
			string message = "";
			if (v.first[0] == '^') {
				message =  "Parameter '" + v.first.substr(1) + "' is not used";
			}
			else {
				message =  "Variable '" + v.first + "' declared at line " + to_string(v.second.varLine) + " is not used";
			}
			eH.signal(WARNING, message, -1);
		}
	}
}

void SymbolTable::checkUsedFunctions(ErrorHandler& eH) {
	unordered_set<string> globFunc = {"main", "putchar", "getchar"};
	for (auto v : funcMap) {
		if (globFunc.find(v.second.funcName) != globFunc.end()) { continue; }
		if (!v.second.isCalled) {
			string message =  "Function '" + v.first + "' declared at line " + to_string(v.second.funcLine) + " is not used";
			eH.signal(WARNING, message, -1);
		}
	}
}

int SymbolTable::getCast(string type, int value) {
	if(type.compare("int") == 0){
		return (int) value;
	} else if (type.compare("char") == 0){
		return (char) value;
	} 
	return value;
}

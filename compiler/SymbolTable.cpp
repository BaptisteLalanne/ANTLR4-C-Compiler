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

bool SymbolTable::hasVar(string name) {
	return varMap.find(name) != varMap.end();
}

bool SymbolTable::hasFunc(string name) {
	return funcMap.find(name) != funcMap.end();
}

varStruct& SymbolTable::getVar(string name) {
	return varMap[name];
}

funcStruct& SymbolTable::getFunc(string name) {
	return funcMap[name];
}

int SymbolTable::getStackPointer() {
	return stackPointer;
}

void SymbolTable::setStackPointer(int s) {
	stackPointer = s;
}

void SymbolTable::addVar(string name, string vT, string vS, int vL) {
	stackPointer -= typeSizes[vT];
	struct varStruct s = {
		stackPointer,
		vT,
		vS,
		vL,
		false,
	};
	varMap[name] = s;
}

void SymbolTable::addFunc(string name, string rT, int nbP, list<string> pT, string c) {
	struct funcStruct s = {
		rT,
		nbP,
		pT,
		c,
		false,
	};
	funcMap[name] = s;
}

void SymbolTable::checkUsedVariables(ErrorHandler& eH) {
	for (auto v : varMap)
	{
		if (!v.second.isUsed) {
			string message =  "Variable " + v.first + " is not used";
			eH.signal(WARNING, message, v.second.varLine);
		}
	}
}

void SymbolTable::cleanTempVars() {
	for (auto v : varMap)
	{
		if (!v.first[0] == '!') {
			varMap.erase(v.first);
		}
	}
}
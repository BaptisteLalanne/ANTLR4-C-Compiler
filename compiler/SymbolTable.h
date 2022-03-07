#pragma once

#include <unordered_map>
#include <list>
#include <string>
#include "ErrorHandler.h"
using namespace std;

struct varStruct {
	int memoryOffset; 
	string varType;
	string varScope;
	int varLine;
	bool isUsed;
};

struct funcStruct {
	string returnType; 
	int nbParameters;
	list<string> parameterTypes;
	string code;
	bool isCalled;
};

class SymbolTable {
	
	public:
		SymbolTable() : stackPointer(0) { }
		bool hasVar(string name);
		bool hasFunc(string name);
		varStruct& getVar(string name);
		funcStruct& getFunc(string name);
		void addVar(string name, string vT, string vS, int vL);
		void addFunc(string name, string rT, int nbP, list<string> pT, string c);
		static unordered_map<string, int> typeSizes;
		void checkUsedVariables(ErrorHandler& eH);
		
	protected:
		int stackPointer;
		unordered_map<string, varStruct> varMap;
		unordered_map<string, funcStruct> funcMap;
};


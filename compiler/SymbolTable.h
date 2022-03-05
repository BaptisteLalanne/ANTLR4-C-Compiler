#pragma once

#include <unordered_map>
#include <list>
#include <string>
using namespace std;

struct varStruct {
	int memoryOffset; 
	string varType;
	string varScope;
};

struct funcStruct {
	string returnType; 
	int nbParameters;
	list<string> parameterTypes;
	string code;
};

class SymbolTable {
	
	public:
		SymbolTable() : stackPointer(0) { }
		bool hasVar(string name);
		bool hasFunc(string name);
		varStruct getVar(string name);
		funcStruct getFunc(string name);
		void addVar(string name, string vT, string vS);
		void addFunc(string name, string rT, int nbP, list<string> pT, string c);
		static unordered_map<string, int> typeSizes;
		
	protected:
		unordered_map<string, varStruct> varMap;
		unordered_map<string, funcStruct> funcMap;
		int stackPointer;

};


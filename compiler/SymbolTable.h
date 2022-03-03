#pragma once

#include <unordered_map>
#include <list>
using namespace std;

enum type {INT, CHAR};
enum scope {LOCAL, GLOBAL, PARAM};

struct varStruct {
	int memoryOffset; 
	type varType;
	scope varScope;
};

struct funcStruct {
	type returnType; 
	int nbParameters;
	list<type> parameterTypes;
	string code;
};

class SymbolTable {
	
	public:
		bool hasVar(string name);
		bool hasFunc(string name);
		varStruct getVar(string name);
		funcStruct getFunc(string name);
		void addVar(string name, type vT, scope vS);
		void addFunc(string name, type rT, int nbP, list<type> pT, string c);
		static unordered_map<type, int> typeSizes;
		
	protected:
		unordered_map<string, varStruct> varMap;
		unordered_map<string, funcStruct> funcMap;
		int stackPointer;

};


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
		varStruct getVar(string name) {
			return varMap[name];
		}
		funcStruct getFunc(string name) {
			return funcMap[name];
		}
		void addVar(string name, int mO, type vT, scope vS) {
			struct varStruct s;
			s.memoryOffset = mO;
			s.varType = vT;
			s.varScope = vS;
			varMap[name] = s;
		}
		void addFunc(string name, type rT, int nbP, list<type> pT, string c) {
			struct funcStruct s;
			s.returnType = rT;
			s.nbParameters = nbP;
			s.parameterTypes = pT;
			s.code = c;
			funcMap[name] = s;
		}
		
	protected:
		unordered_map<string, varStruct> varMap;
		unordered_map<string, funcStruct> funcMap;

};


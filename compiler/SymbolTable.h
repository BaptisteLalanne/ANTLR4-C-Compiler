#pragma once

#include <unordered_map>
#include <list>
#include <string>
using namespace std;

enum errorType {ERROR, WARNING};

class ErrorHandler {
    public:
        static void generateMessage(int severity, string message, int lineNumber);
    protected:
        static string errorValues[2];
};

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
		unordered_map<string, varStruct> varMap;
		unordered_map<string, funcStruct> funcMap;
		
	protected:
		int stackPointer;

};


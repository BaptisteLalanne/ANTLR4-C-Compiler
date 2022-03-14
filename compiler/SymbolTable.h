/*************************************************************************
                          PLD Compiler : SymbolTable
                          ---------------------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

//------ Interface of class <SymbolTable> (file SymbolTable.h) -------/
#pragma once

//--------------------------------------------------- Called interfaces
#include <unordered_map>
#include <list>
#include "ErrorHandler.h"
using namespace std;

//------------------------------------------------------------------ Types
// Store all informations relvent for a variable
struct varStruct {
	int memoryOffset;	//Its offset (in memory) to the base pointer 
	string varType;		//The type of the variable
	string varScope;	//The variable scope (i.e. global, local, ou paramètre)
	int varLine;		//The line of code where the variable is declared
	bool isUsed;		//Whether the variable is used in the code
    bool isCorrect; // False when a dummy struct is returned to avoid bad cast
};

// Store all informations relvent for a function
struct funcStruct {
	string returnType; 				//The return type of the function
	int nbParameters;				//The number of input parameters
	list<string> parameterTypes;	//The type of every input parameter
	string code;					//The code inside the function
	bool isCalled;					//Whether the function is called
};

//------------------------------------------------------------------------
// Goal of class <SymbolTable>
// The goal of this class is to store all symbols encountered while
// parsing a code using a subset of C.
//------------------------------------------------------------------------
class SymbolTable {
	
	public:

		// Constructor of SymbolTable
		SymbolTable() : stackPointer(0) { }

		// Tell whether a variable with a given name is present in the symbol table
		bool hasVar(string name);

		// Tell whether a function with a given name is present in the symbol table
		bool hasFunc(string name);

		// Get the variable corresponding to the input variable name if it was found
		varStruct& getVar(string name);

		// Get the function corresponding to the input function name if it was found
		funcStruct& getFunc(string name);

		// Get the stack pointer 
		int getStackPointer();

		// Set the stack pointer
		void setStackPointer(int s);

		// Add a variable to the table of symbols
		void addVar(string name, string vT, string vS, int vL);

		// Add a function to the table of symbols
		void addFunc(string name, string rT, int nbP, list<string> pT, string c);
		
		// Perform static analysis
		void checkUsedVariables(ErrorHandler& eH);

		// Clean temporary variables
		void cleanTempVars();

		// Hashtable containing the size in bytes of the different types (typeName : size)
		static unordered_map<string, int> typeSizes;

        // Dummy varStruct to handle parsing errors
        varStruct dummyVarStruct = {0,"","",0,false,false};
		
	protected:

		// The current position of the memory stack pointer 
		int stackPointer;	
		
		// TODO: turn this into a MultiMap (or use a key containing the scope)
		// Hashtable containing the encountered variables (varName : variable)
		unordered_map<string, varStruct> varMap;

		// Hashtable containing the encountered functions (funcName : function)
		unordered_map<string, funcStruct> funcMap;

};


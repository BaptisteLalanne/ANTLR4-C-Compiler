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
#include <vector>
#include <unordered_set>
#include "ErrorHandler.h"
using namespace std;

//------------------------------------------------------------------ Types
// Store all informations relvent for a variable
struct varStruct {
	string varName; 	// Its name
	int memoryOffset;	// Its offset (in memory) to the base pointer 
	string varType;		// The type of the variable
	int varLine;		// The line of code where the variable is declared
	bool isUsed;		// Whether the variable is used in the code
    bool isCorrect; 	// False when a dummy struct is returned to avoid bad cast
	bool noConst;		// Tell if the variable can be set as a simple const
	int* constPtr;  	// Const pointer
};

// Store all informations relvent for a function
struct funcStruct {
	string funcName;				// Its name
	string returnType; 				// Its return type 
	int nbParameters;				// The number of input parameters
	vector<string> parameterTypes;	// The type of every input parameter
	vector<string> parameterNames; 	// The names of every parameter
	int funcLine; 					// The line of code where the function is declared
	bool isCalled;					// Whether the function is called
};

//------------------------------------------------------------------------
// Goal of class <SymbolTable>
// The goal of this class is to store all symbols encountered while
// parsing a code using a subset of C.
//------------------------------------------------------------------------
class SymbolTable {
	
	public:

		/* Constructor / Destructor */
		SymbolTable(int sP = 0, SymbolTable* par = nullptr) : stackPointer(sP), parentSymbolTable(par) {
			if (parentSymbolTable != nullptr) {
				parentSymbolTable->childSymbolTables.push_back(this);
			}
		}
		~SymbolTable() {
			for(auto var: varMap) {
				delete(var.second.constPtr);
			}
		};

		// Tell whether a variable or a parameter with a given name is present in the symbol table
		int hasVar(string name);
		int hasParam(string name);

		// Tell whether a function with a given name is present in the symbol table
		bool hasFunc(string name);

		// Get the variable corresponding to the input variable name if it was found
		varStruct* getVar(string name, bool searchParents = true);

		// Get the variable corresponding to the input variable name if it was found
		varStruct* getVarCurrentBlock(string name);

		// Get the function corresponding to the input function name if it was found
		funcStruct* getFunc(string name);

		// Get the number of bytes needed to store the local variables of a given function
		int getMemorySpace();

		// Add a variable to the table of symbols
		void addVar(string name, string vT, int vL, int* constPtr = nullptr);

		// Add a function to the table of symbols
		void addFunc(string name, string rT, int nP, vector<string> pT, vector<string> pN, int fL);

		// Parent getter 
		SymbolTable* getParent();

		// Returned getter
		bool hasReturned();

		// Returned setter 
		void setReturned(bool r);

		// Stack pointer getter
		int getStackPointer();

		// Stack pointer setter
		void setStackPointer(int s);
		
		// Perform static analysis on variables
		void checkUsedVariables(ErrorHandler& eH);

		// Perform static analysis on variables
		void checkUsedFunctions(ErrorHandler& eH);

		// Used for assembler
		static int getCast(string type, int value);

		// Hashtable containing the size in bytes of the different types (typeName : size)
		static unordered_map<string, int> typeSizes;

		// Hashtable containing the move asm instructions for different types (typeName : intrName)
		static unordered_map<string, string> typeOpeMoves;

        // Dummy varStruct to handle parsing errors
        static varStruct dummyVarStruct;

	protected:

		// The current position of the memory stack pointer 
		int stackPointer;	

		// Whether the scope has a return statement
		bool returned;
		
		// Parent symbol table
		SymbolTable* parentSymbolTable;

		// Children symbol tables
		vector<SymbolTable*> childSymbolTables;

		// Hashtable containing the encountered variable declarations
		unordered_map<string, varStruct> varMap;

		// Hashtable containing the encountered function declarations
		unordered_map<string, funcStruct> funcMap;

};


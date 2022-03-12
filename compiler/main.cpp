#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"
#include "CodeGenVisitor.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv) {
    
    // Load the given code
    stringstream in;
    if(argn==2) {
        ifstream lecture(argv[1]);
        if (lecture.fail()) {
            cerr << argv[1] << " does not exist" << endl;
            exit(1);
        }
        in << lecture.rdbuf();
    }
    else {
        cerr << "usage: ifcc path/to/file.c" << endl ;
        exit(1);
    }

    // Parse and construct tree
    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    ifccParser parser(&tokens);
    tree::ParseTree* tree = parser.axiom();

    if(parser.getNumberOfSyntaxErrors() != 0) {
        cerr << "error: syntax error during parsing" << endl;
        exit(1);
    }
    
    // Create symbol table and error handler
    SymbolTable symbolTable;
    ErrorHandler errorHandler;

    cout << "	.text" << endl;

    // Visit tree and linearize
    CodeGenVisitor v(symbolTable, errorHandler);
    v.visit(tree);
    
    // Static Analysis
	symbolTable.checkUsedVariables(errorHandler);

    //In case the function has not returned, return 0 by default
    if (!v.hasReturned()) {
        v.returnDefault();
    }

    return 0;
}

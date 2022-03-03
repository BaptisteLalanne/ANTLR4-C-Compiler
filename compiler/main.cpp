#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"

#include "CodeGenVisitor.h"
#include "SymbolTable.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv) {
    
    // Load the given code
    stringstream in;
    if(argn==2) {
        ifstream lecture(argv[1]);
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
    
    // Create symbol table 
    SymbolTable symbolTable;

    // Visit tree and linearize
    CodeGenVisitor v(symbolTable);
    v.visit(tree);

    return 0;
}

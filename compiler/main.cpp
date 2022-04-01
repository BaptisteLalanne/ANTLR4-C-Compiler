#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"
#include "CodeGenVisitor.h"
#include "IR/CFG.h"

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
        cerr << "ERROR : syntax error during parsing" << endl;
        cout.flush();
        exit(1);
    }
    if(lexer.getNumberOfSyntaxErrors() != 0) {
        cout.flush();
        exit(1);
    }
    
    // Create error handler and IR
    ErrorHandler errorHandler;
    CFG controlFlowGraph;

    // Visit tree and linearize
    CodeGenVisitor v(errorHandler, controlFlowGraph);
    v.visit(tree);

    if(errorHandler.hasError()) {
        cout.flush();
        exit(1);
    }

    // Try to optimize IR
    controlFlowGraph.optimize();

    // Generate ASM instructions
    controlFlowGraph.generateASM(cout);

    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"
#include "CodeGenVisitor.h"
#include "IR/CFG.h"

using namespace antlr4;
using namespace std;

int main(int argc, char *argv[])
{

    CFG controlFlowGraph;
    stringstream in;

    
    int c;
    char* arg_o = nullptr;
    while ((c = getopt(argc, argv, "o")) != -1)
    {
        switch (c)
        {
            case 'o':
            {
                controlFlowGraph.setOptimized(true);
                break;
            }
            case '?':
            {
                cerr << "Got unknown option." << endl; 
                exit(1);
                break;
            }
            default:
            {
                cout << "Got unknown parse returns: " << endl; 
                exit(1);
            }
        }
    }
    for (int i = optind; i < argc; i ++)
    {
        ifstream lecture(argv[i]);
        if (lecture.fail()) {
            cerr << argv[i] << " does not exist" << endl;
            exit(1);
        }
        in << lecture.rdbuf();
        break;
    }

    // Parse and construct tree
    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    ifccParser parser(&tokens);
    tree::ParseTree *tree = parser.axiom();

    if (parser.getNumberOfSyntaxErrors() != 0)
    {
        cerr << "ERROR : syntax error during parsing" << endl;
        cout.flush();
        exit(1);
    }
    if (lexer.getNumberOfSyntaxErrors() != 0)
    {
        cout.flush();
        exit(1);
    }
    
    // Create error handler
    ErrorHandler errorHandler;

    // Visit tree and linearize
    CodeGenVisitor v(errorHandler, controlFlowGraph);
    v.visit(tree);

    if (errorHandler.hasError())
    {
        cout.flush();
        exit(1);
    }

    controlFlowGraph.initStandardFunctions(v.getGlobalSymbolTable());

    // Optimize IR
    if(controlFlowGraph.getOptimized()) {
        controlFlowGraph.optimizeIR();
    }

    // Generate ASM instructions
    stringstream out;
    controlFlowGraph.generateASM(out);

    // Optimize ASM instructions
    if(controlFlowGraph.getOptimized()) {
        controlFlowGraph.optimizeASM(out, cout);
    }
    else {
        cout << out.str();
    }

    return 0;
}

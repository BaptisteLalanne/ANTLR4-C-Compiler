#include "CodeGenVisitor.h"

using namespace std;

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitBody(ifccParser::ProgContext *ctx) 
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitEnd(ifccParser::ProgContext *ctx) 
{
	/*
	int retval = stoi(ctx->CONST()->getText()); // ou alors VAR... ça dépend
	cout << " 	movl	$" << retval << ", %eax\n"
			" 	ret\n";
	*/
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitVarDeclaration(ifccParser::ProgContext *ctx) 
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitConstAffectation(ifccParser::ProgContext *ctx) 
{
	
	/* Exemple avec "VAR(-12) = 42;"
	movl	$42, -12(%rbp)
	*/
	
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitVarAffectation(ifccParser::ProgContext *ctx) 
{
	
	/* Exemple avec "VAR(-4) = VAR(-12);"
	movl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)
	*/
	
	return visitChildren(ctx);
}
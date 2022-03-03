#include "CodeGenVisitor.h"

using namespace std;

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) {
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitBody(ifccParser::ProgContext *ctx) {
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitEnd(ifccParser::ProgContext *ctx) {
	/*
	int retval = stoi(ctx->CONST()->getText()); // ou alors VAR... ça dépend
	cout << " 	movl	$" << retval << ", %eax\n"
			" 	ret\n";
	*/
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitVarDeclr(ifccParser::ProgContext *ctx) {
	// add variable to symbol table
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitVarDeclrConstAffect(ifccParser::ProgContext *ctx) {
	// add variable to symbol table,
	// write instruction to put the given constant in memory
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitVarDeclrVarAffect(ifccParser::ProgContext *ctx) {
	// add variable to symbol table,
	// write instruction to put the contents of the given variable in memory
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitConstAffect(ifccParser::ProgContext *ctx) {
	/* Exemple avec "VAR(-12) = 42;"
	movl	$42, -12(%rbp)
	*/
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitVarAffect(ifccParser::ProgContext *ctx) {
	/* Exemple avec "VAR(-4) = VAR(-12);"
	movl	-12(%rbp), %rax
	movl	%rax, -4(%rbp)
	*/
	return visitChildren(ctx);
}
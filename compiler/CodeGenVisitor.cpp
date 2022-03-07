/*************************************************************************
                          PLD Compiler : CodeGenVisitor
                          ---------------------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

//---- Implementation of class <CodeGenVisitor> (file CodeGenVisitor.cpp) -----/
#include "CodeGenVisitor.h"

using namespace std;

antlrcpp::Any CodeGenVisitor::visitMainHeader(ifccParser::MainHeaderContext *ctx) {
	cout << ".globl	main" << endl;
	cout << "main:" << endl;
	cout << "	pushq	%rbp" << endl;
	cout << "	movq	%rsp, %rbp" << endl;
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitAddExpr(ifccParser::AddExprContext *ctx) {
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitSubExpr(ifccParser::SubExprContext *ctx) {
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitMulExpr(ifccParser::MulExprContext *ctx) {
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitDivExpr(ifccParser::DivExprContext *ctx) {
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) {
	
	// Fetch constant's info
	int constValue = stoi(ctx->CONST()->getText());
	
	// Write assembly instructions
	cout << "	movl	$" << constValue << ", %eax" << endl;
	
	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
	
	// Fetch variable
	string varName = ctx->VAR()->getText();
	// Check errors
	if (!symbolTable.hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Fetch variable's infos, mark it as used
	symbolTable.getVar(varName).isUsed = true;
	int varOffset = symbolTable.getVar(varName).memoryOffset;
	
	// Write assembly instructions
	cout << "	movl	" << varOffset << "(%rbp), %ebx" << endl;
	cout << "	movl	%ebx, %eax" << endl;
	
	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitVarDeclr(ifccParser::VarDeclrContext *ctx) {
	
	// Fetch variable
	string dVarName = ctx->VAR()->getText();
	string dVarType = ctx->TYPE()->getText();
	// Check errors
	if (symbolTable.hasVar(dVarName)) {
		string message =  "Variable " + dVarName + " has already been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Add variable to symbol table
	symbolTable.addVar(dVarName, dVarType, "local", ctx->getStart()->getLine());
	int dVarOffset = symbolTable.getVar(dVarName).memoryOffset;
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDeclrAndAffect(ifccParser::VarDeclrAndAffectContext *ctx) {
	
	// Fetch variable
	string dVarName = ctx->VAR()->getText();
	string dVarType = ctx->TYPE()->getText();
	// Check errors
	if (symbolTable.hasVar(dVarName)) {
		string message =  "Variable " + dVarName + " has already been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Add variable to symbol table
	symbolTable.addVar(dVarName, dVarType, "local", ctx->getStart()->getLine());
	int dVarOffset = symbolTable.getVar(dVarName).memoryOffset;
	
	// Compute expression
	visit(ctx->expr());
	
	// Write assembly instructions
	cout << "	movl	%eax, " << dVarOffset << "(%rbp)" << endl;
	
	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitAffect(ifccParser::AffectContext *ctx) {
	
	// Fetch first variable
	string varName = ctx->VAR()->getText();
	// Check for errors
	if (!symbolTable.hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Fetch first variable's infos
	int varOffset = symbolTable.getVar(varName).memoryOffset;
	
	// Compute expression
	visit(ctx->expr());
	
	// Write assembly instructions
	cout << "	movl	%eax, " << varOffset << "(%rbp)" << endl;
	
	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitEnd(ifccParser::EndContext *ctx) {
	
	// Compute expression
	visit(ctx->expr());
	
	// Write assembly instructions
	cout << "	popq	%rbp\n" << "	ret" << endl;
	
	// Static Analysis
	symbolTable.checkUsedVariables(errorHandler);
	
	return 0;
	
}
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
	// Fetch variable
	string expr1 = ctx->expr(0)->getText();
	string expr2 = ctx->expr(1)->getText();

	// Visit first expression
	visit(ctx->expr(0));

	// Move result of first expression into EDX register
	cout << "	movl	%eax, %edx" << endl;

	// Visit second expression
	visit(ctx->expr(1));

	// Do addition
	cout << "	addl	%edx, %eax" << endl;
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitSubExpr(ifccParser::SubExprContext *ctx) {
	// Fetch variable
	string expr1 = ctx->expr(0)->getText();
	string expr2 = ctx->expr(1)->getText();

	// Visit first expression
	visit(ctx->expr(0));

	// Move result of first expression into EDX register
	cout << "	movl	%eax, %edx" << endl;

	// Visit second expression
	visit(ctx->expr(1));

	// Do substraction
	cout << "	subl	%eax, %edx" << endl;
	cout << "	movl	%edx, %eax" << endl;
	
	return 0;
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
	
	// Number of variable to declare
	int numVariable = ctx->VAR().size();
	// Fetch type
	string dVarType = ctx->TYPE()->getText();
	for(int i = 0 ; i < numVariable ; i++) {
		// Fetch variable
		string dVarName = ctx->VAR(i)->getText();
		// Check errors
		if (symbolTable.hasVar(dVarName)) {
			string message =  "Variable " + dVarName + " has already been declared";
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
			return -1;
		}
		// Add variable to symbol table
		symbolTable.addVar(dVarName, dVarType, "local", ctx->getStart()->getLine());
		int dVarOffset = symbolTable.getVar(dVarName).memoryOffset;
	}
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

antlrcpp::Any CodeGenVisitor::visitExprEnd(ifccParser::ExprEndContext *ctx) {
	
	// Compute expression
	visit(ctx->expr());
	
	returned = true;

	// Write assembly instructions
	cout << "	popq	%rbp\n" << "	ret" << endl;
	
	// Static Analysis
	symbolTable.checkUsedVariables(errorHandler);
	
	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitEmptyEnd(ifccParser::EmptyEndContext *ctx) {
	
	returned = true;

	// Write assembly instructions
	cout << "	movl	$0, %eax"<< endl;
	cout << "	popq	%rbp\n" << "	ret" << endl;
	
	// Static Analysis
	symbolTable.checkUsedVariables(errorHandler);
	
	return 0;

}

void CodeGenVisitor::returnZero() {
	cout << "	movl	$0, %eax"<< endl;
	cout << "	popq	%rbp\n" << "	ret" << endl;
}

bool CodeGenVisitor::hasReturned() {
	return returned;
}
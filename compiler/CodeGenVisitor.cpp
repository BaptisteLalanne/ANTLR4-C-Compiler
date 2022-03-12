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

antlrcpp::Any CodeGenVisitor::visitAddSubExpr(ifccParser::AddSubExprContext *ctx) {

	cout << "#enter visitAddSubExpr: " << ctx->getText() << endl;

	char op = ctx->OP2()->getText()[0];

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	int var1Offset = var1.memoryOffset;
	int var2Offset = var2.memoryOffset;

	// Do addition
	if (op == '+') {
		cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
		cout << "	addl	" << var2Offset << "(%rbp), %eax" << endl;
	} 
	// Do substraction
	else {
		cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
		cout << "	subl	" << var2Offset << "(%rbp), %eax" << endl;
	}

	// Create temporary variable with the intermediary result
	tempVarCounter++;
	string newVar = "!tmp" + to_string(tempVarCounter);
	string newVarType = "int";
	symbolTable.addVar(newVar, newVarType, "temporary", ctx->getStart()->getLine());
	symbolTable.getVar(newVar).isUsed = true;
	int newVarOffset = symbolTable.getVar(newVar).memoryOffset;
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << newVarOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return symbolTable.getVar(newVar);

}

antlrcpp::Any CodeGenVisitor::visitMulDivExpr(ifccParser::MulDivExprContext *ctx) {

	cout << "#enter visitMultDivExpr: "  << ctx->getText() << endl;

	char op = ctx->OP1()->getText()[0];

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	int var1Offset = var1.memoryOffset;
	int var2Offset = var2.memoryOffset;

	// Do multiplication
	if (op == '*') {
		cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
		cout << "	imull	" << var2Offset << "(%rbp), %eax" << endl;
	} 
	// Do division
	else {
		cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
		cout << "	cltd" << endl;
		cout << "	idivl	" << var2Offset << "(%rbp)" << endl; 
	}

	// Create temporary variable with the intermediary result
	tempVarCounter++;
	string newVar = "!tmp" + to_string(tempVarCounter);
	string newVarType = "int";
	symbolTable.addVar(newVar, newVarType, "temporary", ctx->getStart()->getLine());
	symbolTable.getVar(newVar).isUsed = true;
	int newVarOffset = symbolTable.getVar(newVar).memoryOffset;
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << newVarOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return symbolTable.getVar(newVar);
	
}

antlrcpp::Any CodeGenVisitor::visitParExpr(ifccParser::ParExprContext *ctx) {
	return visit(ctx->expr());
}

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) {
	
	cout << "#enter visitConstExpr: "  << ctx->getText() << endl;

	// Fetch constant's info
	int constValue = stoi(ctx->CONST()->getText());

	// Create temporary variable with it
	tempVarCounter++;
	string newVar = "!tmp" + to_string(tempVarCounter);
	string newVarType = "int";
	symbolTable.addVar(newVar, newVarType, "temporary", ctx->getStart()->getLine());
	symbolTable.getVar(newVar).isUsed = true;
	int newVarOffset = symbolTable.getVar(newVar).memoryOffset;
 	
	// Write assembly instructions
	cout << "	movl	$" << constValue << ", " << newVarOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return symbolTable.getVar(newVar);
	
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
	
	cout << "#enter visitVarExpr: "  << ctx->getText() << endl;

	// Fetch variable
	string varName = ctx->VAR()->getText();
	// Check errors
	if (!symbolTable.hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Mark it as used
	symbolTable.getVar(varName).isUsed = true;
	
	// Return the variable
	return symbolTable.getVar(varName);
	
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

	// Save current stack pointer
	int currStackPointer = symbolTable.getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());
	int aVarOffset = result.memoryOffset;
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable.setStackPointer(currStackPointer);
	symbolTable.cleanTempVars();
	tempVarCounter = 0;
	
	// Write assembly instructions
	cout << "	movl	" << aVarOffset << "(%rbp), " << dVarOffset << "(%rbp)" << endl;
	
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
	
	// Save current stack pointer
	int currStackPointer = symbolTable.getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());
	int aVarOffset = result.memoryOffset;

	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable.setStackPointer(currStackPointer);
	symbolTable.cleanTempVars();
	tempVarCounter = 0;
	
	// Write assembly instructions
	cout << "	movl	" << aVarOffset << "(%rbp), " << varOffset << "(%rbp)" << endl;
	
	return 0;

}

antlrcpp::Any CodeGenVisitor::visitExprEnd(ifccParser::ExprEndContext *ctx) {
	
	returned = true;

	// Save current stack pointer
	int currStackPointer = symbolTable.getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());
	int aVarOffset = result.memoryOffset;
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable.setStackPointer(currStackPointer);
	symbolTable.cleanTempVars();
	tempVarCounter = 0;

	// Write assembly instructions
	cout << "	movl	" << aVarOffset << "%(rbp), %eax"<< endl;
	cout << "	popq	%rbp" << endl;
	cout << "	ret" << endl;

	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitEmptyEnd(ifccParser::EmptyEndContext *ctx) {

	returnDefault();
	return 0;

}

void CodeGenVisitor::returnDefault() {
	returned = true;
	cout << "	movl	$0, %eax"<< endl;
	cout << "	popq	%rbp" << endl;
	cout << "	ret" << endl;
}

bool CodeGenVisitor::hasReturned() {
	return returned;
}
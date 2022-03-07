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

antlrcpp:: Any CodeGenVisitor::visitMainHeader(ifccParser::MainHeaderContext *ctx) {
	cout << ".globl	main" << endl;
	cout << "main:" << endl;
	cout << "	pushq	%rbp" << endl;
	cout << "	movq	%rsp, %rbp" << endl;
	return visitChildren(ctx);
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

antlrcpp::Any CodeGenVisitor::visitVarDeclrConstAffect(ifccParser::VarDeclrConstAffectContext *ctx) {
	
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
	
	// Fetch constant's info
	int constValue = stoi(ctx->CONST()->getText());
	
	// Write assembly instructions
	cout << "	movl	$" << constValue << ", " << dVarOffset << "(%rbp)" << endl;
	
	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitVarDeclrVarAffect(ifccParser::VarDeclrVarAffectContext *ctx) {
	
	// Fetch variable
	string dVarName = ctx->VAR(0)->getText();
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
	
	// Fetch other variable
	string oVarName = ctx->VAR(1)->getText();
	// Check errors
	if (!symbolTable.hasVar(oVarName)) {
		string message =  "Variable " + oVarName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Fetch other variable's infos, mark it as used
	symbolTable.getVar(oVarName).isUsed = true;
	int oVarOffset = symbolTable.getVar(oVarName).memoryOffset;
	
	// Write assembly instructions
	cout << "	movl	" << oVarOffset << "(%rbp), %eax" << endl;
	cout << "	movl	%eax, " << dVarOffset << "(%rbp)" << endl;
	
	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitConstAffect(ifccParser::ConstAffectContext *ctx) {
	
	// Fetch variable
	string varName = ctx->VAR()->getText();
	// Check errors
	if (!symbolTable.hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Fetch variable's infos
	int varOffset = symbolTable.getVar(varName).memoryOffset;
	
	// Fetch constant's infos
	int constValue = stoi(ctx->CONST()->getText());
	
	// Write assembly instructions
	cout << "	movl	$" << constValue << ", " << varOffset << "(%rbp)" << endl;
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarAffect(ifccParser::VarAffectContext *ctx) {
	
	// Fetch first variable
	string varName = ctx->VAR(0)->getText();
	// Check for errors
	if (!symbolTable.hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Fetch first variable's infos
	int varOffset = symbolTable.getVar(varName).memoryOffset;
	
	// Fetch second variable
	string oVarName = ctx->VAR(1)->getText();
	// Check for errors
	if (!symbolTable.hasVar(oVarName)) {
		string message =  "Variable " + oVarName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Fetch second variable's infos, mark it as used
	int oVarOffset = symbolTable.getVar(oVarName).memoryOffset;
	symbolTable.getVar(oVarName).isUsed = true;
	
	// Write assembly instructions
	cout << "	movl	" << oVarOffset << "(%rbp), %eax" << endl;
	cout << "	movl	%eax, " << varOffset << "(%rbp)" << endl;
	
	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitConstEnd(ifccParser::ConstEndContext *ctx) {
	
	// Fetch constant's info
	int retConst = stoi(ctx->CONST()->getText());
	
	// Write assembly instructions
	cout << "	movl	$" << retConst << ",  %eax" << endl;
	cout << "	popq	%rbp\n" << "	ret" << endl;
	
	// Static Analysis
	for (auto v : symbolTable.varMap)
	{
		if (!v.second.isUsed) {
			string message =  "Variable " + v.first + " is not used";
			errorHandler.signal(WARNING, message, v.second.varLine);
		}
	}
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarEnd(ifccParser::VarEndContext *ctx) {
	
	// Fetch return variable
	string retVar = ctx->VAR()->getText();
	// Check errors
	if (!symbolTable.hasVar(retVar)) {
		string message =  "Variable " + retVar + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return -1;
	}
	// Fetch variable's infos, mark it as used
	int retVarOffset = symbolTable.getVar(retVar).memoryOffset;
	symbolTable.getVar(retVar).isUsed = true;
	
	// Write assembly instructions
	cout << "	movl	" << retVarOffset << "(%rbp), %eax" << endl;
	cout << "	popq	%rbp\n" << "	ret" << endl;
	
	// Static Analysis
	for (auto v : symbolTable.varMap)
	{
		if (!v.second.isUsed) {
			string message =  "Variable " + v.first + " is not used";
			errorHandler.signal(WARNING, message, v.second.varLine);
		}
	}
	
	return 0;
	
}
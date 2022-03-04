#include "CodeGenVisitor.h"

using namespace std;

antlrcpp::Any CodeGenVisitor::visitVarDeclr(ifccParser::VarDeclrContext *ctx) {
	// Add variable to symbol table
	string dVarName = ctx->VAR()->getText();
	string dVarType = ctx->TYPE()->getText();
	symbolTable.addVar(dVarName, dVarType, "local");
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDeclrConstAffect(ifccParser::VarDeclrConstAffectContext *ctx) {
	// Add variable to symbol table
	string dVarName = ctx->VAR()->getText();
	string dVarType = ctx->TYPE()->getText();
	symbolTable.addVar(dVarName, dVarType, "local");
	int dVarOffset = symbolTable.getVar(dVarName).memoryOffset;
	// Fetch info
	int constValue = stoi(ctx->CONST()->getText());
	// Write assembler instructions
	cout << "movl	$" << constValue << ", " << dVarOffset << "(%rbp)" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDeclrVarAffect(ifccParser::VarDeclrVarAffectContext *ctx) {
	// Add variable to symbol table
	string dVarName = ctx->VAR(0)->getText();
	string dVarType = ctx->TYPE()->getText();
	symbolTable.addVar(dVarName, dVarType, "local");
	int dVarOffset = symbolTable.getVar(dVarName).memoryOffset;
	// Fetch info
	string oVarName = ctx->VAR(1)->getText();
	int oVarOffset = symbolTable.getVar(oVarName).memoryOffset;
	// Write assembler instructions
	cout << "movl	" << oVarOffset << "(%rbp), %rax" << endl;
	cout << "movl	%rax, " << dVarOffset << "(%rbp)" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitConstAffect(ifccParser::ConstAffectContext *ctx) {
	// Fetch info
	string varName = ctx->VAR()->getText();
	int varOffset = symbolTable.getVar(varName).memoryOffset;
	int constValue = stoi(ctx->CONST()->getText());
	// Write assembler instructions
	cout << "movl	$" << constValue << ", " << varOffset << "(%rbp)" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarAffect(ifccParser::VarAffectContext *ctx) {
	// Fetch info
	string varName = ctx->VAR(0)->getText();
	int varOffset = symbolTable.getVar(varName).memoryOffset;
	string oVarName = ctx->VAR(1)->getText();
	int oVarOffset = symbolTable.getVar(oVarName).memoryOffset;
	// Write assembler instructions
	cout << "movl	" << oVarOffset << "(%rbp), %rax" << endl;
	cout << "movl	%rax, " << varOffset << "(%rbp)" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitConstEnd(ifccParser::ConstEndContext *ctx) {
	// Fetch info
	int retConst = stoi(ctx->CONST()->getText());
	// Write assembler instructions
	cout << "movl	$" << retConst << ",  %eax" << endl;
	cout << "ret" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarEnd(ifccParser::VarEndContext *ctx) {
	// Fetch info
	string retVar = ctx->VAR()->getText();
	int retVarOffset = symbolTable.getVar(retVar).memoryOffset;
	// Write assembler instructions
	cout << "movl	" << retVarOffset << "(%rbp), %eax" << endl;
	cout << "ret" << endl;
	return 0;
}
#include "CodeGenVisitor.h"

using namespace std;

/*antlrcpp:: Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) {
	cout <<".globl	main\n"
		" main:" << endl;
	visit(ctx->body());
	return 0;
}*/

antlrcpp::Any CodeGenVisitor::visitVarDeclr(ifccParser::VarDeclrContext *ctx) {
	// Add variable to symbol table
	string dVarName = ctx->VAR()->getText();
	string dVarType = ctx->TYPE()->getText();
	symbolTable.addVar(dVarName, dVarType, "local", ctx->getStart()->getLine());
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDeclrConstAffect(ifccParser::VarDeclrConstAffectContext *ctx) {
	// Add variable to symbol table
	string dVarName = ctx->VAR()->getText();
	string dVarType = ctx->TYPE()->getText();
	symbolTable.addVar(dVarName, dVarType, "local", ctx->getStart()->getLine());
	int dVarOffset = symbolTable.getVar(dVarName).memoryOffset;
	// Fetch info
	int constValue = stoi(ctx->CONST()->getText());
	// Write assembly instructions
	cout << "	movl	$" << constValue << ", " << dVarOffset << "(%rbp)" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDeclrVarAffect(ifccParser::VarDeclrVarAffectContext *ctx) {
	// Add variable to symbol table
	string dVarName = ctx->VAR(0)->getText();
	string dVarType = ctx->TYPE()->getText();
	symbolTable.addVar(dVarName, dVarType, "local", ctx->getStart()->getLine());
	int dVarOffset = symbolTable.getVar(dVarName).memoryOffset;
	// Fetch info
	string oVarName = ctx->VAR(1)->getText();
	symbolTable.getVar(oVarName).isUsed = true;
	int oVarOffset = symbolTable.getVar(oVarName).memoryOffset;
	// Write assembly instructions
	cout << "	movl	" << oVarOffset << "(%rbp), %eax" << endl;
	cout << "	movl	%eax, " << dVarOffset << "(%rbp)" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitConstAffect(ifccParser::ConstAffectContext *ctx) {
	// Fetch info
	string varName = ctx->VAR()->getText();
	int varOffset = symbolTable.getVar(varName).memoryOffset;
	int constValue = stoi(ctx->CONST()->getText());
	// Write assembly instructions
	cout << "	movl	$" << constValue << ", " << varOffset << "(%rbp)" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarAffect(ifccParser::VarAffectContext *ctx) {
	// Fetch info
	string varName = ctx->VAR(0)->getText();
	int varOffset = symbolTable.getVar(varName).memoryOffset;
	string oVarName = ctx->VAR(1)->getText();
	symbolTable.getVar(oVarName).isUsed = true;
	int oVarOffset = symbolTable.getVar(oVarName).memoryOffset;
	// Write assembly instructions
	cout << "	movl	" << oVarOffset << "(%rbp), %eax" << endl;
	cout << "	movl	%eax, " << varOffset << "(%rbp)" << endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitConstEnd(ifccParser::ConstEndContext *ctx) {
	// Fetch info
	string varName = ctx->CONST()->getText();
	int retConst = stoi(varName);
	symbolTable.getVar(varName).isUsed = true;
	// Write assembly instructions
	cout << "	movl	$" << retConst << ",  %eax" << endl;
	cout << "	popq	%rbp\n" << "	ret" << endl;
	// Static Analisys
	for (auto v : symbolTable.varMap)
	{
		if (!v.second.isUsed) {
			string message =  "Variable " + v.first + " is not used";
			eH.generateMessage(WARNING, message, v.second.varLine);
		}
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarEnd(ifccParser::VarEndContext *ctx) {
	// Fetch info
	string retVar = ctx->VAR()->getText();
	int retVarOffset = symbolTable.getVar(retVar).memoryOffset;
	symbolTable.getVar(retVar).isUsed = true;
	// Write assembly instructions
	cout << "	movl	" << retVarOffset << "(%rbp), %eax" << endl;
	cout << "	popq	%rbp\n" << "	ret" << endl;
	// Static Analisys
	for (auto v : symbolTable.varMap)
	{
		if (!v.second.isUsed) {
			string message =  "Variable " + v.first + " is not used";
			eH.generateMessage(WARNING, message, v.second.varLine);
		}
	}
	return 0;
}
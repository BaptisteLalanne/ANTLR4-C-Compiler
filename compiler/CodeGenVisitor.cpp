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

antlrcpp::Any CodeGenVisitor::visitUnaryExpr(ifccParser::UnaryExprContext *ctx) {

	cout << "#enter visitUnaryExpr: " << ctx->getText() << endl;

	char op = ctx->UNARY->getText()[0];

	// Fetch sub-expressions
	varStruct var = visit(ctx->expr());
	int varOffset = var.memoryOffset;

	// Apply the ! operator
	if (op == '!') {
		cout << "	cmpl	$0, " << varOffset << "(%rbp)" << endl;
		cout << "	sete	%al" << endl;
		cout << "	movzbl	%al, %eax" << endl;
	} else {
		cout << "	movl	" << varOffset << "(%rbp), %eax" << endl;
		cout << "	negl	%eax" << endl;
	}
	// Create temporary variable with the intermediary result
	varStruct tmp = createTempVar(ctx);
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitAndExpr(ifccParser::AndExprContext *ctx) {
	
	cout << "#enter visitAndExpr: " << ctx->getText() << endl;

	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	int var1Offset = var1.memoryOffset;
	int var2Offset = var2.memoryOffset;

	//Do And
	cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
	cout << "	andl	" << var2Offset << "(%rbp), %eax" << endl;
	
	// Create temporary variable with the intermediary result
	varStruct tmp = createTempVar(ctx);
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitXorExpr(ifccParser::XorExprContext *ctx) {

	cout << "#enter visitXorExpr: " << ctx->getText() << endl;

	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	int var1Offset = var1.memoryOffset;
	int var2Offset = var2.memoryOffset;

	//Do Xor
	cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
	cout << "	xorl	" << var2Offset << "(%rbp), %eax" << endl;

	// Create temporary variable with the intermediary result
	varStruct tmp = createTempVar(ctx);
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitOrExpr(ifccParser::OrExprContext *ctx) {
	
	cout << "#enter visitOrExpr: " << ctx->getText() << endl;
	
	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	int var1Offset = var1.memoryOffset;
	int var2Offset = var2.memoryOffset;
	
	//Do Or
	cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
	cout << "	orl	" << var2Offset << "(%rbp), %eax" << endl;

	// Create temporary variable with the intermediary result
	varStruct tmp = createTempVar(ctx);
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitAddSubExpr(ifccParser::AddSubExprContext *ctx) {

	cout << "#enter visitAddSubExpr: " << ctx->getText() << endl;

	char op = ctx->OP2->getText()[0];

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));

    if(!var1.isCorrect || !var2.isCorrect) {
		
        return symbolTable.dummyVarStruct;
    }

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

	varStruct tmp = createTempVar(ctx);
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitMulDivModExpr(ifccParser::MulDivModExprContext *ctx) {

	cout << "#enter visitMultDivModExpr: "  << ctx->getText() << endl;

	char op = ctx->OP1->getText()[0];

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));

    if(!var1.isCorrect || !var2.isCorrect) {
        return symbolTable.dummyVarStruct;
    }

	int var1Offset = var1.memoryOffset;
	int var2Offset = var2.memoryOffset;

	// Do multiplication
	if (op == '*') {
		cout << "#enter * case" << endl;
		cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
		cout << "	imull	" << var2Offset << "(%rbp), %eax" << endl;
	} 
	// Do division
	else {
		cout << "#enter / or \% case" << endl;
		cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
		cout << "	cltd" << endl;
		cout << "	idivl	" << var2Offset << "(%rbp)" << endl; 
	}

	varStruct tmp = createTempVar(ctx);

	// Write expression result (which is in %eax) in new var
	if(op == '%')
	{
		cout << "	movl	%edx, " << tmp.memoryOffset << "(%rbp)" << endl;
	}else {
		cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	}
	
	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitCmpLessOrGreaterExpr(ifccParser::CmpLessOrGreaterExprContext *ctx) {

	cout << "#enter visitCmpLessOrGreaterExpr: " << ctx->getText() << endl;
	
	char op = ctx->CMP->getText()[0];

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));

    if(!var1.isCorrect || !var2.isCorrect) {
        return symbolTable.dummyVarStruct;
    }

	int var1Offset = var1.memoryOffset;
	int var2Offset = var2.memoryOffset;

	// Do comparaison
	cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
	cout << "	cmpl	" << var2Offset << "(%rbp), %eax" << endl;
	// Less than comparaison
	if (op == '<') {
		cout << "	setl	%al" << endl;
	}
	// Greater than comparaison
	else {
		cout << "	setg	%al" << endl;
	}
	cout << "	movzbl	%al, %eax" << endl;
	
	varStruct tmp = createTempVar(ctx);
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitCmpEqualityExpr(ifccParser::CmpEqualityExprContext *ctx) {
	
	cout << "#enter visitCmpEqualExpr: " << ctx->getText() << endl;
	
	char op = ctx->EQ->getText()[0];

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));

    if(!var1.isCorrect || !var2.isCorrect) {
        return symbolTable.dummyVarStruct;
    }

	int var1Offset = var1.memoryOffset;
	int var2Offset = var2.memoryOffset;

	// Do an equality comparaison
	cout << "	movl	" << var1Offset << "(%rbp), %eax" << endl;
	cout << "	cmpl	" << var2Offset << "(%rbp), %eax" << endl;
	// Equal comparaison
	if (op == '=') {
		cout << "	sete	%al" << endl;
	}
	// Not equal comparaison
	else {
		cout << "	setne	%al" << endl;
	}
	cout << "	movzbl	%al, %eax" << endl;
	
	varStruct tmp = createTempVar(ctx);
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitParExpr(ifccParser::ParExprContext *ctx) {
	return visit(ctx->expr());
}

antlrcpp::Any CodeGenVisitor::visitAffExpr(ifccParser::AffExprContext *ctx) {
	
	// Fetch first variable
	string varName = ctx->VAR()->getText();
	// Check for errors
	if (!symbolTable.hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return symbolTable.dummyVarStruct;
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
	
	// Write assembly instructions to save expression in variable 
	cout << "	movl	" << aVarOffset << "(%rbp), %eax" << endl;
	cout << "	movl	%eax, " << varOffset << "(%rbp)" << endl;

	// Create new temporary variable holding the result
	varStruct tmp = createTempVar(ctx);
 	
	// Write expression result (which is in %eax) in new var
	cout << "	movl	%eax, " << tmp.memoryOffset << "(%rbp)" << endl;
	
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) {
	
	cout << "#enter visitConstExpr: "  << ctx->getText() << endl;

	int constValue;

	// Size of INT
	long intSize = (long)INT_MAX - (long)INT_MIN + 1;

	//deal with std::out_of_range
	try{ 
		// Fetch constant's info as ull
		unsigned long long ullConstValue = stoull(ctx->CONST()->getText());
		
		// make it a int
		ullConstValue = ullConstValue % intSize;
		if(ullConstValue>INT_MAX) constValue = ullConstValue-intSize;
		else constValue = ullConstValue;

	} catch(std::out_of_range& e){ //if ctx->CONST()->getText() is too big for uul

		// Fetch constant's info as ull
		string constStr = ctx->CONST()->getText();
		
		long lConstValue = 0;
		int currentDigit;
		//iterate through each char in string (left to right)
		for ( string::iterator it=constStr.begin(); it!=constStr.end(); ++it){	
			currentDigit = *it - '0';
			if(currentDigit >= 0 && currentDigit < 10){
				lConstValue = lConstValue*10 + currentDigit;
				if(lConstValue > INT_MAX){
					lConstValue -= intSize;
				}
			}
		}
		//should be already good, but it makes gcc happy
		constValue = (int)lConstValue;

		//warning
		string message =  "Integer constant is too large for its type.\nOverflow in conversion to ‘int’ changes value from ‘" + constStr + "’ to ‘" + to_string(constValue) + "’";
		errorHandler.signal(WARNING, message, ctx->getStart()->getLine());
	}

	varStruct tmp = createTempVar(ctx);
 	
	// Write assembly instructions
	cout << "	movl	$" << constValue << ", " << tmp.memoryOffset << "(%rbp)" << endl;
	
	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
	
	cout << "#enter visitVarExpr: "  << ctx->getText() << endl;

	// Fetch variable
	string varName = ctx->VAR()->getText();
	// Check errors
	if (!symbolTable.hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return symbolTable.dummyVarStruct;
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
			return 1;
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
        return 1;
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
	cout << "	movl	" << aVarOffset << "(%rbp), %eax" << endl;
	cout << "	movl	%eax, " << dVarOffset << "(%rbp)" << endl;
	
	return 0;

}

antlrcpp::Any CodeGenVisitor::visitExprEnd(ifccParser::ExprEndContext *ctx) {
	
	returned = true;

	// Save current stack pointer
	int currStackPointer = symbolTable.getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());

    if (!result.isCorrect) {
        cout << "	popq	%rbp" << endl;
        cout << "	ret" << endl;
        return 1;
    }

	int aVarOffset = result.memoryOffset;
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable.setStackPointer(currStackPointer);
	symbolTable.cleanTempVars();
	tempVarCounter = 0;

	// Write assembly instructions
	cout << "	movl	" << aVarOffset << "(%rbp), %eax"<< endl;
	cout << "	popq	%rbp" << endl;
	cout << "	ret" << endl;

	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitEmptyEnd(ifccParser::EmptyEndContext *ctx) {
	returned = true;
	cout << "	movl	$41, %eax"<< endl;
	cout << "	popq	%rbp" << endl;
	cout << "	ret" << endl;
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

varStruct CodeGenVisitor::createTempVar(antlr4::ParserRuleContext *ctx) {

	// Create temporary variable with the intermediary result
	tempVarCounter++;
	string newVar = "!tmp" + to_string(tempVarCounter);
	string newVarType = "int";
	symbolTable.addVar(newVar, newVarType, "temporary", ctx->getStart()->getLine());
	symbolTable.getVar(newVar).isUsed = true;
	return symbolTable.getVar(newVar);

}
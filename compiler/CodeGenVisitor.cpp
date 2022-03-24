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
	cfg.getCurrentBB()->addInstr(Instr::call, {"main"});
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitUnaryExpr(ifccParser::UnaryExprContext *ctx) {

	// Fetch sub-expressions
	varStruct var = visit(ctx->expr());
	varStruct tmp = createTempVar(ctx);

	// Apply the operators
	char op = ctx->UNARY->getText()[0];
	switch(op) {
		case '!':
			cfg.getCurrentBB()->addInstr(Instr::op_not, {var.varName, tmp.varName});
			break;
		case '-':
			cfg.getCurrentBB()->addInstr(Instr::op_minus, {var.varName, tmp.varName});
			break;
	}
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitAndExpr(ifccParser::AndExprContext *ctx) {

	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_and, {var1.varName, var2.varName, tmp.varName});
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitXorExpr(ifccParser::XorExprContext *ctx) {

	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_xor, {var1.varName, var2.varName, tmp.varName});
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitOrExpr(ifccParser::OrExprContext *ctx) {
	
	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);
	
	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_or, {var1.varName, var2.varName, tmp.varName});
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitAddSubExpr(ifccParser::AddSubExprContext *ctx) {

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

    if(!var1.isCorrect || !var2.isCorrect) {
        return symbolTable.dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->OP2->getText()[0];
	switch (op) {
		case '+':
			cfg.getCurrentBB()->addInstr(Instr::op_add, {var1.varName, var2.varName, tmp.varName});
			break;
		case '-':
			cfg.getCurrentBB()->addInstr(Instr::op_sub, {var1.varName, var2.varName, tmp.varName});
			break;
	}

	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitMulDivModExpr(ifccParser::MulDivModExprContext *ctx) {

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

    if(!var1.isCorrect || !var2.isCorrect) {
        return symbolTable.dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->OP1->getText()[0];
	switch (op) {
		case '*':
			cfg.getCurrentBB()->addInstr(Instr::op_mul, {var1.varName, var2.varName, tmp.varName});
			break;
		case '/':
			cfg.getCurrentBB()->addInstr(Instr::op_div, {var1.varName, var2.varName, tmp.varName});
			break;
		case '%':
			cfg.getCurrentBB()->addInstr(Instr::op_mod, {var1.varName, var2.varName, tmp.varName});
			break;
	}

	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitCmpLessOrGreaterExpr(ifccParser::CmpLessOrGreaterExprContext *ctx) {
	
	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

    if(!var1.isCorrect || !var2.isCorrect) {
        return symbolTable.dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->CMP->getText()[0];
	switch (op) {
		case '<':
			cfg.getCurrentBB()->addInstr(Instr::cmp_lt, {var1.varName, var2.varName, tmp.varName});
			break;
		case '>':
			cfg.getCurrentBB()->addInstr(Instr::cmp_gt, {var1.varName, var2.varName, tmp.varName});
			break;
	}
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitCmpEqualityExpr(ifccParser::CmpEqualityExprContext *ctx) {
		
	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

    if(!var1.isCorrect || !var2.isCorrect) {
        return symbolTable.dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->EQ->getText()[0];
	switch (op) {
		case '=':
			cfg.getCurrentBB()->addInstr(Instr::cmp_eq, {var1.varName, var2.varName, tmp.varName});
			break;
		case '!':
			cfg.getCurrentBB()->addInstr(Instr::cmp_neq, {var1.varName, var2.varName, tmp.varName});
			break;
	}
		
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitParExpr(ifccParser::ParExprContext *ctx) {
	return visit(ctx->expr());
}

antlrcpp::Any CodeGenVisitor::visitAffExpr(ifccParser::AffExprContext *ctx) {
	
	// Fetch first variable
	string varName = ctx->TOKENNAME()->getText();

	// Check for errors
	if (!symbolTable.hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return symbolTable.dummyVarStruct;
	}
		
	// Save current stack pointer
	int currStackPointer = symbolTable.getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());

	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable.setStackPointer(currStackPointer);
	symbolTable.cleanTempVars();
	tempVarCounter = 0;
	
	// Write assembly instructions to save expression in variable 
	cfg.getCurrentBB()->addInstr(Instr::copy, {varName, result.varName});

	// Create new temporary variable holding the result
	varStruct tmp = createTempVar(ctx);
	cfg.getCurrentBB()->addInstr(Instr::copy, {tmp.varName, result.varName});
 		
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) {
	
	int constValue;

	// Size of INT
	long intSize = (long)INT_MAX - (long)INT_MIN + 1;

	// Fetch constant's info
	string constStr = ctx->CONST()->getText();
 
	if (constStr.length() == 3 && constStr[0] == '\'' && constStr[2] == '\'') {

		constValue = constStr[1];

	} 
	else if (constStr.length() > 3 && constStr[0] == '\'' && constStr[constStr.length()-1] == '\'') {

		// Warning
		string message =  "Multi-character character constant";
		errorHandler.signal(WARNING, message, ctx->getStart()->getLine());
		
		// Compute value
		constValue = 0;
		for (int i=1 ; i<constStr.length()-1 ; i++){
			constValue = constValue*256 + constStr[i];
		}
	
	} 
	else {

		// Deal with std::out_of_range and std::invalid_argument
		try{ 

			// Transform constant's info as ull
			unsigned long long ullConstValue = stoull(constStr);
			
			// Make it an int
			ullConstValue = ullConstValue % intSize;
			if(ullConstValue>INT_MAX) constValue = ullConstValue-intSize;
			else constValue = ullConstValue;

		} 
		//if ctx->CONST()->getText() is too big for uul
		catch(std::out_of_range& e){ 
			
			long lConstValue = 0;
			int currentDigit;

			// Iterate through each char in string (left to right)
			for (string::iterator it=constStr.begin(); it!=constStr.end(); ++it) {	
				currentDigit = *it - '0';
				if (currentDigit >= 0 && currentDigit < 10) {
					lConstValue = lConstValue*10 + currentDigit;
					if (lConstValue > INT_MAX) {
						lConstValue -= intSize;
					}
				}
			}

			// Should be already good, but it makes gcc happy
			constValue = (int)lConstValue;

			// Warning
			string message =  "Integer constant is too large for its type.\nOverflow in conversion to 'int' changes value from '" + constStr + "' to '" + to_string(constValue) + "'";
			errorHandler.signal(WARNING, message, ctx->getStart()->getLine());

		} 
		catch(std::invalid_argument& e){
			
			//Error
			string message =  "Integer constant threw invalid argument exception : " + constStr;
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		}

	}

	varStruct tmp = createTempVar(ctx);
 	
	// Write assembly instructions
	cfg.getCurrentBB()->addInstr(Instr::ldconst, {tmp.varName, "$" + to_string(constValue)});
	
	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
	
	// Fetch variable
	string varName = ctx->TOKENNAME()->getText();
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
	int numVariable = ctx->TOKENNAME().size();
	// Fetch type
	string dVarType = ctx->VTYPE()->getText();
	for(int i = 0 ; i < numVariable ; i++) {
		// Fetch variable
		string dVarName = ctx->TOKENNAME(i)->getText();
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
	string dVarName = ctx->TOKENNAME()->getText();
	string dVarType = ctx->VTYPE()->getText();
	// Check errors
	if (symbolTable.hasVar(dVarName)) {
		string message =  "Variable " + dVarName + " has already been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
        return 1;
	}
	// Add variable to symbol table
	symbolTable.addVar(dVarName, dVarType, "local", ctx->getStart()->getLine());

	// Save current stack pointer
	int currStackPointer = symbolTable.getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable.setStackPointer(currStackPointer);
	symbolTable.cleanTempVars();
	tempVarCounter = 0;
	
	// Write assembly instructions
	cfg.getCurrentBB()->addInstr(Instr::copy, {dVarName, result.varName});
	
	return 0;

}

antlrcpp::Any CodeGenVisitor::visitExprEnd(ifccParser::ExprEndContext *ctx) {
	
	returned = true;

	// Save current stack pointer
	int currStackPointer = symbolTable.getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());

    if (!result.isCorrect) {
		cfg.getCurrentBB()->addInstr(Instr::ret, {});
        return 1;
    }

	//int aVarOffset = result.memoryOffset;
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable.setStackPointer(currStackPointer);
	symbolTable.cleanTempVars();
	tempVarCounter = 0;

	// Write assembly instructions
	cfg.getCurrentBB()->addInstr(Instr::ret, {result.varName});

	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitEmptyEnd(ifccParser::EmptyEndContext *ctx) {
	returned = true;
	cfg.getCurrentBB()->addInstr(Instr::ret, {"$41"});
	return 0;
}

void CodeGenVisitor::returnDefault() {
	returned = true;
	cfg.getCurrentBB()->addInstr(Instr::ret, {"$0"});
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
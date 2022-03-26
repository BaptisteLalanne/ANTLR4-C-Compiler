/*************************************************************************
                          PLD Compiler : CodeGenVisitor
                          ---------------------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

//---- Implementation of class <CodeGenVisitor> (file CodeGenVisitor.cpp) -----/
#include "CodeGenVisitor.h"
#include <algorithm>

using namespace std;

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
	cfg.getCurrentBB()->addInstr(Instr::copy, {result.varName, varName});

	// Create new temporary variable holding the result
	varStruct tmp = createTempVar(ctx);
	cfg.getCurrentBB()->addInstr(Instr::copy, {result.varName, tmp.varName});
 		
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
	cfg.getCurrentBB()->addInstr(Instr::ldconst, {"$" + to_string(constValue), tmp.varName});
	
	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
	
	// Fetch variable
	string varName = ctx->TOKENNAME()->getText();

	// If the variable is one of the current function's parameters, return new temporary variable holding the register
	vector<string> funcParams = symbolTable.getFunc(currFunction).parameterNames;
	vector<string>::iterator varPos = find(funcParams.begin(), funcParams.end(), varName);
	if(varPos != funcParams.end()) {
    	
		varStruct tmp = createTempVar(ctx);
 	
		// Write assembly instructions
		cfg.getCurrentBB()->addInstr(Instr::rparam, {tmp.varName, to_string(varPos-funcParams.begin())});
		
		// Return the temporary variable
		return tmp;

	}

	// Otherwise, return the saved variable
	else {

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
	
}

antlrcpp::Any CodeGenVisitor::visitFuncExpr(ifccParser::FuncExprContext *ctx) {

	string funcName = ctx->TOKENNAME()->getText();

	// Check if function is declared 
	if (!symbolTable.hasFunc(funcName)) {
		string message =  "Function " + funcName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return symbolTable.dummyVarStruct;
	}

	funcStruct func = symbolTable.getFunc(funcName);
	
	// Check type error 
	//cout << "RETURN: " << func.returnType << endl;
	if (func.returnType == "void") {
		string message =  "Function " + funcName + " has a void return type";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return symbolTable.dummyVarStruct;
	}

	// Check param number
	int numParams = ctx->expr().size();
	//cout << "PARAMS: " << numParams << " VS " << func.nbParameters << endl;
	if (numParams != func.nbParameters) {
		string message =  "Function " + funcName + " is called with the wrong number of parameters";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return symbolTable.dummyVarStruct;
	}

	// TEMPORARY Error message if there are more than 6 params
	if (numParams > 6) {
		string message =  "Sorry, this compiler does not support more than 6 parameters yet";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return symbolTable.dummyVarStruct;
	}

	// Iterate through parameters and put them into registers
	for(int i = 1 ; i < numParams ; i++) {
		
		// Save current stack pointer
		int currStackPointer = symbolTable.getStackPointer();

		// Compute expression
		varStruct result = visit(ctx->expr(i));

		// Reset the stack pointer and temp variable counter after having evaluated the expression
		symbolTable.setStackPointer(currStackPointer);
		symbolTable.cleanTempVars();
		tempVarCounter = 0;

		// Check param types
		if (result.varType != func.parameterTypes[i]) {
			string message =  "Function " + funcName + " is called with the wrong parameter types";
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
			return symbolTable.dummyVarStruct;
		}
		
		// Write assembly instructions to put the expression into a param register
		cfg.getCurrentBB()->addInstr(Instr::wparam, {result.varName, to_string(i)});

	}

	// Write call instruction
	varStruct tmp = createTempVar(ctx);
	cfg.getCurrentBB()->addInstr(Instr::call, {funcName, tmp.varName});

	return tmp;

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
		symbolTable.addVar(dVarName, dVarType, currFunction, ctx->getStart()->getLine());
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
	symbolTable.addVar(dVarName, dVarType, currFunction, ctx->getStart()->getLine());

	// Save current stack pointer
	int currStackPointer = symbolTable.getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable.setStackPointer(currStackPointer);
	symbolTable.cleanTempVars();
	tempVarCounter = 0;
	
	// Write assembly instructions
	cfg.getCurrentBB()->addInstr(Instr::copy, {result.varName, dVarName});
	
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

antlrcpp::Any CodeGenVisitor::visitMainDeclr(ifccParser::MainDeclrContext *ctx) {

	// Create main function in symbol table (grammar makes sure it can only be declared once)
	symbolTable.addFunc("main", "int", {}, {}, ctx->getStart()->getLine());

	// Set it as the current function
	currFunction = "main";

	// Write function instructions
	cfg.getCurrentBB()->addInstr(Instr::prologue, {"main"});
	visit(ctx->body());
    if (!returned) returnDefault();
	cfg.getCurrentBB()->addInstr(Instr::epilogue, {}); 
	
	return 0;

}


antlrcpp::Any CodeGenVisitor::visitFuncDeclr(ifccParser::FuncDeclrContext *ctx) {

	// Visit header
	funcStruct func = visit(ctx->funcHeader());

	// Set the new function as the current function
	currFunction = func.funcName;

	// Write function instructions
	cfg.getCurrentBB()->addInstr(Instr::prologue, {func.funcName}); 
	visit(ctx->body());
	cfg.getCurrentBB()->addInstr(Instr::epilogue, {}); 

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitFuncHeader(ifccParser::FuncHeaderContext *ctx) {

	string funcName = ctx->TOKENNAME(0)->getText();

	// Fetch parameter names and types
	vector<string> paramTypes = {};
	vector<string> paramNames = {};
	int numParams = ctx->TOKENNAME().size()-1;
	for(int i = 0 ; i < numParams ; i++) {
		paramTypes.push_back( ctx->VTYPE(i)->getText());
		paramNames.push_back(ctx->TOKENNAME(1+i)->getText());
	}

	// Fetch return type
	string returnType = ctx->FTYPE->getText();

	// Check errors
	if (symbolTable.hasFunc(funcName)) {
		string message =  "Function " + funcName + " has already been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return 1; //TODO: return dummy func struct
	}

	// Create function in symbol table (if doesn't exist, otherwise error)
	symbolTable.addFunc(funcName, returnType, paramTypes, paramNames, ctx->getStart()->getLine());

	return symbolTable.getFunc(funcName);

}

varStruct CodeGenVisitor::createTempVar(antlr4::ParserRuleContext *ctx) {
	tempVarCounter++;
	string newVar = "!tmp" + to_string(tempVarCounter);
	string newVarType = "int";
	symbolTable.addVar(newVar, newVarType, currFunction, ctx->getStart()->getLine());
	symbolTable.getVar(newVar).isUsed = true;
	return symbolTable.getVar(newVar);
}
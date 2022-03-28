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

	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct var = visit(ctx->expr());
	varStruct tmp = createTempVar(ctx);

	// Apply the operators
	char op = ctx->UNARY->getText()[0];
	switch(op) {
		case '!':
			cfg.getCurrentBB()->addInstr(Instr::op_not, {var.varName, tmp.varName}, symbolTable);
			break;
		case '-':
			cfg.getCurrentBB()->addInstr(Instr::op_minus, {var.varName, tmp.varName}, symbolTable);
			break;
	}
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitAndExpr(ifccParser::AndExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_and, {var1.varName, var2.varName, tmp.varName}, symbolTable);
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitXorExpr(ifccParser::XorExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_xor, {var1.varName, var2.varName, tmp.varName}, symbolTable);
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitOrExpr(ifccParser::OrExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	//Fetch expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);
	
	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_or, {var1.varName, var2.varName, tmp.varName}, symbolTable);
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitAddSubExpr(ifccParser::AddSubExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

    if(!var1.isCorrect || !var2.isCorrect) {
        return SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->OP2->getText()[0];
	switch (op) {
		case '+':
			cfg.getCurrentBB()->addInstr(Instr::op_add, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
		case '-':
			cfg.getCurrentBB()->addInstr(Instr::op_sub, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
	}

	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitMulDivModExpr(ifccParser::MulDivModExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

    if(!var1.isCorrect || !var2.isCorrect) {
        return SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->OP1->getText()[0];
	switch (op) {
		case '*':
			cfg.getCurrentBB()->addInstr(Instr::op_mul, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
		case '/':
			cfg.getCurrentBB()->addInstr(Instr::op_div, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
		case '%':
			cfg.getCurrentBB()->addInstr(Instr::op_mod, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
	}

	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitCmpLessOrGreaterExpr(ifccParser::CmpLessOrGreaterExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

    if(!var1.isCorrect || !var2.isCorrect) {
        return SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->CMP->getText()[0];
	switch (op) {
		case '<':
			cfg.getCurrentBB()->addInstr(Instr::cmp_lt, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
		case '>':
			cfg.getCurrentBB()->addInstr(Instr::cmp_gt, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
	}
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitCmpEqualityExpr(ifccParser::CmpEqualityExprContext *ctx) {
		
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct var1 = visit(ctx->expr(0));
	varStruct var2 = visit(ctx->expr(1));
	varStruct tmp = createTempVar(ctx);

    if(!var1.isCorrect || !var2.isCorrect) {
        return SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->EQ->getText()[0];
	switch (op) {
		case '=':
			cfg.getCurrentBB()->addInstr(Instr::cmp_eq, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
		case '!':
			cfg.getCurrentBB()->addInstr(Instr::cmp_neq, {var1.varName, var2.varName, tmp.varName}, symbolTable);
			break;
	}
		
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitParExpr(ifccParser::ParExprContext *ctx) {

	return visit(ctx->expr());
}

antlrcpp::Any CodeGenVisitor::visitAffExpr(ifccParser::AffExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch first variable
	string varName = ctx->TOKENNAME()->getText();

	// Check for errors
	if (!symbolTable->hasVar(varName)) {
		string message =  "Variable " + varName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return SymbolTable::dummyVarStruct;
	}
		
	// Save current stack pointer
	int currStackPointer = symbolTable->getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());

	// Reset the stack pointer and temp variable counter after having evaluated the expression
	// symbolTable->setStackPointer(currStackPointer);
	// symbolTable->cleanTempVars();
	// tempVarCounter = 0;
	
	// Write assembly instructions to save expression in variable 
	cfg.getCurrentBB()->addInstr(Instr::copy, {result.varName, varName}, symbolTable);

	// Create new temporary variable holding the result
	varStruct tmp = createTempVar(ctx, result.varType);
	cfg.getCurrentBB()->addInstr(Instr::copy, {result.varName, tmp.varName}, symbolTable);

	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) {
	
	int constValue;
	SymbolTable* symbolTable = symbolTablesStack.top();

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

	varStruct tmp;
 	
	// Write assembly instructions
	if (constStr[0] == '\'') {
		tmp = createTempVar(ctx, "char");
		cfg.getCurrentBB()->addInstr(Instr::ldconst, {"\'" + to_string(constValue), tmp.varName}, symbolTable);
	} else {
		tmp = createTempVar(ctx, "int");
		cfg.getCurrentBB()->addInstr(Instr::ldconst, {"$" + to_string(constValue), tmp.varName}, symbolTable);
	}

	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();
	

	// Fetch variable
	string varName = ctx->TOKENNAME()->getText();

	// Check if var doesn't exist
	bool isParam = symbolTable->hasVar("^"+varName);
	bool isVar = symbolTable->hasVar(varName);

	// If the variable is neither a parameter or a variable of the current symbol table
	if (!isVar && !isParam) {


		// Check if it's a variable of a parent symbol table
		SymbolTable* parentSymbolTable = symbolTable->getParent();
		SymbolTable* previousParent = nullptr;
		while (!isVar && parentSymbolTable != nullptr && previousParent != parentSymbolTable) {
			cout << "#loop: isVar=" << isVar << ", parent=" << parentSymbolTable << endl;
			previousParent = parentSymbolTable;
			parentSymbolTable = symbolTable->getParent();
			isVar = parentSymbolTable->hasVar(varName);
			// Save the variable's actual symbol table
			if (isVar) {
				symbolTable = parentSymbolTable;
			}
		}

		// Throw error if no corresponding variable has been found
		if (!isVar) {
			string message =  "Variable " + varName + " has not been declared";
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
			return SymbolTable::dummyVarStruct;
		}

	}
	
	// If the variable is one of the current function's parameters, return new temporary variable holding the register
	if (!isVar && isParam) {
		varName = "^"+varName;
	}

	// Mark it as used
	symbolTable->getVar(varName).isUsed = true;

	// Return the variable
	return symbolTable->getVar(varName);
	
}

antlrcpp::Any CodeGenVisitor::visitFuncExpr(ifccParser::FuncExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	string funcName = ctx->TOKENNAME()->getText();

	// Check if function is declared 
	if (!globalSymbolTable->hasFunc(funcName)) {
		string message =  "Function " + funcName + " has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return SymbolTable::dummyVarStruct;
	}

	funcStruct func = globalSymbolTable->getFunc(funcName);
	
	// Check type error 
	if (func.returnType == "void") {
		string message =  "Function " + funcName + " has a void return type";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return SymbolTable::dummyVarStruct;
	}

	// Check param number
	int numParams = ctx->expr().size();
	if (numParams != func.nbParameters) {
		string message =  "Function " + funcName + " is called with the wrong number of parameters";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return SymbolTable::dummyVarStruct;
	}

	// TEMPORARY Error message if there are more than 6 params
	if (numParams > 6) {
		string message =  "Sorry, this compiler does not support more than 6 parameters yet";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return SymbolTable::dummyVarStruct;
	}

	// Iterate through parameters and put them into registers
	for(int i = 0 ; i < numParams ; i++) {
		
		// Save current stack pointer
		int currStackPointer = symbolTable->getStackPointer();

		// Compute expression
		varStruct result = visit(ctx->expr(i));

		// Reset the stack pointer and temp variable counter after having evaluated the expression
		// symbolTable->setStackPointer(currStackPointer);
		// symbolTable->cleanTempVars();
		// tempVarCounter = 0;

		// Check param types
		if (result.varType != func.parameterTypes[i]) {
			string message =  "Function " + funcName + " is called with the wrong parameter types";
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
			return SymbolTable::dummyVarStruct;
		}
		
		// Write assembly instructions to put the expression into a param register
		cfg.getCurrentBB()->addInstr(Instr::wparam, {result.varName, to_string(i)}, symbolTable);
		
	}

	// Write call instruction
	varStruct tmp = createTempVar(ctx);
	cfg.getCurrentBB()->addInstr(Instr::call, {funcName, tmp.varName}, symbolTable);

	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitVarDeclr(ifccParser::VarDeclrContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Number of variable to declare
	int numVariable = ctx->TOKENNAME().size();

	// Fetch type
	string dVarType = ctx->vtype()->getText();
	for(int i = 0 ; i < numVariable ; i++) {
		
		// Fetch variable
		string dVarName = ctx->TOKENNAME(i)->getText();

		// Check errors
		if (symbolTable->hasVar(dVarName)) {
			string message =  "Variable " + dVarName + " has already been declared";
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
			return 1;
		}
		if (symbolTable->hasVar("^"+dVarName)) {
			string message =  "Variable " + dVarName + " is already defined as a parameter of the function";
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
			return 1;
		}

		// Add variable to symbol table
		symbolTable->addVar(dVarName, dVarType, ctx->getStart()->getLine());
	}

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitVarDeclrAndAffect(ifccParser::VarDeclrAndAffectContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch variable
	string dVarName = ctx->TOKENNAME()->getText();
	string dVarType = ctx->vtype()->getText();
	// Check errors
	if (symbolTable->hasVar(dVarName)) {
		string message =  "Variable " + dVarName + " has already been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
        return 1;
	}
	if (symbolTable->hasVar("^"+dVarName)) {
		string message =  "Variable " + dVarName + " is already defined as a parameter of the function";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return 1;
	}

	// Add variable to symbol table
	symbolTable->addVar(dVarName, dVarType, ctx->getStart()->getLine());

	// Save current stack pointer
	int currStackPointer = symbolTable->getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	// symbolTable->setStackPointer(currStackPointer);
	// symbolTable->cleanTempVars();
	// tempVarCounter = 0;
	
	// Write assembly instructions
	cfg.getCurrentBB()->addInstr(Instr::copy, {result.varName, dVarName}, symbolTable);
	
	return 0;

}

antlrcpp::Any CodeGenVisitor::visitExprEnd(ifccParser::ExprEndContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();
	returned = true;

	// Save current stack pointer
	int currStackPointer = symbolTable->getStackPointer();

	// Compute expression
	varStruct result = visit(ctx->expr());

    if (!result.isCorrect) {
		cfg.getCurrentBB()->addInstr(Instr::ret, {}, symbolTable);
        return 1;
    }
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	// symbolTable->setStackPointer(currStackPointer);
	// symbolTable->cleanTempVars();
	// tempVarCounter = 0;

	// Write assembly instructions
	cfg.getCurrentBB()->addInstr(Instr::ret, {result.varName}, symbolTable);

	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitEmptyEnd(ifccParser::EmptyEndContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();
	returned = true;
	cfg.getCurrentBB()->addInstr(Instr::ret, {"$41"}, symbolTable);
	return 0;
}

void CodeGenVisitor::returnDefault() {

	SymbolTable* symbolTable = symbolTablesStack.top();
	returned = true;
	cfg.getCurrentBB()->addInstr(Instr::ret, {"$0"}, symbolTable);
}

antlrcpp::Any CodeGenVisitor::visitMainDeclr(ifccParser::MainDeclrContext *ctx) {

	// Create main function in symbol table (grammar makes sure it can only be declared once)
	globalSymbolTable->addFunc("main", "int", {}, {}, ctx->getStart()->getLine());	

		// Create new symbol table
	SymbolTable* newSymbolTable = new SymbolTable(0, globalSymbolTable);
	symbolTablesStack.push(newSymbolTable);

	// Create prologue instructions
	cfg.getCurrentBB()->addInstr(Instr::prologue, {"main"}, newSymbolTable);

	// Create body instructions
	visit(ctx->body());
    if (!returned) returnDefault();

	// Create epilogue instructions
	cfg.getCurrentBB()->addInstr(Instr::epilogue, {}, newSymbolTable); 

	// Visit end 
	visit(ctx->endBlock());
	
	return 0;

}


antlrcpp::Any CodeGenVisitor::visitFuncDeclr(ifccParser::FuncDeclrContext *ctx) {

	// Create new symbol table
	SymbolTable* newSymbolTable = new SymbolTable(0, nullptr);
	symbolTablesStack.push(newSymbolTable);

	// Fetch function name
	string funcName = ctx->TOKENNAME(0)->getText();

	// Fetch parameter names and types
	vector<string> paramTypes = {};
	vector<string> paramNames = {};
	int numParams = ctx->TOKENNAME().size()-1;
	for(int i = 0 ; i < numParams ; i++) {
		// Save names and types
		string paramName = ctx->TOKENNAME(1+i)->getText();
		string paramType = ctx->vtype(i)->getText();
		paramTypes.push_back(paramType);
		paramNames.push_back(paramName);
		// Create param variable in symbol table
		newSymbolTable->addVar("^" + paramName, paramType, ctx->getStart()->getLine());
	}

	// Fetch return type
	string returnType = ctx->FTYPE->getText();

	// Check errors
	if (globalSymbolTable->hasFunc(funcName)) {
		string message =  "Function " + funcName + " has already been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return 1; 
	}

	// Create function in symbol table (if doesn't exist, otherwise error)
	globalSymbolTable->addFunc(funcName, returnType, paramTypes, paramNames, ctx->getStart()->getLine());

	// Create prologue instruction
	cfg.getCurrentBB()->addInstr(Instr::prologue, {funcName}, newSymbolTable); 
	
	// Create instruction that loads register into variable
	for(int i = 0 ; i < numParams ; i++) {
		string paramName = ctx->TOKENNAME(1+i)->getText();
		cfg.getCurrentBB()->addInstr(Instr::rparam, {paramName, to_string(i)}, newSymbolTable);
	}

	// Create body instrctions
	visit(ctx->body());

	// Create epilogue instructions
	cfg.getCurrentBB()->addInstr(Instr::epilogue, {}, newSymbolTable); 

	// Visit end 
	visit(ctx->endBlock());

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitEndBlock(ifccParser::EndBlockContext *ctx) {

	// Static analysis
	symbolTablesStack.top()->checkUsedVariables(errorHandler);

	// Remove symbol table from stack
	symbolTablesStack.pop();

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitVtype(ifccParser::VtypeContext *ctx) {
	return 0;
}


varStruct CodeGenVisitor::createTempVar(antlr4::ParserRuleContext *ctx, string varType) {

	SymbolTable* symbolTable = symbolTablesStack.top();
	tempVarCounter++;
	string newVar = "!tmp" + to_string(tempVarCounter);
	string newVarType = varType;
	symbolTable->addVar(newVar, newVarType, ctx->getStart()->getLine());
	symbolTable->getVar(newVar).isUsed = true;
	return symbolTable->getVar(newVar);
}

varStruct CodeGenVisitor::createTempVar(antlr4::ParserRuleContext *ctx) {
	return this->createTempVar(ctx, "int");
}

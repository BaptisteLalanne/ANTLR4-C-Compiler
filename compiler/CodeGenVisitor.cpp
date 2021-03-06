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

CodeGenVisitor::CodeGenVisitor(ErrorHandler& eH, CFG& cfg) : errorHandler(eH), cfg(cfg) {
	globalSymbolTable = new SymbolTable(0, nullptr);
	this->addSymbolPutchar();
	this->addSymbolGetchar();
}

CodeGenVisitor::~CodeGenVisitor() {
	delete globalSymbolTable;

	while (!symbolTableGarbage.empty()) {
		SymbolTable* _st = symbolTableGarbage.top();
		if (_st != nullptr) {
			delete _st;
			symbolTableGarbage.pop();
		}
	}

}

void CodeGenVisitor::addSymbolPutchar() {
	globalSymbolTable->addFunc("putchar", "int", 1, {"int"}, {"c"}, 0);
}

void CodeGenVisitor::addSymbolGetchar() {
	globalSymbolTable->addFunc("getchar", "int", -1, {}, {}, 0);
}

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) {

	int n = ctx->funcDeclr().size();

	// Visit all function declaration headers
	for (int i = 0; i < n; i++) {
		visitFuncDeclrHeader(ctx->funcDeclr(i));
	}

	// Visit all function declarations
	for (int i = 0; i < n; i++) {
		visitFuncDeclrBody(ctx->funcDeclr(i));
	}

	// Visit main
	visit(ctx->mainDeclr());

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitUnaryExpr(ifccParser::UnaryExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct* var = visit(ctx->expr());
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

	// Apply the operators
	char op = ctx->UNARY->getText()[0];
	switch(op) {
		case '!':
			cfg.getCurrentBB()->addInstr(Instr::op_not, {var->varName, tmp->varName}, symbolTable);
			break;
		case '-':
			cfg.getCurrentBB()->addInstr(Instr::op_minus, {var->varName, tmp->varName}, symbolTable);
			break;
	}
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitAndExpr(ifccParser::AndExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	//Fetch expressions
	varStruct* var1 = visit(ctx->expr(0));
	varStruct* var2 = visit(ctx->expr(1));
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var1->varType == "void" || var2->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_and, {var1->varName, var2->varName, tmp->varName}, symbolTable);
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitXorExpr(ifccParser::XorExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	//Fetch expressions
	varStruct* var1 = visit(ctx->expr(0));
	varStruct* var2 = visit(ctx->expr(1));
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var1->varType == "void" || var2->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_xor, {var1->varName, var2->varName, tmp->varName}, symbolTable);
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitOrExpr(ifccParser::OrExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	//Fetch expressions
	varStruct* var1 = visit(ctx->expr(0));
	varStruct* var2 = visit(ctx->expr(1));
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var1->varType == "void" || var2->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}
	
	// Apply the operator
	cfg.getCurrentBB()->addInstr(Instr::op_or, {var1->varName, var2->varName, tmp->varName}, symbolTable);
	
	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitAddSubExpr(ifccParser::AddSubExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct* var1 = visit(ctx->expr(0));
	varStruct* var2 = visit(ctx->expr(1));
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var1->varType == "void" || var2->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

    if(!var1->isCorrect || !var2->isCorrect) {
        return &SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->OP2->getText()[0];
	switch (op) {
		case '+':
			cfg.getCurrentBB()->addInstr(Instr::op_add, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
		case '-':
			cfg.getCurrentBB()->addInstr(Instr::op_sub, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
	}

	// Return the temporary variable
	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitMulDivModExpr(ifccParser::MulDivModExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct* var1 = visit(ctx->expr(0));
	varStruct* var2 = visit(ctx->expr(1));
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var1->varType == "void" || var2->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

    if(!var1->isCorrect || !var2->isCorrect) {
        return &SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->OP1->getText()[0];
	switch (op) {
		case '*':
			cfg.getCurrentBB()->addInstr(Instr::op_mul, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
		case '/':
			cfg.getCurrentBB()->addInstr(Instr::op_div, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
		case '%':
			cfg.getCurrentBB()->addInstr(Instr::op_mod, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
	}

	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitCmpLessOrGreaterExpr(ifccParser::CmpLessOrGreaterExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct* var1 = visit(ctx->expr(0));
	varStruct* var2 = visit(ctx->expr(1));
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var1->varType == "void" || var2->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

    if(!var1->isCorrect || !var2->isCorrect) {
        return &SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->CMP->getText()[0];
	switch (op) {
		case '<':
			cfg.getCurrentBB()->addInstr(Instr::cmp_lt, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
		case '>':
			cfg.getCurrentBB()->addInstr(Instr::cmp_gt, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
	}
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitCmpEqualityLessGreaterExpr(ifccParser::CmpEqualityLessGreaterExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct* var1 = visit(ctx->expr(0));
	varStruct* var2 = visit(ctx->expr(1));
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var1->varType == "void" || var2->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

    if(!var1->isCorrect || !var2->isCorrect) {
        return &SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->EQLG->getText()[0];
	switch (op) {
		case '<':
			cfg.getCurrentBB()->addInstr(Instr::cmp_eqlt, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
		case '>':
			cfg.getCurrentBB()->addInstr(Instr::cmp_eqgt, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
	}
	
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitCmpEqualityExpr(ifccParser::CmpEqualityExprContext *ctx) {
		
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch sub-expressions
	varStruct* var1 = visit(ctx->expr(0));
	varStruct* var2 = visit(ctx->expr(1));
	varStruct* tmp = createTempVar(ctx);

	// Check void errors
	if (var1->varType == "void" || var2->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

    if(!var1->isCorrect || !var2->isCorrect) {
        return &SymbolTable::dummyVarStruct;
    }

	// Apply the operators
	char op = ctx->EQ->getText()[0];
	switch (op) {
		case '=':
			cfg.getCurrentBB()->addInstr(Instr::cmp_eq, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
		case '!':
			cfg.getCurrentBB()->addInstr(Instr::cmp_neq, {var1->varName, var2->varName, tmp->varName}, symbolTable);
			break;
	}
		
	// Return the temporary variable
	return tmp;
}

antlrcpp::Any CodeGenVisitor::visitParExpr(ifccParser::ParExprContext *ctx) {
	return visit(ctx->expr2());
}

antlrcpp::Any CodeGenVisitor::visitAffExpr(ifccParser::AffExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch first variable
	string varName = ctx->TOKENNAME()->getText();

	// Check for errors
	if (symbolTable->hasVar(varName) == 0 && symbolTable->hasParam(varName) == 0) {
		string message =  "Variable '" + varName + "' has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}
		
	// Save current stack pointer
	int currStackPointer = symbolTable->getStackPointer();
	
	// Compute expression
	varStruct* result = visit(ctx->expr2());

	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable->setStackPointer(currStackPointer);

	// Check void errors
	if (result->varType == "void") {
		string message =  "Cannot assign on void type";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

	// Write assembly instructions to save expression in variable 
	cfg.getCurrentBB()->addInstr(Instr::aff, {result->varName, varName}, symbolTable);

	// Create new temporary variable holding the result
	varStruct* tmp = createTempVar(ctx, result->varType);
	cfg.getCurrentBB()->addInstr(Instr::copy, {result->varName, tmp->varName}, symbolTable);

	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();
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
		string message =  "Use of multi-character character constant";
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
			string message =  "Integer constant is too large for its type. Overflow in conversion to 'int' changes value from '" + constStr + "' to '" + to_string(constValue) + "'";
			errorHandler.signal(WARNING, message, ctx->getStart()->getLine());

		} 
		catch(std::invalid_argument& e){
			
			//Error
			string message =  "Integer constant threw invalid argument exception : " + constStr;
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		}

	}

	varStruct* tmp;
 	
	// Write assembly instructions
	if (constStr[0] == '\'') {
		int* constPtr = new int(constValue);
		tmp = createTempVar(ctx, "char", constPtr);
		// Load each const if we do not add the optimize option
		if(!cfg.getOptimized()){
			cfg.getCurrentBB()->addInstr(Instr::ldconst, {"\'" + to_string(constValue), tmp->varName}, symbolTable);
		}
	} else {
		int* constPtr = new int(constValue);
		tmp = createTempVar(ctx, "int", constPtr);
		// Load each const if we do not add the optimize option
		if(!cfg.getOptimized()){
			cfg.getCurrentBB()->addInstr(Instr::ldconst, {"$" + to_string(constValue), tmp->varName}, symbolTable);
		}
	}

	// Return the temporary variable
	return tmp;
	
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch variable
	string varName = ctx->TOKENNAME()->getText();

	// Throw error if no corresponding variable has been found
	if (symbolTable->hasVar(varName) == 0 && symbolTable->hasParam(varName) == 0) {
		string message =  "Variable '" + varName + "' has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

	// Mark it as used
	symbolTable->getVar(varName,true)->isUsed = true;

	// Return the variable
	return symbolTable->getVar(varName);
	
}

antlrcpp::Any CodeGenVisitor::visitFuncExpr(ifccParser::FuncExprContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	string funcName = ctx->TOKENNAME()->getText();

	// Check if function is declared 
	if (!globalSymbolTable->hasFunc(funcName)) {
		string message =  "Function '" + funcName + "' has not been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

	funcStruct* func = globalSymbolTable->getFunc(funcName);

	// Check if it's an implicit declaration
	if (func->funcLine > ctx->getStart()->getLine()) {
		string message =  "Function '" + funcName + "' might be declared implicitely";
		errorHandler.signal(WARNING, message, ctx->getStart()->getLine());
	}

	// Check param number
	int numParams = ctx->expr().size();
	bool hasVoid = func->nbParameters < 0;
	if ((func->nbParameters > 0 && numParams != func->nbParameters) || (hasVoid && numParams > 0)) {
		string message =  "Function '" + funcName + "' is called with the wrong number of parameters";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

	// Save current stack pointer
	int currStackPointer = symbolTable->getStackPointer();

	// Iterate through parameters to evaluate and save them
	vector<varStruct*> params;
	for(int i = 0 ; i < numParams ; i++) {
		varStruct* result = visit(ctx->expr(i));
		params.push_back(result);
	}

	// Reset the stack pointer after having evaluated the expression
	symbolTable->setStackPointer(currStackPointer);

	// Write assembly instructions to put the evaluated params into a param register
	for (int i = numParams-1; i >= 0; i--) {
			cfg.getCurrentBB()->addInstr(Instr::wparam, {params[i]->varName, to_string(i)}, symbolTable);
	}

	// Write call instruction
	varStruct* tmp = createTempVar(ctx, func->returnType);
	cfg.getCurrentBB()->addInstr(Instr::call, {funcName, tmp->varName, to_string(numParams)}, symbolTable);
	func->isCalled = true;

	return tmp;

}

antlrcpp::Any CodeGenVisitor::visitVarDeclr(ifccParser::VarDeclrContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Number of variable to declarer
	int numVariable = ctx->TOKENNAME().size();

	// Fetch type
	string dVarType = ctx->vtype()->getText();
	for(int i = 0 ; i < numVariable ; i++) {
		
		// Fetch variable
		string dVarName = ctx->TOKENNAME(i)->getText();

		// Check errors
		if (symbolTable->hasVar(dVarName) == 1) {
			string message =  "Variable '" + dVarName + "' has already been declared";
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
			return 1;
		}
		if (symbolTable->hasParam(dVarName) == 1) {
			string message =  "Variable '" + dVarName + "' is already defined as a parameter of the function";
			errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
			return 1;
		}

		// Add variable to symbol table
		symbolTable->addVar(dVarName, dVarType, ctx->getStart()->getLine());
		cfg.getCurrentBB()->addInstr(Instr::decl, {dVarType,dVarName}, symbolTable);
	}
	return 0;

}

antlrcpp::Any CodeGenVisitor::visitVarDeclrAndAffect(ifccParser::VarDeclrAndAffectContext *ctx) {
	
	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch variable
	string dVarName = ctx->TOKENNAME()->getText();
	string dVarType = ctx->vtype()->getText();

	// Check errors
	if (symbolTable->hasVar(dVarName) == 1) {
		string message =  "Variable '" + dVarName + "' has already been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
        return 1;
	}
	if (symbolTable->hasParam(dVarName) == 1) {
		string message =  "Variable '" + dVarName + "' is already defined as a parameter of the function";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return 1;
	}

	// Add variable to symbol table
	symbolTable->addVar(dVarName, dVarType, ctx->getStart()->getLine());

	// Save current stack pointer
	int currStackPointer = symbolTable->getStackPointer();

	// Compute expression
	varStruct* result = visit(ctx->expr2());

	// Check void errors
	if (result->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable->setStackPointer(currStackPointer);

	// Write assembly instructions
	cfg.getCurrentBB()->addInstr(Instr::aff, {result->varName, dVarName}, symbolTable);
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitExprEnd(ifccParser::ExprEndContext *ctx) {
	SymbolTable* symbolTable = symbolTablesStack.top();
	symbolTable->setReturned(true);

	// Save current stack pointer
	int currStackPointer = symbolTable->getStackPointer();

	// Compute expression
	varStruct* result = visit(ctx->expr2());

	// Check void errors
	if (result->varType == "void") {
		string message =  "Cannot perform operations on void";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return &SymbolTable::dummyVarStruct;
	}

    if (!result->isCorrect) {
		cfg.getCurrentBB()->addInstr(Instr::ret, {}, symbolTable);
        return 1;
    }
	
	// Reset the stack pointer and temp variable counter after having evaluated the expression
	symbolTable->setStackPointer(currStackPointer);

	// Write assembly instructions
	cfg.getCurrentBB()->addInstr(Instr::ret, {result->varName}, symbolTable);

	return 0;
	
}

antlrcpp::Any CodeGenVisitor::visitEmptyEnd(ifccParser::EmptyEndContext *ctx) {

	// Set flag
	SymbolTable* symbolTable = symbolTablesStack.top();
	symbolTable->setReturned(true);

	// Check warnings
	funcStruct* func = globalSymbolTable->getFunc(currFunction);
	if (func->returnType != "void") {
		string message =  "Use of empty 'return;' in non-void function '" + currFunction + "'";
		errorHandler.signal(WARNING, message, ctx->getStart()->getLine());
	}

	// Add actual return instruction
	cfg.getCurrentBB()->addInstr(Instr::ret, {(currFunction == "main") ? "$41" : "$0"}, symbolTable);
	return 0;
}

void CodeGenVisitor::returnDefault(antlr4::ParserRuleContext *ctx) {

	// Set flag
	SymbolTable* symbolTable = symbolTablesStack.top();
	symbolTable->setReturned(true);

	// Check warnings
	funcStruct* func = globalSymbolTable->getFunc(currFunction);
	if (func->returnType != "void") {
		string message =  "No 'return' found in non-void function '" + currFunction + "'";
		errorHandler.signal(WARNING, message, ctx->getStart()->getLine());
	}

	bool return41 = currFunction == "main" && func->returnType == "void";

	// Add actual return instruction
	cfg.getCurrentBB()->addInstr(Instr::ret, {(return41) ? "$41" : "$0"}, symbolTable);
}

antlrcpp::Any CodeGenVisitor::visitMainDeclrHeaderNoRet(ifccParser::MainDeclrHeaderNoRetContext *ctx) { 

	// Create main function in symbol table (grammar makes sure it can only be declared once)
	globalSymbolTable->addFunc("main", "int", 0, {}, {}, ctx->getStart()->getLine());

	// Warning
	string message =  "No return type specified: defaults to 'int'";
	errorHandler.signal(WARNING, message, ctx->getStart()->getLine());

	return 0;

}
antlrcpp::Any CodeGenVisitor::visitMainDeclrHeaderWithRet(ifccParser::MainDeclrHeaderWithRetContext *ctx) {

	// Create main function in symbol table (grammar makes sure it can only be declared once)
	globalSymbolTable->addFunc("main", ctx->FTYPE->getText(), 0, {}, {}, ctx->getStart()->getLine());
	return 0;

}
antlrcpp::Any CodeGenVisitor::visitMainDeclr(ifccParser::MainDeclrContext *ctx) {

	visit(ctx->mainDeclrHeader());
	currFunction = "main";

	// Visit begin (create symbol table) 
	visit(ctx->beginBlock());
	SymbolTable* newSymbolTable = symbolTablesStack.top();

	// Create prologue instructions
	cfg.getCurrentBB()->addInstr(Instr::prologue, {"main"}, newSymbolTable);

	// Create body instructions
	visit(ctx->body());

	// Create default return instruction
    if (!newSymbolTable->hasReturned()) returnDefault(ctx);

	// Visit end (discard symbol table)
	visit(ctx->endBlock());
	
	return 0;

}

antlrcpp::Any CodeGenVisitor::visitFuncDeclrHeader(ifccParser::FuncDeclrContext *ctx) {

	// Fetch function name
	string funcName = ctx->TOKENNAME(0)->getText();

	// Fetch return type
	string returnType = ctx->FTYPE->getText();

	// Fetch parameter names and types
	vector<string> paramTypes = {};
	vector<string> paramNames = {};
	int numParams = ctx->TOKENNAME().size()-1;
	for(int i = 0 ; i < numParams ; i++) {
		string paramName = ctx->TOKENNAME(1+i)->getText();
		string paramType = ctx->vtype(i)->getText();
		paramTypes.push_back(paramType);
		paramNames.push_back(paramName);
	}
	if (ctx->TVOID().size() == 2 && returnType == "void" || ctx->TVOID().size() == 1 && returnType != "void") {
		numParams = -1;
	}

	// Check errors
	if (globalSymbolTable->hasFunc(funcName)) {
		string message =  "Function '" + funcName + "' has already been declared";
		errorHandler.signal(ERROR, message, ctx->getStart()->getLine());
		return 1; 
	}

	// Create function in symbol table (if doesn't exist, otherwise error)
	globalSymbolTable->addFunc(funcName, returnType, numParams, paramTypes, paramNames, ctx->getStart()->getLine());

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitFuncDeclrBody(ifccParser::FuncDeclrContext *ctx) {

	// Visit begin (create symbol table) 
	visit(ctx->beginBlock());
	SymbolTable* newSymbolTable = symbolTablesStack.top();

	// Fetch function name
	string funcName = ctx->TOKENNAME(0)->getText();
	currFunction = funcName;

	// Fetch function from symbol table (has been added when visiting header)
	funcStruct* func = globalSymbolTable->getFunc(funcName);

	// Create param variables in symbol table
	for(int i = 0 ; i < func->nbParameters ; i++) {
		newSymbolTable->addVar("^" + func->parameterNames[i], func->parameterTypes[i], ctx->getStart()->getLine());
	}

	// Create prologue instruction
	cfg.getCurrentBB()->addInstr(Instr::prologue, {funcName}, newSymbolTable); 
	
	// Create instruction that loads register into variable
	int paramStackOffset = 16; // The size of the return adress stored on the stack when calling the function
	for(int i = func->nbParameters-1 ; i >= 0 ; i--) {
		cfg.getCurrentBB()->addInstr(Instr::rparam, {func->parameterNames[i], to_string(i), to_string(paramStackOffset)}, newSymbolTable);
		paramStackOffset += 8;
	}

	// Create body instructions
	visit(ctx->body());

	// Create default return instruction
	if (!newSymbolTable->hasReturned()) returnDefault(ctx);

	// Visit end (discard symbol table)
	visit(ctx->endBlock());

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitFuncDeclr(ifccParser::FuncDeclrContext *ctx) {
	return 0;
}	

antlrcpp::Any CodeGenVisitor::visitBeginBlock(ifccParser::BeginBlockContext *ctx) {
	// Fetch parent symbol table
	SymbolTable* parentSymbolTable = globalSymbolTable;
	int startingStackPointer = 0;
	if (symbolTablesStack.size() > 0) {
		parentSymbolTable = symbolTablesStack.top();
		startingStackPointer = parentSymbolTable->getStackPointer();
	}

	// Create new symbol table
	SymbolTable* newSymbolTable = new SymbolTable(startingStackPointer, parentSymbolTable);
	symbolTablesStack.push(newSymbolTable);

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitEndBlock(ifccParser::EndBlockContext *ctx) {
	
	// Static analysis
	symbolTablesStack.top()->checkUsedVariables(errorHandler);

	SymbolTable* symbolTable = symbolTablesStack.top();
	BasicBlock * currBB = cfg.getCurrentBB();

	if (currBB->getExitFalse()) {
		currBB->addInstr(Instr::conditional_jump, {currBB->getTestVarName(), currBB->getExitFalse()->getLabel(), currBB->getExitTrue()->getLabel()}, symbolTable);
	}
	if (currBB->getExitTrue()){
		currBB->addInstr(Instr::absolute_jump, {currBB->getExitTrue()->getLabel()}, symbolTable);
	}

	// Remove symbol table from stack
	symbolTableGarbage.push(symbolTable);
	symbolTablesStack.pop();

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitVtype(ifccParser::VtypeContext *ctx) {
	return 0;
}

varStruct* CodeGenVisitor::createTempVar(antlr4::ParserRuleContext *ctx, string varType, int* constPtr) {

	SymbolTable* symbolTable = symbolTablesStack.top();
	
	tempVarCounter++;
	string newVar = "!tmp" + to_string(tempVarCounter);
	string newVarType = varType;
	symbolTable->addVar(newVar, newVarType, ctx->getStart()->getLine(), constPtr);
	symbolTable->getVar(newVar)->isUsed = true;

	return symbolTable->getVar(newVar);
}

antlrcpp::Any CodeGenVisitor::visitIfStatement(ifccParser::IfStatementContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	// Fetch boolean expression of the if
	varStruct* testVar = visit(ctx->expr2(0));

	//Check whether there is an else statment
	bool hasElseStatment = ctx->elseStatement(); 

	// Basic block for the test
	BasicBlock* testBB = cfg.getCurrentBB();

	//Stores the name of the boolean test variable within the basic block for the test
	testBB->setTestVarName(testVar->varName);

	// Create an 'then' BB
	BasicBlock* thenBB = cfg.createBB();
		
	// Create a BB for the code following the if/else statement
	BasicBlock* endIfBB = cfg.createBB();
	// Set its exit pointers to the ones of the parent BB
	endIfBB->setExitTrue(testBB->getExitTrue());
	endIfBB->setExitFalse(testBB->getExitFalse());
	
	// Set the parent's true exit pointer to the 'then' BB
	testBB->setExitTrue(thenBB);
	
	// If there's both a 'then' and an 'else' statement,
	if (hasElseStatment) {
		
		// Create an 'else' BB
		BasicBlock* elseBB = cfg.createBB();

		// Set the parent's false exit pointer to it
		testBB->setExitFalse(elseBB);

		// Set the 'else's BB true exit pointer to the following BB
		elseBB->setExitTrue(endIfBB);
		elseBB->setExitFalse(nullptr);
				
		// Write jump instructions
		testBB->addInstr(Instr::conditional_jump, {testBB->getTestVarName(), testBB->getExitFalse()->getLabel(), testBB->getExitTrue()->getLabel()}, symbolTable);
	
		// Visit else body
		cfg.setCurrentBB(elseBB);
		visit(ctx->elseStatement());
	}
	// If there's only a 'then' statement
	else {
		// Set the parent's false exit pointer to the following BB
		testBB->setExitFalse(endIfBB);

		// Write jump instructions
		testBB->addInstr(Instr::conditional_jump, {testBB->getTestVarName(), testBB->getExitFalse()->getLabel(), testBB->getExitTrue()->getLabel()}, symbolTable);
	}

	// Set the 'then's BB true exit pointer to the following BB
	thenBB->setExitTrue(endIfBB);
	thenBB->setExitFalse(nullptr);
	
	// Visit then body or exprssion
	cfg.setCurrentBB(thenBB);
	if (ctx->body()) {
		visit(ctx->beginBlock());
		visit(ctx->body());
		// Write instruction to jump back to the following block
		visit(ctx->endBlock());
	} else if (ctx->expr2(1))
	{
		visit(ctx->expr2(1));
		// Write instruction to jump back to the following block
		thenBB->addInstr(Instr::absolute_jump, {thenBB->getExitTrue()->getLabel()}, symbolTable);
	} else if (ctx->end())
	{
		visit(ctx->end());
		// Write instruction to jump back to the following block
		thenBB->addInstr(Instr::absolute_jump, {thenBB->getExitTrue()->getLabel()}, symbolTable);
	}
	
	// Set the next current BB
	cfg.setCurrentBB(endIfBB);

	return 0;

}

antlrcpp::Any CodeGenVisitor::visitElseStatement(ifccParser::ElseStatementContext *ctx) {
	SymbolTable* symbolTable = symbolTablesStack.top();
	// Basic block for the test
	BasicBlock* elseBB = cfg.getCurrentBB();

	if (ctx->body()) {
		visit(ctx->beginBlock());
		visit(ctx->body());
		// Write instruction to jump back to the following block
		visit(ctx->endBlock());
	} else if (ctx->expr2())
	{
		visit(ctx->expr2());
		// Write instruction to jump back to the following block
		elseBB->addInstr(Instr::absolute_jump, {elseBB->getExitTrue()->getLabel()}, symbolTable);
	}else if (ctx->end())
	{
		visit(ctx->end());
		// Write instruction to jump back to the following block
		elseBB->addInstr(Instr::absolute_jump, {elseBB->getExitTrue()->getLabel()}, symbolTable);
	}

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitWhileStatement(ifccParser::WhileStatementContext *ctx) {

	SymbolTable* symbolTable = symbolTablesStack.top();

	// Basic block before the while expression
	BasicBlock* beforeWhileBB = cfg.getCurrentBB();

	// Create a basic block that will contain the condition
	BasicBlock* testBB = cfg.createBB();
	// Fetch the condition of the while loop
	cfg.setCurrentBB(testBB);
	varStruct* testVar = visit(ctx->expr2(0));
	//Stores the name of the boolean test variable within the basic block for the test
	testBB->setTestVarName(testVar->varName);

	// Create a basic block that will contain the body of the while loop
	BasicBlock* bodyBB = cfg.createBB();
	
	// Create a basic block that will contain the code after the while loop
	BasicBlock* afterWhileBB = cfg.createBB();

	// Set the exit pointers of the afterWhileBB to the ones of the parent BB
	afterWhileBB->setExitTrue(beforeWhileBB->getExitTrue());
	afterWhileBB->setExitFalse(beforeWhileBB->getExitFalse());
	
	// Set beforeWhileBB exit to testBB
	beforeWhileBB->setExitTrue(testBB);
	beforeWhileBB->setExitFalse(nullptr);
	
	// Set the tue exit pointer of the test block to the body block
	testBB->setExitTrue(bodyBB);
	// Set the false exit pointer of the test block to the block after the while
	testBB->setExitFalse(afterWhileBB);

	// Set the true exit pointer of the body block to the test block
	bodyBB->setExitTrue(testBB);
	bodyBB->setExitFalse(nullptr);

	// Visit body of the while loop
	cfg.setCurrentBB(bodyBB);
	if (ctx->body()) {
		visit(ctx->beginBlock());
		visit(ctx->body());
		visit(ctx->endBlock());
	} else if (ctx->expr2(1)) {
		visit(ctx->expr2(1));
	} else if (ctx->end()) {
		visit(ctx->end());
	} 
	

	//if(afterWhileBB->getExitTrue())
	beforeWhileBB->addInstr(Instr::absolute_jump, {beforeWhileBB->getExitTrue()->getLabel()}, symbolTable);
	testBB->addInstr(Instr::conditional_jump, {testBB->getTestVarName(), testBB->getExitFalse()->getLabel(), testBB->getExitTrue()->getLabel()}, symbolTable);
	bodyBB->addInstr(Instr::absolute_jump, {bodyBB->getExitTrue()->getLabel()}, symbolTable);


	// Set the next current BB
	cfg.setCurrentBB(afterWhileBB);

	return 0;

}
antlrcpp::Any CodeGenVisitor::visitPmmdEqual(ifccParser::PmmdEqualContext *ctx) {

    // Fetch constant's info
    varStruct* rExpr = visit(ctx->expr());
    // Fetch variable
    string lExpr = ctx->TOKENNAME()->getText();
    // Get op
    string op = ctx->OPPMMD->getText();

    // Add the instruction to the IR
    SymbolTable* symbolTable = symbolTablesStack.top();

    if (op == "+=") {
        cfg.getCurrentBB()->addInstr(Instr::op_plus_equal, {lExpr, rExpr->varName}, symbolTable);
    } else if (op == "-=") {
        cfg.getCurrentBB()->addInstr(Instr::op_sub_equal, {lExpr, rExpr->varName}, symbolTable);
    } else if (op == "*=") {
        cfg.getCurrentBB()->addInstr(Instr::op_mult_equal, {lExpr, rExpr->varName}, symbolTable);
    } else {
        cfg.getCurrentBB()->addInstr(Instr::op_div_equal, {lExpr, rExpr->varName}, symbolTable);
    }

    return symbolTable->getVar(lExpr);

}

SymbolTable* CodeGenVisitor::getGlobalSymbolTable() {
	return this->globalSymbolTable;
}

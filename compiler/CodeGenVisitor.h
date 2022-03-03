#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "SymbolTable.h"


class  CodeGenVisitor : public ifccBaseVisitor {
	
	public:
		CodeGenVisitor(SymbolTable& sT) : symbolTable(sT) { }
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitBody(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitEnd(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitVarDeclaration(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitConstAffectation(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitVarAffectation(ifccParser::ProgContext *ctx) ;

	protected:
		SymbolTable& symbolTable;

};


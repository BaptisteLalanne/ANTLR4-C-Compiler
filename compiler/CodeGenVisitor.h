#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "SymbolTable.h"

class  CodeGenVisitor : public ifccBaseVisitor {
	
	public:
		CodeGenVisitor(SymbolTable& sT) : symbolTable(sT) { }
		//virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx);
		virtual antlrcpp::Any visitVarDeclr(ifccParser::VarDeclrContext *ctx) ;
		virtual antlrcpp::Any visitVarDeclrConstAffect(ifccParser::VarDeclrConstAffectContext *ctx) ;
		virtual antlrcpp::Any visitVarDeclrVarAffect(ifccParser::VarDeclrVarAffectContext *ctx) ;
		virtual antlrcpp::Any visitConstAffect(ifccParser::ConstAffectContext *ctx) ;
		virtual antlrcpp::Any visitVarAffect(ifccParser::VarAffectContext *ctx) ;
		virtual antlrcpp::Any visitConstEnd(ifccParser::ConstEndContext *ctx) ;
		virtual antlrcpp::Any visitVarEnd(ifccParser::VarEndContext *ctx) ;

	protected:
		SymbolTable& symbolTable;

};


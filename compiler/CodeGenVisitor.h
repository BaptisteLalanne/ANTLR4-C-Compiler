#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


class  CodeGenVisitor : public ifccBaseVisitor {
	public:
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitBody(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitEnd(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitVarDeclaration(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitConstAffectation(ifccParser::ProgContext *ctx) ;
		virtual antlrcpp::Any visitVarAffectation(ifccParser::ProgContext *ctx) ;

};


/*************************************************************************
                          PLD Compiler : CodeGenVisitor
                          ---------------------------
    start   : 02/28/2022
    authors : Bastien B. Laetitia D. Arthur D. Loann L.
			  Baptiste L. Amine L. Tom P. David T.
*************************************************************************/

//------ Interface of class <CodeGenVisitor> (file CodeGenVisitor.h) -------/
#pragma once

//--------------------------------------------------- Called interfaces
#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "SymbolTable.h"
#include "ErrorHandler.h"

//------------------------------------------------------------------------
// Goal of class <CodeGenVisitor>
// The goal of this class is to define the visitors for the different
// syntax element.
//------------------------------------------------------------------------
class  CodeGenVisitor : public ifccBaseVisitor {
	
	public:
		// Constructor of CodeGenVisitor
		CodeGenVisitor(SymbolTable& sT, ErrorHandler& eH) : symbolTable(sT), errorHandler(eH) { }
		virtual antlrcpp::Any visitMainHeader(ifccParser::MainHeaderContext *ctx);
		/*
		virtual antlrcpp::Any visitAddExpr(ifccParser::AddExprContext *ctx) ;
		virtual antlrcpp::Any visitSubExpr(ifccParser::SubExprContext *ctx) ;
		virtual antlrcpp::Any visitMulExpr(ifccParser::MulExprContext *ctx) ;
		virtual antlrcpp::Any visitDivExpr(ifccParser::DivExprContext *ctx) ;
		*/
		virtual antlrcpp::Any visitAddSubExpr(ifccParser::AddSubExprContext *ctx) ;
		virtual antlrcpp::Any visitMulDivExpr(ifccParser::MulDivExprContext *ctx) ;
		virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) ;
		virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) ;
		virtual antlrcpp::Any visitVarDeclr(ifccParser::VarDeclrContext *ctx) ;
		virtual antlrcpp::Any visitVarDeclrAndAffect(ifccParser::VarDeclrAndAffectContext *ctx) ;
		virtual antlrcpp::Any visitAffect(ifccParser::AffectContext *ctx) ;
		virtual antlrcpp::Any visitEnd(ifccParser::EndContext *ctx) ;
		
	protected:
		SymbolTable& symbolTable;
		ErrorHandler& errorHandler;

};


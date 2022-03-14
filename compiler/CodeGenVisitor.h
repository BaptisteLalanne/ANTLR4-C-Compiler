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

		// Default constructor
		CodeGenVisitor(SymbolTable& sT, ErrorHandler& eH) : symbolTable(sT), errorHandler(eH), returned(false), tempVarCounter(0) { }

		// Linearising functions
		virtual antlrcpp::Any visitMainHeader(ifccParser::MainHeaderContext *ctx);
		virtual antlrcpp::Any visitUnaryExpr(ifccParser::UnaryExprContext *ctx) ;
		virtual antlrcpp::Any visitAddSubExpr(ifccParser::AddSubExprContext *ctx) ;
		virtual antlrcpp::Any visitMulDivExpr(ifccParser::MulDivExprContext *ctx) ;
		virtual antlrcpp::Any visitCmpLessOrGreaterExpr(ifccParser::CmpLessOrGreaterExprContext *ctx) ;
		virtual antlrcpp::Any visitCmpEqualityExpr(ifccParser::CmpEqualityExprContext *ctx) ;
		virtual antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) ;
		virtual antlrcpp::Any visitAffExpr(ifccParser::AffExprContext *ctx) ;
		virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) ;
		virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) ;
		virtual antlrcpp::Any visitVarDeclr(ifccParser::VarDeclrContext *ctx) ;
		virtual antlrcpp::Any visitVarDeclrAndAffect(ifccParser::VarDeclrAndAffectContext *ctx) ;
		virtual antlrcpp::Any visitExprEnd(ifccParser::ExprEndContext *ctx) ;
		virtual antlrcpp::Any visitEmptyEnd(ifccParser::EmptyEndContext *ctx) ;
		// virtual antlrcpp::Any visitBwExpr(ifccParser::BwExprContext *ctx) ;
		virtual antlrcpp::Any visitAndExpr(ifccParser::AndExprContext *ctx) ;
		virtual antlrcpp::Any visitXorExpr(ifccParser::XorExprContext *ctx) ;
		virtual antlrcpp::Any visitOrExpr(ifccParser::OrExprContext *ctx) ;

		// Return 0 by default
		void returnDefault();

		// Whether the program has returned or not
		bool hasReturned();
		
		// Return offset temp variable after created it
		varStruct createTempVar(antlr4::ParserRuleContext *ctx);
		
	protected:

		// The associated symbol table instance
		SymbolTable& symbolTable;

		// The associated error handler instance
		ErrorHandler& errorHandler;

		// Whether the function has returned
		bool returned;		

		// A temp variables counter for evaluating expressions
		int tempVarCounter;

};
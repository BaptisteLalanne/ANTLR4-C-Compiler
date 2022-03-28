
// Generated from ifcc.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "ifccParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ifccParser.
 */
class  ifccVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ifccParser.
   */
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *context) = 0;

    virtual antlrcpp::Any visitProg(ifccParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitFuncDeclr(ifccParser::FuncDeclrContext *context) = 0;

    virtual antlrcpp::Any visitFuncHeader(ifccParser::FuncHeaderContext *context) = 0;

    virtual antlrcpp::Any visitMainDeclr(ifccParser::MainDeclrContext *context) = 0;

    virtual antlrcpp::Any visitBody(ifccParser::BodyContext *context) = 0;

    virtual antlrcpp::Any visitFuncExpr(ifccParser::FuncExprContext *context) = 0;

    virtual antlrcpp::Any visitAddSubExpr(ifccParser::AddSubExprContext *context) = 0;

    virtual antlrcpp::Any visitOrExpr(ifccParser::OrExprContext *context) = 0;

    virtual antlrcpp::Any visitMulDivModExpr(ifccParser::MulDivModExprContext *context) = 0;

    virtual antlrcpp::Any visitCmpEqualityExpr(ifccParser::CmpEqualityExprContext *context) = 0;

    virtual antlrcpp::Any visitXorExpr(ifccParser::XorExprContext *context) = 0;

    virtual antlrcpp::Any visitParExpr(ifccParser::ParExprContext *context) = 0;

    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(ifccParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitCmpLessOrGreaterExpr(ifccParser::CmpLessOrGreaterExprContext *context) = 0;

    virtual antlrcpp::Any visitAffExpr(ifccParser::AffExprContext *context) = 0;

    virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *context) = 0;

    virtual antlrcpp::Any visitAndExpr(ifccParser::AndExprContext *context) = 0;

    virtual antlrcpp::Any visitDeclr(ifccParser::DeclrContext *context) = 0;

    virtual antlrcpp::Any visitVarDeclr(ifccParser::VarDeclrContext *context) = 0;

    virtual antlrcpp::Any visitVarDeclrAndAffect(ifccParser::VarDeclrAndAffectContext *context) = 0;

    virtual antlrcpp::Any visitExprEnd(ifccParser::ExprEndContext *context) = 0;

    virtual antlrcpp::Any visitEmptyEnd(ifccParser::EmptyEndContext *context) = 0;


};


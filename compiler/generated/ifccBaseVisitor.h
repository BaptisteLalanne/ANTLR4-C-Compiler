
// Generated from ifcc.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "ifccVisitor.h"


/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ifccBaseVisitor : public ifccVisitor {
public:

  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncDeclr(ifccParser::FuncDeclrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncHeader(ifccParser::FuncHeaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMainDeclr(ifccParser::MainDeclrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBody(ifccParser::BodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncExpr(ifccParser::FuncExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddSubExpr(ifccParser::AddSubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOrExpr(ifccParser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulDivModExpr(ifccParser::MulDivModExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCmpEqualityExpr(ifccParser::CmpEqualityExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitXorExpr(ifccParser::XorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpr(ifccParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCmpLessOrGreaterExpr(ifccParser::CmpLessOrGreaterExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAffExpr(ifccParser::AffExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAndExpr(ifccParser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclr(ifccParser::DeclrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDeclr(ifccParser::VarDeclrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDeclrAndAffect(ifccParser::VarDeclrAndAffectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprEnd(ifccParser::ExprEndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEmptyEnd(ifccParser::EmptyEndContext *ctx) override {
    return visitChildren(ctx);
  }


};


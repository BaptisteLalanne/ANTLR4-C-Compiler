
// Generated from ifcc.g4 by ANTLR 4.9.2


#include "ifccVisitor.h"

#include "ifccParser.h"


using namespace antlrcpp;
using namespace antlr4;

ifccParser::ifccParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ifccParser::~ifccParser() {
  delete _interpreter;
}

std::string ifccParser::getGrammarFileName() const {
  return "ifcc.g4";
}

const std::vector<std::string>& ifccParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ifccParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- AxiomContext ------------------------------------------------------------------

ifccParser::AxiomContext::AxiomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::ProgContext* ifccParser::AxiomContext::prog() {
  return getRuleContext<ifccParser::ProgContext>(0);
}


size_t ifccParser::AxiomContext::getRuleIndex() const {
  return ifccParser::RuleAxiom;
}


antlrcpp::Any ifccParser::AxiomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAxiom(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::AxiomContext* ifccParser::axiom() {
  AxiomContext *_localctx = _tracker.createInstance<AxiomContext>(_ctx, getState());
  enterRule(_localctx, 0, ifccParser::RuleAxiom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(22);
    prog();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgContext ------------------------------------------------------------------

ifccParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::MainDeclrContext* ifccParser::ProgContext::mainDeclr() {
  return getRuleContext<ifccParser::MainDeclrContext>(0);
}

std::vector<ifccParser::FuncDeclrContext *> ifccParser::ProgContext::funcDeclr() {
  return getRuleContexts<ifccParser::FuncDeclrContext>();
}

ifccParser::FuncDeclrContext* ifccParser::ProgContext::funcDeclr(size_t i) {
  return getRuleContext<ifccParser::FuncDeclrContext>(i);
}


size_t ifccParser::ProgContext::getRuleIndex() const {
  return ifccParser::RuleProg;
}


antlrcpp::Any ifccParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ProgContext* ifccParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 2, ifccParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(27);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(24);
        funcDeclr(); 
      }
      setState(29);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
    setState(30);
    mainDeclr();
    setState(34);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ifccParser::T__2

    || _la == ifccParser::T__3) {
      setState(31);
      funcDeclr();
      setState(36);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDeclrContext ------------------------------------------------------------------

ifccParser::FuncDeclrContext::FuncDeclrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::FuncHeaderContext* ifccParser::FuncDeclrContext::funcHeader() {
  return getRuleContext<ifccParser::FuncHeaderContext>(0);
}

ifccParser::BodyContext* ifccParser::FuncDeclrContext::body() {
  return getRuleContext<ifccParser::BodyContext>(0);
}


size_t ifccParser::FuncDeclrContext::getRuleIndex() const {
  return ifccParser::RuleFuncDeclr;
}


antlrcpp::Any ifccParser::FuncDeclrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFuncDeclr(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::FuncDeclrContext* ifccParser::funcDeclr() {
  FuncDeclrContext *_localctx = _tracker.createInstance<FuncDeclrContext>(_ctx, getState());
  enterRule(_localctx, 4, ifccParser::RuleFuncDeclr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    funcHeader();
    setState(38);
    match(ifccParser::T__0);
    setState(39);
    body();
    setState(40);
    match(ifccParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncHeaderContext ------------------------------------------------------------------

ifccParser::FuncHeaderContext::FuncHeaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ifccParser::FuncHeaderContext::TOKENNAME() {
  return getTokens(ifccParser::TOKENNAME);
}

tree::TerminalNode* ifccParser::FuncHeaderContext::TOKENNAME(size_t i) {
  return getToken(ifccParser::TOKENNAME, i);
}


size_t ifccParser::FuncHeaderContext::getRuleIndex() const {
  return ifccParser::RuleFuncHeader;
}


antlrcpp::Any ifccParser::FuncHeaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFuncHeader(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::FuncHeaderContext* ifccParser::funcHeader() {
  FuncHeaderContext *_localctx = _tracker.createInstance<FuncHeaderContext>(_ctx, getState());
  enterRule(_localctx, 6, ifccParser::RuleFuncHeader);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(42);
    dynamic_cast<FuncHeaderContext *>(_localctx)->FTYPE = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == ifccParser::T__2

    || _la == ifccParser::T__3)) {
      dynamic_cast<FuncHeaderContext *>(_localctx)->FTYPE = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(43);
    match(ifccParser::TOKENNAME);
    setState(44);
    match(ifccParser::T__4);
    setState(55);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ifccParser::T__3

    || _la == ifccParser::T__5) {
      setState(45);
      dynamic_cast<FuncHeaderContext *>(_localctx)->VTYPE = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == ifccParser::T__3

      || _la == ifccParser::T__5)) {
        dynamic_cast<FuncHeaderContext *>(_localctx)->VTYPE = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(46);
      match(ifccParser::TOKENNAME);
      setState(52);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ifccParser::T__6) {
        setState(47);
        match(ifccParser::T__6);
        setState(48);
        dynamic_cast<FuncHeaderContext *>(_localctx)->VTYPE = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == ifccParser::T__3

        || _la == ifccParser::T__5)) {
          dynamic_cast<FuncHeaderContext *>(_localctx)->VTYPE = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(49);
        match(ifccParser::TOKENNAME);
        setState(54);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(57);
    match(ifccParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MainDeclrContext ------------------------------------------------------------------

ifccParser::MainDeclrContext::MainDeclrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::BodyContext* ifccParser::MainDeclrContext::body() {
  return getRuleContext<ifccParser::BodyContext>(0);
}


size_t ifccParser::MainDeclrContext::getRuleIndex() const {
  return ifccParser::RuleMainDeclr;
}


antlrcpp::Any ifccParser::MainDeclrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitMainDeclr(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::MainDeclrContext* ifccParser::mainDeclr() {
  MainDeclrContext *_localctx = _tracker.createInstance<MainDeclrContext>(_ctx, getState());
  enterRule(_localctx, 8, ifccParser::RuleMainDeclr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    match(ifccParser::T__3);
    setState(60);
    match(ifccParser::T__8);
    setState(61);
    match(ifccParser::T__4);
    setState(62);
    match(ifccParser::T__7);
    setState(63);
    match(ifccParser::T__0);
    setState(64);
    body();
    setState(65);
    match(ifccParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BodyContext ------------------------------------------------------------------

ifccParser::BodyContext::BodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::DeclrContext* ifccParser::BodyContext::declr() {
  return getRuleContext<ifccParser::DeclrContext>(0);
}

ifccParser::BodyContext* ifccParser::BodyContext::body() {
  return getRuleContext<ifccParser::BodyContext>(0);
}

ifccParser::ExprContext* ifccParser::BodyContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::EndContext* ifccParser::BodyContext::end() {
  return getRuleContext<ifccParser::EndContext>(0);
}


size_t ifccParser::BodyContext::getRuleIndex() const {
  return ifccParser::RuleBody;
}


antlrcpp::Any ifccParser::BodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitBody(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::BodyContext* ifccParser::body() {
  BodyContext *_localctx = _tracker.createInstance<BodyContext>(_ctx, getState());
  enterRule(_localctx, 10, ifccParser::RuleBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(80);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ifccParser::T__3:
      case ifccParser::T__5: {
        enterOuterAlt(_localctx, 1);
        setState(67);
        declr();
        setState(68);
        match(ifccParser::T__9);
        setState(69);
        body();
        break;
      }

      case ifccParser::T__4:
      case ifccParser::T__10:
      case ifccParser::T__11:
      case ifccParser::CONST:
      case ifccParser::TOKENNAME: {
        enterOuterAlt(_localctx, 2);
        setState(71);
        expr(0);
        setState(72);
        match(ifccParser::T__9);
        setState(73);
        body();
        break;
      }

      case ifccParser::RETURN: {
        enterOuterAlt(_localctx, 3);
        setState(75);
        end();
        setState(76);
        match(ifccParser::T__9);
        setState(77);
        body();
        break;
      }

      case ifccParser::T__1: {
        enterOuterAlt(_localctx, 4);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ifccParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ifccParser::ExprContext::getRuleIndex() const {
  return ifccParser::RuleExpr;
}

void ifccParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::FuncExprContext::TOKENNAME() {
  return getToken(ifccParser::TOKENNAME, 0);
}

std::vector<ifccParser::ExprContext *> ifccParser::FuncExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::FuncExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::FuncExprContext::FuncExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::FuncExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFuncExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::AddSubExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::AddSubExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::AddSubExprContext::AddSubExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::AddSubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAddSubExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::OrExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::OrExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::OrExprContext::OrExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::OrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivModExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::MulDivModExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::MulDivModExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::MulDivModExprContext::MulDivModExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::MulDivModExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitMulDivModExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CmpEqualityExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::CmpEqualityExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::CmpEqualityExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::CmpEqualityExprContext::CmpEqualityExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::CmpEqualityExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitCmpEqualityExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- XorExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::XorExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::XorExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::XorExprContext::XorExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::XorExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitXorExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParExprContext ------------------------------------------------------------------

ifccParser::ExprContext* ifccParser::ParExprContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::ParExprContext::ParExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::ParExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitParExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::VarExprContext::TOKENNAME() {
  return getToken(ifccParser::TOKENNAME, 0);
}

ifccParser::VarExprContext::VarExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::VarExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVarExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

ifccParser::ExprContext* ifccParser::UnaryExprContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::UnaryExprContext::UnaryExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CmpLessOrGreaterExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::CmpLessOrGreaterExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::CmpLessOrGreaterExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::CmpLessOrGreaterExprContext::CmpLessOrGreaterExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::CmpLessOrGreaterExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitCmpLessOrGreaterExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AffExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::AffExprContext::TOKENNAME() {
  return getToken(ifccParser::TOKENNAME, 0);
}

ifccParser::ExprContext* ifccParser::AffExprContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::AffExprContext::AffExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::AffExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAffExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::ConstExprContext::CONST() {
  return getToken(ifccParser::CONST, 0);
}

ifccParser::ConstExprContext::ConstExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::ConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitConstExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::AndExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::AndExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::AndExprContext::AndExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ExprContext* ifccParser::expr() {
   return expr(0);
}

ifccParser::ExprContext* ifccParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ifccParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  ifccParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, ifccParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(107);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(83);
      match(ifccParser::T__4);
      setState(84);
      expr(0);
      setState(85);
      match(ifccParser::T__7);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(87);
      dynamic_cast<UnaryExprContext *>(_localctx)->UNARY = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == ifccParser::T__10

      || _la == ifccParser::T__11)) {
        dynamic_cast<UnaryExprContext *>(_localctx)->UNARY = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(88);
      expr(12);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<AffExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(89);
      match(ifccParser::TOKENNAME);
      setState(90);
      match(ifccParser::T__20);
      setState(91);
      expr(7);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<FuncExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(92);
      match(ifccParser::TOKENNAME);
      setState(93);
      match(ifccParser::T__4);
      setState(102);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << ifccParser::T__4)
        | (1ULL << ifccParser::T__10)
        | (1ULL << ifccParser::T__11)
        | (1ULL << ifccParser::CONST)
        | (1ULL << ifccParser::TOKENNAME))) != 0)) {
        setState(94);
        expr(0);
        setState(99);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ifccParser::T__6) {
          setState(95);
          match(ifccParser::T__6);
          setState(96);
          expr(0);
          setState(101);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(104);
      match(ifccParser::T__7);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(105);
      match(ifccParser::CONST);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<VarExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(106);
      match(ifccParser::TOKENNAME);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(132);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(130);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivModExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(109);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(110);
          dynamic_cast<MulDivModExprContext *>(_localctx)->OP1 = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << ifccParser::T__12)
            | (1ULL << ifccParser::T__13)
            | (1ULL << ifccParser::T__14))) != 0))) {
            dynamic_cast<MulDivModExprContext *>(_localctx)->OP1 = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(111);
          expr(12);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(112);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(113);
          dynamic_cast<AddSubExprContext *>(_localctx)->OP2 = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == ifccParser::T__10

          || _la == ifccParser::T__15)) {
            dynamic_cast<AddSubExprContext *>(_localctx)->OP2 = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(114);
          expr(11);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CmpLessOrGreaterExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(115);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(116);
          dynamic_cast<CmpLessOrGreaterExprContext *>(_localctx)->CMP = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == ifccParser::T__16

          || _la == ifccParser::T__17)) {
            dynamic_cast<CmpLessOrGreaterExprContext *>(_localctx)->CMP = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(117);
          expr(10);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<CmpEqualityExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(118);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(119);
          dynamic_cast<CmpEqualityExprContext *>(_localctx)->EQ = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == ifccParser::T__18

          || _la == ifccParser::T__19)) {
            dynamic_cast<CmpEqualityExprContext *>(_localctx)->EQ = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(120);
          expr(9);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(121);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(122);
          match(ifccParser::T__21);
          setState(123);
          expr(7);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<XorExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(124);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(125);
          match(ifccParser::T__22);
          setState(126);
          expr(6);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(127);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(128);
          match(ifccParser::T__23);
          setState(129);
          expr(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(134);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- DeclrContext ------------------------------------------------------------------

ifccParser::DeclrContext::DeclrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::VarDeclrContext* ifccParser::DeclrContext::varDeclr() {
  return getRuleContext<ifccParser::VarDeclrContext>(0);
}

ifccParser::VarDeclrAndAffectContext* ifccParser::DeclrContext::varDeclrAndAffect() {
  return getRuleContext<ifccParser::VarDeclrAndAffectContext>(0);
}


size_t ifccParser::DeclrContext::getRuleIndex() const {
  return ifccParser::RuleDeclr;
}


antlrcpp::Any ifccParser::DeclrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitDeclr(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::DeclrContext* ifccParser::declr() {
  DeclrContext *_localctx = _tracker.createInstance<DeclrContext>(_ctx, getState());
  enterRule(_localctx, 14, ifccParser::RuleDeclr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(137);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(135);
      varDeclr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(136);
      varDeclrAndAffect();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclrContext ------------------------------------------------------------------

ifccParser::VarDeclrContext::VarDeclrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ifccParser::VarDeclrContext::TOKENNAME() {
  return getTokens(ifccParser::TOKENNAME);
}

tree::TerminalNode* ifccParser::VarDeclrContext::TOKENNAME(size_t i) {
  return getToken(ifccParser::TOKENNAME, i);
}


size_t ifccParser::VarDeclrContext::getRuleIndex() const {
  return ifccParser::RuleVarDeclr;
}


antlrcpp::Any ifccParser::VarDeclrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVarDeclr(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VarDeclrContext* ifccParser::varDeclr() {
  VarDeclrContext *_localctx = _tracker.createInstance<VarDeclrContext>(_ctx, getState());
  enterRule(_localctx, 16, ifccParser::RuleVarDeclr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    dynamic_cast<VarDeclrContext *>(_localctx)->VTYPE = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == ifccParser::T__3

    || _la == ifccParser::T__5)) {
      dynamic_cast<VarDeclrContext *>(_localctx)->VTYPE = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(140);
    match(ifccParser::TOKENNAME);
    setState(145);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ifccParser::T__6) {
      setState(141);
      match(ifccParser::T__6);
      setState(142);
      match(ifccParser::TOKENNAME);
      setState(147);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclrAndAffectContext ------------------------------------------------------------------

ifccParser::VarDeclrAndAffectContext::VarDeclrAndAffectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::VarDeclrAndAffectContext::TOKENNAME() {
  return getToken(ifccParser::TOKENNAME, 0);
}

ifccParser::ExprContext* ifccParser::VarDeclrAndAffectContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}


size_t ifccParser::VarDeclrAndAffectContext::getRuleIndex() const {
  return ifccParser::RuleVarDeclrAndAffect;
}


antlrcpp::Any ifccParser::VarDeclrAndAffectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVarDeclrAndAffect(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VarDeclrAndAffectContext* ifccParser::varDeclrAndAffect() {
  VarDeclrAndAffectContext *_localctx = _tracker.createInstance<VarDeclrAndAffectContext>(_ctx, getState());
  enterRule(_localctx, 18, ifccParser::RuleVarDeclrAndAffect);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    dynamic_cast<VarDeclrAndAffectContext *>(_localctx)->VTYPE = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == ifccParser::T__3

    || _la == ifccParser::T__5)) {
      dynamic_cast<VarDeclrAndAffectContext *>(_localctx)->VTYPE = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(149);
    match(ifccParser::TOKENNAME);
    setState(150);
    match(ifccParser::T__20);
    setState(151);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EndContext ------------------------------------------------------------------

ifccParser::EndContext::EndContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ifccParser::EndContext::getRuleIndex() const {
  return ifccParser::RuleEnd;
}

void ifccParser::EndContext::copyFrom(EndContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EmptyEndContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::EmptyEndContext::RETURN() {
  return getToken(ifccParser::RETURN, 0);
}

ifccParser::EmptyEndContext::EmptyEndContext(EndContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::EmptyEndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitEmptyEnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprEndContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::ExprEndContext::RETURN() {
  return getToken(ifccParser::RETURN, 0);
}

ifccParser::ExprContext* ifccParser::ExprEndContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::ExprEndContext::ExprEndContext(EndContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ifccParser::ExprEndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitExprEnd(this);
  else
    return visitor->visitChildren(this);
}
ifccParser::EndContext* ifccParser::end() {
  EndContext *_localctx = _tracker.createInstance<EndContext>(_ctx, getState());
  enterRule(_localctx, 20, ifccParser::RuleEnd);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(156);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<EndContext *>(_tracker.createInstance<ifccParser::ExprEndContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(153);
      match(ifccParser::RETURN);
      setState(154);
      expr(0);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<EndContext *>(_tracker.createInstance<ifccParser::EmptyEndContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(155);
      match(ifccParser::RETURN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool ifccParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 6: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ifccParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 11);
    case 1: return precpred(_ctx, 10);
    case 2: return precpred(_ctx, 9);
    case 3: return precpred(_ctx, 8);
    case 4: return precpred(_ctx, 6);
    case 5: return precpred(_ctx, 5);
    case 6: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ifccParser::_decisionToDFA;
atn::PredictionContextCache ifccParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ifccParser::_atn;
std::vector<uint16_t> ifccParser::_serializedATN;

std::vector<std::string> ifccParser::_ruleNames = {
  "axiom", "prog", "funcDeclr", "funcHeader", "mainDeclr", "body", "expr", 
  "declr", "varDeclr", "varDeclrAndAffect", "end"
};

std::vector<std::string> ifccParser::_literalNames = {
  "", "'{'", "'}'", "'void'", "'int'", "'('", "'char'", "','", "')'", "'main'", 
  "';'", "'-'", "'!'", "'*'", "'/'", "'%'", "'+'", "'<'", "'>'", "'=='", 
  "'!='", "'='", "'&'", "'^'", "'|'", "", "'return'"
};

std::vector<std::string> ifccParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "WS", "RETURN", "CONST", "NUMBER", "CHAR", 
  "TOKENNAME", "MULTICOMMENT", "SINGLECOMMENT", "DIRECTIVE"
};

dfa::Vocabulary ifccParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ifccParser::_tokenNames;

ifccParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x23, 0xa1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x3, 0x2, 0x3, 
       0x3, 0x7, 0x3, 0x1c, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x1f, 0xb, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x23, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 
       0x26, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x7, 0x5, 0x35, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x38, 
       0xb, 0x5, 0x5, 0x5, 0x3a, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 
       0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
       0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x5, 0x7, 0x53, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
       0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x64, 
       0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x67, 0xb, 0x8, 0x5, 0x8, 0x69, 0xa, 
       0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x6e, 0xa, 0x8, 0x3, 
       0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
       0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x8, 0x7, 0x8, 0x85, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x88, 0xb, 
       0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x8c, 0xa, 0x9, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x92, 0xa, 0xa, 0xc, 0xa, 0xe, 
       0xa, 0x95, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
       0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x9f, 0xa, 0xc, 0x3, 
       0xc, 0x2, 0x3, 0xe, 0xd, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 
       0x12, 0x14, 0x16, 0x2, 0x9, 0x3, 0x2, 0x5, 0x6, 0x4, 0x2, 0x6, 0x6, 
       0x8, 0x8, 0x3, 0x2, 0xd, 0xe, 0x3, 0x2, 0xf, 0x11, 0x4, 0x2, 0xd, 
       0xd, 0x12, 0x12, 0x3, 0x2, 0x13, 0x14, 0x3, 0x2, 0x15, 0x16, 0x2, 
       0xad, 0x2, 0x18, 0x3, 0x2, 0x2, 0x2, 0x4, 0x1d, 0x3, 0x2, 0x2, 0x2, 
       0x6, 0x27, 0x3, 0x2, 0x2, 0x2, 0x8, 0x2c, 0x3, 0x2, 0x2, 0x2, 0xa, 
       0x3d, 0x3, 0x2, 0x2, 0x2, 0xc, 0x52, 0x3, 0x2, 0x2, 0x2, 0xe, 0x6d, 
       0x3, 0x2, 0x2, 0x2, 0x10, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x12, 0x8d, 0x3, 
       0x2, 0x2, 0x2, 0x14, 0x96, 0x3, 0x2, 0x2, 0x2, 0x16, 0x9e, 0x3, 0x2, 
       0x2, 0x2, 0x18, 0x19, 0x5, 0x4, 0x3, 0x2, 0x19, 0x3, 0x3, 0x2, 0x2, 
       0x2, 0x1a, 0x1c, 0x5, 0x6, 0x4, 0x2, 0x1b, 0x1a, 0x3, 0x2, 0x2, 0x2, 
       0x1c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1d, 
       0x1e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x20, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x1d, 
       0x3, 0x2, 0x2, 0x2, 0x20, 0x24, 0x5, 0xa, 0x6, 0x2, 0x21, 0x23, 0x5, 
       0x6, 0x4, 0x2, 0x22, 0x21, 0x3, 0x2, 0x2, 0x2, 0x23, 0x26, 0x3, 0x2, 
       0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 
       0x2, 0x25, 0x5, 0x3, 0x2, 0x2, 0x2, 0x26, 0x24, 0x3, 0x2, 0x2, 0x2, 
       0x27, 0x28, 0x5, 0x8, 0x5, 0x2, 0x28, 0x29, 0x7, 0x3, 0x2, 0x2, 0x29, 
       0x2a, 0x5, 0xc, 0x7, 0x2, 0x2a, 0x2b, 0x7, 0x4, 0x2, 0x2, 0x2b, 0x7, 
       0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x9, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x7, 
       0x20, 0x2, 0x2, 0x2e, 0x39, 0x7, 0x7, 0x2, 0x2, 0x2f, 0x30, 0x9, 
       0x3, 0x2, 0x2, 0x30, 0x36, 0x7, 0x20, 0x2, 0x2, 0x31, 0x32, 0x7, 
       0x9, 0x2, 0x2, 0x32, 0x33, 0x9, 0x3, 0x2, 0x2, 0x33, 0x35, 0x7, 0x20, 
       0x2, 0x2, 0x34, 0x31, 0x3, 0x2, 0x2, 0x2, 0x35, 0x38, 0x3, 0x2, 0x2, 
       0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 0x2, 0x2, 
       0x37, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x38, 0x36, 0x3, 0x2, 0x2, 0x2, 0x39, 
       0x2f, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 
       0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 0x7, 0xa, 0x2, 0x2, 0x3c, 0x9, 0x3, 
       0x2, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x6, 0x2, 0x2, 0x3e, 0x3f, 0x7, 0xb, 
       0x2, 0x2, 0x3f, 0x40, 0x7, 0x7, 0x2, 0x2, 0x40, 0x41, 0x7, 0xa, 0x2, 
       0x2, 0x41, 0x42, 0x7, 0x3, 0x2, 0x2, 0x42, 0x43, 0x5, 0xc, 0x7, 0x2, 
       0x43, 0x44, 0x7, 0x4, 0x2, 0x2, 0x44, 0xb, 0x3, 0x2, 0x2, 0x2, 0x45, 
       0x46, 0x5, 0x10, 0x9, 0x2, 0x46, 0x47, 0x7, 0xc, 0x2, 0x2, 0x47, 
       0x48, 0x5, 0xc, 0x7, 0x2, 0x48, 0x53, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 
       0x5, 0xe, 0x8, 0x2, 0x4a, 0x4b, 0x7, 0xc, 0x2, 0x2, 0x4b, 0x4c, 0x5, 
       0xc, 0x7, 0x2, 0x4c, 0x53, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x5, 0x16, 
       0xc, 0x2, 0x4e, 0x4f, 0x7, 0xc, 0x2, 0x2, 0x4f, 0x50, 0x5, 0xc, 0x7, 
       0x2, 0x50, 0x53, 0x3, 0x2, 0x2, 0x2, 0x51, 0x53, 0x3, 0x2, 0x2, 0x2, 
       0x52, 0x45, 0x3, 0x2, 0x2, 0x2, 0x52, 0x49, 0x3, 0x2, 0x2, 0x2, 0x52, 
       0x4d, 0x3, 0x2, 0x2, 0x2, 0x52, 0x51, 0x3, 0x2, 0x2, 0x2, 0x53, 0xd, 
       0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x8, 0x8, 0x1, 0x2, 0x55, 0x56, 0x7, 
       0x7, 0x2, 0x2, 0x56, 0x57, 0x5, 0xe, 0x8, 0x2, 0x57, 0x58, 0x7, 0xa, 
       0x2, 0x2, 0x58, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x9, 0x4, 0x2, 
       0x2, 0x5a, 0x6e, 0x5, 0xe, 0x8, 0xe, 0x5b, 0x5c, 0x7, 0x20, 0x2, 
       0x2, 0x5c, 0x5d, 0x7, 0x17, 0x2, 0x2, 0x5d, 0x6e, 0x5, 0xe, 0x8, 
       0x9, 0x5e, 0x5f, 0x7, 0x20, 0x2, 0x2, 0x5f, 0x68, 0x7, 0x7, 0x2, 
       0x2, 0x60, 0x65, 0x5, 0xe, 0x8, 0x2, 0x61, 0x62, 0x7, 0x9, 0x2, 0x2, 
       0x62, 0x64, 0x5, 0xe, 0x8, 0x2, 0x63, 0x61, 0x3, 0x2, 0x2, 0x2, 0x64, 
       0x67, 0x3, 0x2, 0x2, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 
       0x3, 0x2, 0x2, 0x2, 0x66, 0x69, 0x3, 0x2, 0x2, 0x2, 0x67, 0x65, 0x3, 
       0x2, 0x2, 0x2, 0x68, 0x60, 0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 0x3, 0x2, 
       0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6e, 0x7, 0xa, 0x2, 
       0x2, 0x6b, 0x6e, 0x7, 0x1d, 0x2, 0x2, 0x6c, 0x6e, 0x7, 0x20, 0x2, 
       0x2, 0x6d, 0x54, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x59, 0x3, 0x2, 0x2, 0x2, 
       0x6d, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x6d, 
       0x6b, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x86, 
       0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0xc, 0xd, 0x2, 0x2, 0x70, 0x71, 0x9, 
       0x5, 0x2, 0x2, 0x71, 0x85, 0x5, 0xe, 0x8, 0xe, 0x72, 0x73, 0xc, 0xc, 
       0x2, 0x2, 0x73, 0x74, 0x9, 0x6, 0x2, 0x2, 0x74, 0x85, 0x5, 0xe, 0x8, 
       0xd, 0x75, 0x76, 0xc, 0xb, 0x2, 0x2, 0x76, 0x77, 0x9, 0x7, 0x2, 0x2, 
       0x77, 0x85, 0x5, 0xe, 0x8, 0xc, 0x78, 0x79, 0xc, 0xa, 0x2, 0x2, 0x79, 
       0x7a, 0x9, 0x8, 0x2, 0x2, 0x7a, 0x85, 0x5, 0xe, 0x8, 0xb, 0x7b, 0x7c, 
       0xc, 0x8, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x18, 0x2, 0x2, 0x7d, 0x85, 
       0x5, 0xe, 0x8, 0x9, 0x7e, 0x7f, 0xc, 0x7, 0x2, 0x2, 0x7f, 0x80, 0x7, 
       0x19, 0x2, 0x2, 0x80, 0x85, 0x5, 0xe, 0x8, 0x8, 0x81, 0x82, 0xc, 
       0x6, 0x2, 0x2, 0x82, 0x83, 0x7, 0x1a, 0x2, 0x2, 0x83, 0x85, 0x5, 
       0xe, 0x8, 0x7, 0x84, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x84, 0x72, 0x3, 0x2, 
       0x2, 0x2, 0x84, 0x75, 0x3, 0x2, 0x2, 0x2, 0x84, 0x78, 0x3, 0x2, 0x2, 
       0x2, 0x84, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x84, 0x7e, 0x3, 0x2, 0x2, 0x2, 
       0x84, 0x81, 0x3, 0x2, 0x2, 0x2, 0x85, 0x88, 0x3, 0x2, 0x2, 0x2, 0x86, 
       0x84, 0x3, 0x2, 0x2, 0x2, 0x86, 0x87, 0x3, 0x2, 0x2, 0x2, 0x87, 0xf, 
       0x3, 0x2, 0x2, 0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8c, 0x5, 
       0x12, 0xa, 0x2, 0x8a, 0x8c, 0x5, 0x14, 0xb, 0x2, 0x8b, 0x89, 0x3, 
       0x2, 0x2, 0x2, 0x8b, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x11, 0x3, 0x2, 
       0x2, 0x2, 0x8d, 0x8e, 0x9, 0x3, 0x2, 0x2, 0x8e, 0x93, 0x7, 0x20, 
       0x2, 0x2, 0x8f, 0x90, 0x7, 0x9, 0x2, 0x2, 0x90, 0x92, 0x7, 0x20, 
       0x2, 0x2, 0x91, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x92, 0x95, 0x3, 0x2, 0x2, 
       0x2, 0x93, 0x91, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x3, 0x2, 0x2, 0x2, 
       0x94, 0x13, 0x3, 0x2, 0x2, 0x2, 0x95, 0x93, 0x3, 0x2, 0x2, 0x2, 0x96, 
       0x97, 0x9, 0x3, 0x2, 0x2, 0x97, 0x98, 0x7, 0x20, 0x2, 0x2, 0x98, 
       0x99, 0x7, 0x17, 0x2, 0x2, 0x99, 0x9a, 0x5, 0xe, 0x8, 0x2, 0x9a, 
       0x15, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x7, 0x1c, 0x2, 0x2, 0x9c, 
       0x9f, 0x5, 0xe, 0x8, 0x2, 0x9d, 0x9f, 0x7, 0x1c, 0x2, 0x2, 0x9e, 
       0x9b, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x17, 
       0x3, 0x2, 0x2, 0x2, 0xf, 0x1d, 0x24, 0x36, 0x39, 0x52, 0x65, 0x68, 
       0x6d, 0x84, 0x86, 0x8b, 0x93, 0x9e, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ifccParser::Initializer ifccParser::_init;

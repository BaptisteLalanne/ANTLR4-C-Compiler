grammar ifcc;

axiom : prog ;

prog : 
	mainHeader '{' body '}'
;
mainHeader :
	'int' 'main' '(' ')'
;
body : 
	| declr ';' body 
	| expr ';' body
	| end ';' body
	| 
;

expr :
	'(' expr ')' 		#parExpr
	| UNARY expr 		#unaryExpr	
	| expr OP1 expr 	#mulDivModExpr	
	| expr OP2 expr 	#addSubExpr
	| expr CMP expr		#cmpLessOrGreaterExpr
	| expr EQ expr		#cmpEqualityExpr
	| VAR '=' expr 		#affExpr
	| expr '&' expr		#andExpr
	| expr '^' expr		#xorExpr
	| expr '|' expr		#orExpr
	| CONST 			#constExpr 
	| VAR				#varExpr
;

declr :
	varDeclr 
	| varDeclrAndAffect
;
varDeclr : 
	TYPE VAR (',' VAR)*
;
varDeclrAndAffect :
	TYPE VAR '=' expr 
;

end :
	RETURN expr			#exprEnd	
	| RETURN 			#emptyEnd
;

UNARY : '!' ;
OP1 : ('*'|'/'|'%') ;
OP2 : ('+'|'-') ;
CMP : ('<' | '>') ;
EQ : ('=='|'!=') ;
WS : [ \t\r\n] -> channel(HIDDEN) ;
RETURN : 'return' ;
TYPE : 'int' ;
CONST : [0-9]+ ;
VAR : [a-zA-Z_][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
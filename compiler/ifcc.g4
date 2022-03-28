grammar ifcc;

axiom : prog ;

prog :
	(funcDeclr)* mainDeclr (funcDeclr)*
;

funcDeclr :
	funcHeader '{' body '}'
;
funcHeader :
	FTYPE=('void'|'int') TOKENNAME '(' (VTYPE TOKENNAME (',' VTYPE TOKENNAME)*)? ')' 
;

mainDeclr : 
	'int' 'main' '(' ')' '{' body '}'
;

body : 
	declr ';' body 
	| end ';' body
	| ifelse body
	| expr ';' body
	|
;

expr :
	'(' expr ')' 								#parExpr
	| UNARY=('-'|'!') expr 		   				#unaryExpr	
	| expr OP1=('*'|'/'|'%') expr 				#mulDivModExpr	
	| expr OP2=('+'|'-') expr 					#addSubExpr
	| expr CMP=('<' | '>') expr					#cmpLessOrGreaterExpr
	| expr EQ=('=='|'!=') expr					#cmpEqualityExpr
	| expr '&' expr								#andExpr
	| expr '^' expr								#xorExpr
	| expr '|' expr								#orExpr
	| TOKENNAME '(' (expr (',' expr)*)? ')'		#funcExpr
	| CONST 									#constExpr 
	| TOKENNAME									#varExpr
	| TOKENNAME '=' expr 						#affExpr
;

ifelse :
	'if' '(' expr ')' '{' body '}' ('else' '{' body '}')?	#ifStatement
;

declr :
	varDeclr 
	| varDeclrAndAffect
;

varDeclr : 
	VTYPE TOKENNAME (',' TOKENNAME)*
;
varDeclrAndAffect :
	VTYPE TOKENNAME '=' expr 
;

end :
	RETURN expr									#exprEnd	
	| RETURN 									#emptyEnd
;

WS : [ \t\r\n] -> channel(HIDDEN) ;
RETURN : 'return' ;
VTYPE : 'int' ;
CONST : NUMBER | CHAR ;
NUMBER : [0-9]+ ;
CHAR : '\'' . '\'' ;
TOKENNAME : [a-zA-Z_][a-zA-Z0-9_]* ;
MULTICOMMENT : '/*' .*? '*/' -> skip ;
SINGLECOMMENT : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
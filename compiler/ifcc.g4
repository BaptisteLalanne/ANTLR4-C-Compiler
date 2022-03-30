grammar ifcc;

vtype:
	TINT
	| TCHAR
;

axiom : prog ;

beginBlock : '{' ;
endBlock : '}' ;

prog :
	(funcDeclr)* mainDeclr (funcDeclr)*
;

funcDeclr :
	FTYPE=('void'|'int') TOKENNAME '(' (vtype TOKENNAME (',' vtype TOKENNAME)*)? ')' beginBlock body endBlock
;

mainDeclr : 
	'int' 'main' '(' ')' beginBlock body endBlock
;

body : 
	declr ';' body 
	| end ';' body
	| ifelse body
	| expr ';' body
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
	vtype TOKENNAME (',' TOKENNAME)*
;
varDeclrAndAffect :
	vtype TOKENNAME '=' expr 
;

end :
	RETURN expr									#exprEnd	
	| RETURN 									#emptyEnd
;

WS : [ \t\r\n] -> channel(HIDDEN) ;
RETURN : 'return' ;
CONST : NUMBER | CHAR ;
NUMBER : [0-9]+ ;
CHAR : '\'' . '\'' ;
TINT : 'int' ;
TCHAR : 'char' ;
TOKENNAME : [a-zA-Z_][a-zA-Z0-9_]* ;
MULTICOMMENT : '/*' .*? '*/' -> skip ;
SINGLECOMMENT : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
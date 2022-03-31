
grammar ifcc;

axiom : prog ;

vtype:
	TINT
	| TCHAR
;

beginBlock : '{' ;
endBlock : '}' ;

prog :
	(funcDeclr)* mainDeclr (funcDeclr)*
;

funcDeclr :
	FTYPE=('void'|'int'|'char') TOKENNAME '(' (vtype TOKENNAME (',' vtype TOKENNAME)*)? ')' beginBlock body endBlock
;

mainDeclr : 
	'int' 'main' '(' ')' beginBlock body endBlock
;

body : 
	declr ';' body 
	| expr ';' body
	| end ';' body
	| ifelse body
	| whileStatement body
	| beginBlock body endBlock body
	|
;

expr :
	'(' expr ')' 								#parExpr
	| UNARY=('-'|'!') expr 		   				#unaryExpr	
	| expr OP1=('*'|'/'|'%') expr 				#mulDivModExpr	
	| expr OP2=('+'|'-') expr 					#addSubExpr
	| expr CMP=('<' | '>') expr					#cmpLessOrGreaterExpr
	| expr EQ=('=='|'!=') expr					#cmpEqualityExpr
	| TOKENNAME '=' expr 						#affExpr
	| expr '&' expr								#andExpr
	| expr '^' expr								#xorExpr
	| expr '|' expr								#orExpr
	| TOKENNAME '(' (expr (',' expr)*)? ')'		#funcExpr
	| CONST 									#constExpr 
	| TOKENNAME									#varExpr
;

ifelse :
	'if' '(' expr ')' beginBlock body endBlock ('else' beginBlock body endBlock)?	#ifStatement
;

whileStatement :
	'while' '(' expr ')' beginBlock body endBlock
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
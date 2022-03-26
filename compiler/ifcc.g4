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
funcCall :
	TOKENNAME '(' (expr (',' expr)*)? ')'
;

mainDeclr : 
	'int' 'main' '(' ')' '{' body '}'
;

body : 
	declr ';' body 
	| expr ';' body
	| end ';' body
	| 
;

expr :
	'(' expr ')' 						#parExpr
	| UNARY=('-'|'!') expr 		   		#unaryExpr	
	| expr OP1=('*'|'/'|'%') expr 		#mulDivModExpr	
	| expr OP2=('+'|'-') expr 			#addSubExpr
	| expr CMP=('<' | '>') expr			#cmpLessOrGreaterExpr
	| expr EQ=('=='|'!=') expr			#cmpEqualityExpr
	| TOKENNAME '=' expr 				#affExpr
	| expr '&' expr						#andExpr
	| expr '^' expr						#xorExpr
	| expr '|' expr						#orExpr
	| funcCall							#funcExpr
	| CONST 							#constExpr 
	| TOKENNAME							#varExpr
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
	RETURN expr							#exprEnd	
	| RETURN 							#emptyEnd
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
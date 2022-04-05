
grammar ifcc;

axiom : prog EOF;

vtype: TINT | TCHAR ;
beginBlock : '{' ;
endBlock : '}' ;

prog :
	(funcDeclr)* mainDeclr (funcDeclr)*
;

funcDeclr :
	FTYPE=('void'|'int'|'char') TOKENNAME '(' ( (vtype TOKENNAME (',' vtype TOKENNAME)*)? | (TVOID)? ) ')' beginBlock body endBlock (';')?
;

mainDeclrHeader:
	FTYPE=('void'|'int') 'main' '(' (TVOID)? ')' 		 		#mainDeclrHeaderWithRet
	| 'main' '(' (TVOID)? ')' 									#mainDeclrHeaderNoRet
;

mainDeclr : 
	mainDeclrHeader beginBlock body endBlock (';')?
;

body : 
	declr ';' body 
	| expr2 ';' body
	| end ';' body
	| ifStatement body
	| whileStatement body
	| beginBlock body endBlock (';')? body
	|
;

expr2 :
    affect
    | expr
;

expr :
	'(' expr2 ')' 										#parExpr
	| UNARY=('-'|'!') expr 		   						#unaryExpr
	| expr OP1=('*'|'/'|'%') expr 						#mulDivModExpr	
	| expr OP2=('+'|'-') expr 							#addSubExpr
	| expr CMP=('<' | '>') expr							#cmpLessOrGreaterExpr
	| expr EQ=('=='|'!=') expr							#cmpEqualityExpr
	| expr EQLG=('<='|'>=') expr						#cmpEqualityLessGreaterExpr
	| expr '&' expr										#andExpr
	| expr '^' expr										#xorExpr
	| expr '|' expr										#orExpr
	| TOKENNAME '(' (expr (',' expr)*)? ')'				#funcExpr
	| CONST 											#constExpr 
	| TOKENNAME											#varExpr
;

affect :
    TOKENNAME '=' expr2									#affExpr
    | TOKENNAME OPPMMD=('+='|'-='|'*='|'/=') expr      	#pmmdEqual
;

ifStatement :
	'if' '(' expr2 ')' beginBlock body endBlock (elseStatement)?
	| 'if' '(' expr2 ')' expr2 ';' (elseStatement)?
;

elseStatement :
	'else' beginBlock body endBlock
	|'else' expr2 ';'
;

whileStatement :
	'while' '(' expr2 ')' beginBlock body endBlock
;

declr :
	varDeclr 
	| varDeclrAndAffect
;
varDeclr : 
	vtype TOKENNAME (',' TOKENNAME)*
;
varDeclrAndAffect :
	vtype TOKENNAME '=' expr2
;

end :
	RETURN expr2										#exprEnd
	| RETURN 											#emptyEnd
;

WS : [ \t\r\n] -> channel(HIDDEN) ;
RETURN : 'return' ;
CONST : NUMBER | CHAR ;
NUMBER : [0-9]+ ;
CHAR : '\'' . '\'' ;
TINT : 'int' ;
TCHAR : 'char' ;
TVOID: 'void' ;
TOKENNAME : [a-zA-Z_][a-zA-Z0-9_]* ;
MULTICOMMENT : '/*' .*? '*/' -> skip ;
SINGLECOMMENT : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
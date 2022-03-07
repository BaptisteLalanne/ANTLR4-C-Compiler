grammar ifcc;

axiom : prog ;

prog : 
	mainHeader '{' body end '}'
;
mainHeader :
	'int' 'main' '(' ')'
;
body : 
	varDeclr body 
	| varDeclrAndAffect body 
	| affect body 
	| 
;

expr :
	expr '+' expr 		#addExpr	
	| expr '-' expr 	#subExpr
	| expr '*' expr		#mulExpr 
	| expr '/' expr 	#divExpr 
	| '(' expr ')' 		#parExpr
	| CONST 			#constExpr 
	| VAR				#varExpr
;

varDeclr : 
	TYPE VAR ';' 
;
varDeclrAndAffect :
	TYPE VAR '=' expr ';'
;

affect :
	VAR '=' expr ';'
;

end :
	RETURN expr ';' 
;

WS : [ \t\r\n] -> channel(HIDDEN);
RETURN : 'return' ;
TYPE : 'int';
CONST : [0-9]+ ;
VAR : [a-zA-Z_][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
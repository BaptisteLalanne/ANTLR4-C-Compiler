grammar ifcc;

axiom : prog ;

prog : 
	mainHeader '{' body end '}'
;
mainHeader :
	'int' 'main' '(' ')'
;
body : 
	varDeclr body | 
	varDeclrConstAffect body | 
	varDeclrVarAffect body | 
	constAffect body | 
	varAffect body | 
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
varDeclrConstAffect : 
	TYPE VAR '=' CONST ';' 
;
varDeclrVarAffect : 
	TYPE VAR '=' VAR ';' 
;
varDeclrExprAffect :
	TYPE VAR '=' expr ';'
;

constAffect :
	VAR '=' CONST ';' 
;
varAffect : 
	VAR '=' VAR ';' 
;
exprAffect :
	VAR '=' expr ';'
;

end :
	constEnd | varEnd 
;
constEnd : 
	RETURN CONST ';' 
;
varEnd :
	RETURN VAR ';' 
;

WS : [ \t\r\n] -> channel(HIDDEN);
RETURN : 'return' ;
TYPE : 'int';
CONST : [0-9]+ ;
VAR : [a-zA-Z_][a-zA-Z0-9_]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;

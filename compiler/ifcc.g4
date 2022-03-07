grammar ifcc;

axiom : prog ;

prog : 
	'int' 'main' '(' ')' '{' body end '}' 
;
body : 
	varDeclr body | 
	varDeclrConstAffect body | 
	varDeclrVarAffect body | 
	constAffect body | 
	varAffect body | 
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
constAffect :
	VAR '=' CONST ';' 
;
varAffect : 
	VAR '=' VAR ';' 
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

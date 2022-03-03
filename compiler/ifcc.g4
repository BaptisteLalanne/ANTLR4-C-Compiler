grammar ifcc;

axiom : prog ;

prog : 
	'int' 'main' '(' ')' OPENBRACKET body end CLOSEDBRACKET 
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
	RETURN (VAR|CONST) ';' 
;

RETURN : 'return' ;
TYPE : 'int';
CONST : [0-9]+ ;
VAR : [a-zA-Z_][a-zA-Z0-9_]* ;
OPENBRACKET : ('\n'|) '{' ('\n'|) ;
CLOSEDBRACKET : ('\n'|) '}' ('\n'|) ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS : [ \t\r\n] -> channel(HIDDEN);

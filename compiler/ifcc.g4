grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' OPENBRACKET body end CLOSEDBRACKET ;
body : varDeclaration body | constAffectation body | varAffectation body | ;
varDeclaration : TYPE VAR '=' CONST ';' ;
constAffectation : VAR '=' CONST ';' ;
varAffectation : VAR '=' VAR ';' ;
end : RETURN expr ';' ;
expr : VAR | CONST ;

RETURN : 'return' ;
TYPE : 'int';
CONST : [0-9]+ ;
VAR : [a-zA-Z_][a-zA-Z0-9_]* ;
OPENBRACKET : ('\n'|) '{' ('\n'|) ;
CLOSEDBRACKET : ('\n'|) '}' ('\n'|) ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS : [ \t\r\n] -> channel(HIDDEN);

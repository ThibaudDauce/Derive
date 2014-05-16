%{
/*
** Derive
** Thibaud Dauce | http://git.thibaud-dauce.fr/thibaud/derive.git
** Base sur l'exemple de Hugues Cassé
** http://www.irit.fr/ACTIVITES/EQ_HECTOR/casse/alcatel/
*/

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "libExpressionMathematique.h"
#include "y.tab.h"
char* dupliquerChaine(char *);
%}

ENT		[0-9]+
VIRG	\.{ENT}
VARIA	[a-zA-Z]
NBRE	{ENT}|{ENT}{VIRG}
%%
[ \t]			;
"exit"			return EXIT;
"cos"			return OP_COS;
"sin"			return OP_SIN;
"tan"			return OP_TAN;
"exp"			return OP_EXP;
"log"			return OP_LOG;
{VARIA}			{yylval.ch = dupliquerChaine(yytext); return VAR;}
{NBRE}			{yylval.val = atof(yytext); return NB;}
[+] 	        return OP_ADD;
[-] 	        return OP_SOUS;
[*] 	        return OP_MUL;
[/] 	        return OP_DIV;
[\^] 	        return OP_POW;
[(] 	        return PAR_G;
[)] 	        return PAR_D;
[,] 	        return VIRGULE;
[\n]            return FIN;
%%

char* dupliquerChaine(char *chaine) {
  char* nouvelleChaine = malloc(strlen(chaine)+1);
  strcpy(nouvelleChaine, chaine);
  return nouvelleChaine;
}

int yywrap(void){
  return 1;
}


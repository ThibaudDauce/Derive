%{
/*
** Base sur l'exemple de Hugues Cassé
** http://www.irit.fr/ACTIVITES/EQ_HECTOR/casse/alcatel/
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "libExpressionMathematique.h"

#define AFFICHER 0
#define QUITTER 1
%}

%union {float val;char *ch;EM_ExpressionMathematique expr;}	// Definit le type de yylval (nomme
				// YYSTYPE)
//Definition des lexemes
%token <val> NB		// Indique le champ de YYSTYPE qui doit etre utilise dans
%token <ch> VAR		// l'interpretation des regles de la grammaire
%token EXIT
%token VIRGULE
%token PAR_G PAR_D
%token FIN
%token OP_SIN OP_COS OP_TAN OP_EXP OP_LOG
%token OP_ADD OP_SOUS OP_DIV OP_MUL OP_POW
// Definition l'ordre des priorites ainsi que l'associativite   	  
%left OP_ADD OP_SOUS
%left OP_POW
%left OP_MUL OP_DIV
%left OP_EXP OP_LOG
%left OP_SIN OP_COS OP_TAN
// Designation du champ de YYSTYPE utilise pour les non terminaux
%type <expr> fonction
// les parametres de yyparse
%parse-param {EM_ExpressionMathematique* pResultat}
%parse-param {char** pVariable}
%parse-param {int* pCommande}

%%
commande: ligne FIN {YYACCEPT;}
	;


ligne:	fonction VIRGULE VAR {*pResultat = $1; *pVariable = $3; *pCommande = AFFICHER;}
	|EXIT	{*pCommande = QUITTER;}
	;

fonction:	VAR	{$$ = EM_creerAPartirDUneVariable($1);}
	|NB	{$$ = EM_creerAPartirDUnNombre($1);}
	|PAR_G fonction PAR_D	{$$ = EM_dupliquer($2);}
	|OP_SOUS fonction	{$$ = EM_creerAPartirDUneOperationUnaire(MOINS, $2);}
	|OP_SIN PAR_G fonction PAR_D	{$$ = EM_creerAPartirDUneOperationUnaire(SIN, $3);}
	|OP_COS PAR_G fonction PAR_D	{$$ = EM_creerAPartirDUneOperationUnaire(COS, $3);}
	|OP_TAN PAR_G fonction PAR_D	{$$ = EM_creerAPartirDUneOperationUnaire(TAN, $3);}
	|OP_EXP PAR_G fonction PAR_D	{$$ = EM_creerAPartirDUneOperationUnaire(EXP, $3);}
	|OP_LOG PAR_G fonction PAR_D	{$$ = EM_creerAPartirDUneOperationUnaire(LOG, $3);}
	|fonction OP_ADD fonction	{$$ = EM_creerAPartirDUneOperationBinaire(ADDITION, $1, $3);}
	|fonction OP_SOUS fonction	{$$ = EM_creerAPartirDUneOperationBinaire(SOUSTRACTION, $1, $3);}
	|fonction OP_MUL fonction	{$$ = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, $1, $3);}
	|fonction OP_DIV fonction	{$$ = EM_creerAPartirDUneOperationBinaire(DIVISION, $1, $3);}
	|fonction OP_POW fonction	{$$ = EM_creerAPartirDUneOperationBinaire(EXPOSANT, $1, $3);}
	;
%%

int yyerror(char *msg){
  printf("Erreur : %s\n",msg);
  return 1;
}

int main(void){

	int commande;
	char* variable;
	EM_ExpressionMathematique derivee;

	do {

		printf("derive > ");
		yyparse(&derivee, &variable, &commande);

		if (commande == AFFICHER)
			printf("d(%s)/d%s = %s\n",expressionMathematiqueEnChaine(derivee), variable, expressionMathematiqueEnChaine(simplifier(calculerDerivee(derivee, variable))));
	
	} while (commande!=QUITTER);

	return EXIT_SUCCESS;
}

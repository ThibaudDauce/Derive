#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"ExpressionMathematique.h"

EM_ExpressionMathematique EM_creer() {
  return (EM_ExpressionMathematique)malloc(sizeof(struct EM_ExpressionMathematique));
}

EM_ExpressionMathematique EM_creerAPartirDUnNombre(float nb) {
  EM_ExpressionMathematique resultat=EM_creer();
  resultat->type=NOMBRE;
  resultat->nombre=nb;
  return resultat;
}

EM_ExpressionMathematique EM_creerAPartirDUneVariable(char* var) {
  EM_ExpressionMathematique resultat=EM_creer();
  resultat->type=VARIABLE;
  resultat->variable=var;
  return resultat;
}

EM_ExpressionMathematique EM_creerAPartirDUneOperationUnaire(EM_OperateurUnaire operateur, 
							     EM_ExpressionMathematique operande) {
  EM_ExpressionMathematique resultat=EM_creer();
  resultat->type=OPERATION;
  resultat->operation.cardinalite=UNAIRE;
  resultat->operation.operationUnaire.operateur=operateur;
  resultat->operation.operationUnaire.operande=operande;
  return resultat;
}

EM_ExpressionMathematique EM_creerAPartirDUneOperationBinaire(EM_OperateurBinaire operateur, 
							      EM_ExpressionMathematique operandeG, 
							      EM_ExpressionMathematique operandeD) {
  EM_ExpressionMathematique resultat=EM_creer();
  resultat->type=OPERATION;
  resultat->operation.cardinalite=BINAIRE;
  resultat->operation.operationBinaire.operateur=operateur;
  resultat->operation.operationBinaire.operandeGauche=operandeG;
  resultat->operation.operationBinaire.operandeDroite=operandeD;
  return resultat;
}

EM_ExpressionMathematique EM_dupliquerVariable(EM_ExpressionMathematique exp) {
    char* variable;
    char* newVariable;
    variable=EM_obtenirVariable(exp);
    newVariable=(char*)malloc(1+strlen(variable));
    strcpy(newVariable,variable);
    return EM_creerAPartirDUneVariable(newVariable);
}

EM_ExpressionMathematique EM_dupliquerOperationUnaire(EM_ExpressionMathematique exp) {
  EM_OperateurUnaire operateur;
  EM_ExpressionMathematique operande;
  EM_obtenirOperationUnaire(exp,&operateur,&operande);
  return EM_creerAPartirDUneOperationUnaire(operateur,EM_dupliquer(operande));
}

EM_ExpressionMathematique EM_dupliquerOperationBinaire(EM_ExpressionMathematique exp) {
  EM_OperateurBinaire operateur;
  EM_ExpressionMathematique operandeG;
  EM_ExpressionMathematique operandeD;
  EM_obtenirOperationBinaire(exp,&operateur,&operandeG,&operandeD);
  return EM_creerAPartirDUneOperationBinaire(operateur,EM_dupliquer(operandeG),EM_dupliquer(operandeD));
}

EM_ExpressionMathematique EM_dupliquer(EM_ExpressionMathematique exp) {

  if (EM_estUnNombre(exp))
    return EM_creerAPartirDUnNombre(EM_obtenirNombre(exp));
  else
    if (EM_estUneVariable(exp)) 
      return EM_dupliquerVariable(exp);
    else 
      if (EM_estUneOperationUnaire(exp)) 
	return EM_dupliquerOperationUnaire(exp);
      else
	return EM_dupliquerOperationBinaire(exp);	
}

int EM_estUnNombre(EM_ExpressionMathematique exp) {
  return exp->type==NOMBRE;
}
int EM_estUneVariable(EM_ExpressionMathematique exp) {
  return exp->type==VARIABLE;
}

int EM_estUneOperationUnaire(EM_ExpressionMathematique exp) {
  return (exp->type==OPERATION) && (exp->operation.cardinalite==UNAIRE);
}

int EM_estUneOperationBinaire(EM_ExpressionMathematique exp) {
  return (exp->type==OPERATION) && (exp->operation.cardinalite==BINAIRE);
}

/* Les fonctions suivantes peuvent genenerer des erreurs (voir errno) */
float EM_obtenirNombre(EM_ExpressionMathematique exp) {
  float resultat=0;
  errno=ERRNO_OK;
  if (!EM_estUnNombre(exp)) {
    errno=ERRNO_PAS_UN_NOMBRE;
  } else {
    resultat=exp->nombre;
  }
  return resultat;
}

char* EM_obtenirVariable(EM_ExpressionMathematique exp) {
  char* resultat=0;
  errno=ERRNO_OK;
  if (!EM_estUneVariable(exp)) {
    errno=ERRNO_PAS_UNE_VARIABLE;
  } else {
    resultat=exp->variable;
  }
  return resultat;
}

void EM_obtenirOperationUnaire(EM_ExpressionMathematique exp, 
			       EM_OperateurUnaire* operateur, 
			       EM_ExpressionMathematique* operande) {
  errno=ERRNO_OK;
  if (!EM_estUneOperationUnaire(exp)) {
    errno=ERRNO_PAS_UNE_OPERATION_UNAIRE;
  } else {
    *operateur=exp->operation.operationUnaire.operateur;
    *operande=exp->operation.operationUnaire.operande;
  }
}

void EM_obtenirOperationBinaire(EM_ExpressionMathematique exp, 
				EM_OperateurBinaire* operateur, 
				EM_ExpressionMathematique* operandeG, 
				EM_ExpressionMathematique* operandeD) {
  errno=ERRNO_OK;
  if (!EM_estUneOperationBinaire(exp)) {
    errno=ERRNO_PAS_UNE_OPERATION_BINAIRE;
  } else {
    *operateur=exp->operation.operationBinaire.operateur;
    *operandeG=exp->operation.operationBinaire.operandeGauche;
    *operandeD=exp->operation.operationBinaire.operandeDroite;
  }
}

void EM_detruire(EM_ExpressionMathematique* exp) {
  if (!EM_estUnNombre(*exp)) {
    if (EM_estUneVariable(*exp)) {
      free((*exp)->variable);
    } else {
      if (EM_estUneOperationUnaire(*exp)) {
	EM_detruire(&((*exp)->operation.operationUnaire.operande));
      } else {
	EM_detruire(&((*exp)->operation.operationBinaire.operandeGauche));
	EM_detruire(&((*exp)->operation.operationBinaire.operandeDroite));
      }
    }
  }
  free(*exp);  
  *exp=NULL;
}

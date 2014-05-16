#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"libExpressionMathematique.h"

#define TAILLE 255

/* Affichage*/
char* floatEnChaine(float f) {
	char* resultat;
	char buf[TAILLE];
	sprintf(buf,"%g",f);
	resultat=(char*)malloc(1+strlen(buf));
	strcpy(resultat,buf);
	return resultat;  
}

char* strEnChaine(char* s) {
	char* resultat;
	char buf[TAILLE];
	sprintf(buf,"%s",s);
	resultat=(char*)malloc(1+strlen(buf));
	strcpy(resultat,buf);
	return resultat;  
}

char* operationUnaireEnChaine(EM_ExpressionMathematique exp) {
	char* resultat;
	char* strOperande;
	char* strOperateur;
	char buf[TAILLE];
	EM_OperateurUnaire operateur;
	EM_ExpressionMathematique operande;

	EM_obtenirOperationUnaire(exp,&operateur,&operande);
	switch(operateur) {
	case MOINS : strOperateur="-"; break;
	case SIN : strOperateur="sin"; break;
	case COS : strOperateur="cos"; break;
	case TAN : strOperateur="tan"; break;
	case EXP : strOperateur="exp"; break;
	case LOG : strOperateur="log"; break;
	}
	strOperande=expressionMathematiqueEnChaine(operande);
	if (operateur==MOINS && !EM_estUneOperationUnaire(operande) && !EM_estUneOperationBinaire(operande)) 
		sprintf(buf,"%s%s",strOperateur,strOperande);
	else
		sprintf(buf,"%s(%s)",strOperateur,strOperande); 
	resultat=(char*)malloc(1+strlen(buf));
	strcpy(resultat,buf);
	free(strOperande);
	return resultat;   
}

char* operationBinaireEnChaine(EM_ExpressionMathematique exp) {
	char* resultat;
	char* strOperandeG;
	char* strOperandeD;
	char* strOperateur;
	char* avantOperandeGauche="";
	char* apresOperandeGauche="";
	char* avantOperandeDroite="";
	char* apresOperandeDroite="";
	char buf[TAILLE];
	EM_OperateurBinaire operateur;
	EM_ExpressionMathematique operandeG;
	EM_ExpressionMathematique operandeD;

	EM_obtenirOperationBinaire(exp,&operateur,&operandeG,&operandeD);
	switch(operateur) {
	case ADDITION : strOperateur="+"; break;
	case SOUSTRACTION : strOperateur="-"; break;
	case MULTIPLICATION : strOperateur="*"; break;
	case DIVISION : strOperateur="/"; break;
	case EXPOSANT : strOperateur="^"; break;
	}
	strOperandeG=expressionMathematiqueEnChaine(operandeG);
	strOperandeD=expressionMathematiqueEnChaine(operandeD);
	if(EM_estUneOperationBinaire(operandeG)) {
		avantOperandeGauche="(";
		apresOperandeGauche=")";
	}
	if(EM_estUneOperationBinaire(operandeD)) {
		avantOperandeDroite="(";
		apresOperandeDroite=")";
	}
	sprintf(buf,"%s%s%s%s%s%s%s",avantOperandeGauche,strOperandeG,apresOperandeGauche,strOperateur,avantOperandeDroite,strOperandeD,apresOperandeDroite); 
	resultat=(char*)malloc(1+strlen(buf));
	strcpy(resultat,buf);
	free(strOperandeG);
	free(strOperandeD);
	return resultat;   
}

char* expressionMathematiqueEnChaine(EM_ExpressionMathematique exp) {
	char* resultat;
	if (EM_estUnNombre(exp)){
		resultat=floatEnChaine(EM_obtenirNombre(exp));
	} else {
		if (EM_estUneVariable(exp)){
			resultat=strEnChaine(EM_obtenirVariable(exp));
		} else {
			if (EM_estUneOperationUnaire(exp))
	resultat=operationUnaireEnChaine(exp);
			else
	resultat=operationBinaireEnChaine(exp);
		}
	}
	return resultat;  
}

/* Derive */

EM_ExpressionMathematique calculerDeriveeSin(EM_ExpressionMathematique exp, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique operandeG;
	EM_ExpressionMathematique operandeD;

	operandeG = calculerDerivee(exp, variable);
	operandeD = EM_creerAPartirDUneOperationUnaire(COS, EM_dupliquer(exp));

	resultat = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, operandeG, operandeD);

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeCos(EM_ExpressionMathematique exp, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique operandeG;
	EM_ExpressionMathematique operandeD;
	EM_ExpressionMathematique resultatPositif;

	operandeG = calculerDerivee(exp, variable);
	operandeD = EM_creerAPartirDUneOperationUnaire(SIN, EM_dupliquer(exp));

	resultatPositif = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, operandeG, operandeD);
	resultat = EM_creerAPartirDUneOperationUnaire(MOINS, resultatPositif);

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeTan(EM_ExpressionMathematique exp, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique numerateur;

	EM_ExpressionMathematique expressionCos;
	EM_ExpressionMathematique denominateur;

	numerateur = calculerDerivee(exp, variable);
	expressionCos = EM_creerAPartirDUneOperationUnaire(COS, EM_dupliquer(exp));
	denominateur = EM_creerAPartirDUneOperationBinaire(EXPOSANT, expressionCos, EM_creerAPartirDUnNombre(2));

	resultat = EM_creerAPartirDUneOperationBinaire(DIVISION, numerateur, denominateur);

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeLog(EM_ExpressionMathematique exp, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique numerateur;
	EM_ExpressionMathematique denominateur;

	numerateur = calculerDerivee(exp, variable);
	denominateur = EM_dupliquer(exp);

	resultat = EM_creerAPartirDUneOperationBinaire(DIVISION, numerateur, denominateur);

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeExp(EM_ExpressionMathematique exp, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique operandeG;
	EM_ExpressionMathematique operandeD;

	operandeG = calculerDerivee(exp, variable);
	operandeD = EM_creerAPartirDUneOperationUnaire(EXP, EM_dupliquer(exp));

	resultat = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, operandeG, operandeD);

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeOperationUnaire(EM_ExpressionMathematique exp, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_OperateurUnaire operateur;
	EM_ExpressionMathematique operande;

	EM_obtenirOperationUnaire(exp,&operateur,&operande);

	switch(operateur) {
		case MOINS : resultat = EM_creerAPartirDUneOperationUnaire(operateur,calculerDerivee(operande, variable)); break;
		case SIN : resultat   = calculerDeriveeSin(operande, variable); break;
		case COS : resultat   = calculerDeriveeCos(operande, variable); break;
		case TAN : resultat   = calculerDeriveeTan(operande, variable); break;
		case EXP : resultat   = calculerDeriveeExp(operande, variable); break;
		case LOG : resultat   = calculerDeriveeLog(operande, variable);
	}
	return resultat;
}

EM_ExpressionMathematique calculerDeriveePlus(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD, char* variable) {
	EM_ExpressionMathematique resultat;
	
	resultat = EM_creerAPartirDUneOperationBinaire(ADDITION, calculerDerivee(operandeG, variable), calculerDerivee(operandeD, variable));

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeMoins(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD, char* variable) {
	EM_ExpressionMathematique resultat;

	resultat = EM_creerAPartirDUneOperationBinaire(SOUSTRACTION, calculerDerivee(operandeG, variable), calculerDerivee(operandeD, variable));

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeMul(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique deriveeOperandeG;
	EM_ExpressionMathematique deriveeOperandeD;
	EM_ExpressionMathematique operandeGDeLaDerivee;
	EM_ExpressionMathematique operandeDDeLaDerivee;

	deriveeOperandeG = calculerDerivee(operandeG, variable);
	deriveeOperandeD = calculerDerivee(operandeD, variable);

	operandeGDeLaDerivee = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, deriveeOperandeG, EM_dupliquer(operandeD));
	operandeDDeLaDerivee = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, deriveeOperandeD, EM_dupliquer(operandeG));

	resultat = EM_creerAPartirDUneOperationBinaire(ADDITION, operandeGDeLaDerivee, operandeDDeLaDerivee);

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeDiv(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique deriveeOperandeG;
	EM_ExpressionMathematique deriveeOperandeD;
	EM_ExpressionMathematique operandeGDeLaDerivee;
	EM_ExpressionMathematique operandeDDeLaDerivee;
	EM_ExpressionMathematique numerateur;
	EM_ExpressionMathematique denominateur;

	deriveeOperandeG = calculerDerivee(operandeG, variable);
	deriveeOperandeD = calculerDerivee(operandeD, variable);

	operandeGDeLaDerivee = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, deriveeOperandeG, EM_dupliquer(operandeD));
	operandeDDeLaDerivee = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, deriveeOperandeD, EM_dupliquer(operandeG));

	numerateur = EM_creerAPartirDUneOperationBinaire(SOUSTRACTION, operandeGDeLaDerivee, operandeDDeLaDerivee);
	denominateur = EM_creerAPartirDUneOperationBinaire(EXPOSANT, EM_dupliquer(operandeD), EM_creerAPartirDUnNombre(2));

	resultat = EM_creerAPartirDUneOperationBinaire(DIVISION, numerateur, denominateur);

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeExposant(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique deriveeOperandeG;
	EM_ExpressionMathematique deriveeOperandeD;
	EM_ExpressionMathematique operandeGDeLAdditionDerivee;
	EM_ExpressionMathematique divisionOperandeDDeLAddition;
	EM_ExpressionMathematique operandeDDeLAdditionDerivee;
	EM_ExpressionMathematique lnOperandeG;
	EM_ExpressionMathematique operandeExp;
	EM_ExpressionMathematique operandeAddition;

	deriveeOperandeG = calculerDerivee(operandeG, variable);
	deriveeOperandeD = calculerDerivee(operandeD, variable);
	
	operandeExp = EM_creerAPartirDUneOperationBinaire(EXPOSANT, EM_dupliquer(operandeG), EM_dupliquer(operandeD));
	lnOperandeG = EM_creerAPartirDUneOperationUnaire(LOG, EM_dupliquer(operandeG));
	operandeGDeLAdditionDerivee = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, deriveeOperandeD, lnOperandeG);
	divisionOperandeDDeLAddition = EM_creerAPartirDUneOperationBinaire(DIVISION, deriveeOperandeG, EM_dupliquer(operandeG));
	operandeDDeLAdditionDerivee = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, EM_dupliquer(operandeD), divisionOperandeDDeLAddition);
		
	operandeAddition = EM_creerAPartirDUneOperationBinaire(ADDITION, operandeGDeLAdditionDerivee, operandeDDeLAdditionDerivee);

	resultat = EM_creerAPartirDUneOperationBinaire(MULTIPLICATION, operandeExp, operandeAddition);

	return resultat;
}

EM_ExpressionMathematique calculerDeriveeOperationBinaire(EM_ExpressionMathematique exp, char* variable) {
	EM_ExpressionMathematique resultat;
	EM_OperateurBinaire operateur;
	EM_ExpressionMathematique operandeG;
	EM_ExpressionMathematique operandeD;

	EM_obtenirOperationBinaire(exp,&operateur,&operandeG,&operandeD);

	switch(operateur) {
		case ADDITION : resultat       = calculerDeriveePlus(operandeG,operandeD, variable); break;
		case SOUSTRACTION : resultat   = calculerDeriveeMoins(operandeG,operandeD, variable); break;
		case MULTIPLICATION : resultat = calculerDeriveeMul(operandeG,operandeD, variable); break;
		case DIVISION : resultat       = calculerDeriveeDiv(operandeG,operandeD, variable); break;
		case EXPOSANT : resultat       = calculerDeriveeExposant(operandeG,operandeD, variable);
	}
	return resultat;
}

EM_ExpressionMathematique calculerDerivee(EM_ExpressionMathematique exp, char* variable) {
	EM_ExpressionMathematique resultat;
	if (EM_estUneOperationBinaire(exp)) {
		resultat=calculerDeriveeOperationBinaire(exp, variable);
	} else {
		if (EM_estUneOperationUnaire(exp)) {
			resultat=calculerDeriveeOperationUnaire(exp, variable);
		} else {
			if (EM_estUnNombre(exp)) {
				resultat = EM_creerAPartirDUnNombre(0);
			} else {
				resultat = EM_creerAPartirDUnNombre(1);
			}
		}
	}
	return resultat;
}

/* Simplification */
/* Algorithmiques qui pourraient etre ameliores */

EM_ExpressionMathematique simplifierOperationUnaire(EM_ExpressionMathematique exp) {
	EM_ExpressionMathematique resultat;
	EM_OperateurUnaire operateur;
	EM_ExpressionMathematique operande;

	EM_obtenirOperationUnaire(exp,&operateur,&operande);
	resultat=EM_creerAPartirDUneOperationUnaire(operateur,simplifier(operande));
	return resultat;
}



EM_ExpressionMathematique simplifierPlus(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique opGSimplifie=simplifier(operandeG);
	EM_ExpressionMathematique opDSimplifie=simplifier(operandeD);

	if (EM_estUnNombre(opGSimplifie) && EM_estUnNombre(opDSimplifie)) {
		resultat=EM_creerAPartirDUnNombre(EM_obtenirNombre(opGSimplifie)+EM_obtenirNombre(opDSimplifie));
	} else {
		if (EM_estUnNombre(opGSimplifie) && EM_obtenirNombre(opGSimplifie)==0)
			resultat=opDSimplifie;
		else
			if (EM_estUnNombre(opDSimplifie) && EM_obtenirNombre(opDSimplifie)==0)
	resultat=opGSimplifie;
			else
	resultat=EM_creerAPartirDUneOperationBinaire(ADDITION,opGSimplifie,opDSimplifie);
	}

	return resultat;
}

EM_ExpressionMathematique simplifierMoins(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique opGSimplifie=simplifier(operandeG);
	EM_ExpressionMathematique opDSimplifie=simplifier(operandeD);

	if (EM_estUnNombre(opGSimplifie) && EM_estUnNombre(opDSimplifie)) {
		resultat=EM_creerAPartirDUnNombre(EM_obtenirNombre(opGSimplifie)-EM_obtenirNombre(opDSimplifie));
	} else {
		if (EM_estUnNombre(opGSimplifie) && EM_obtenirNombre(opGSimplifie)==0)
			resultat=EM_creerAPartirDUneOperationUnaire(MOINS,opDSimplifie);
		else
			if (EM_estUnNombre(opDSimplifie) && EM_obtenirNombre(opDSimplifie)==0)
	resultat=opGSimplifie;
			else
	resultat=EM_creerAPartirDUneOperationBinaire(SOUSTRACTION,opGSimplifie,opDSimplifie);
	}
	return resultat;
}

EM_ExpressionMathematique simplifierMul(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique opGSimplifie=simplifier(operandeG);
	EM_ExpressionMathematique opDSimplifie=simplifier(operandeD);

	if (EM_estUnNombre(opGSimplifie) && EM_estUnNombre(opDSimplifie)) {
		resultat=EM_creerAPartirDUnNombre(EM_obtenirNombre(opGSimplifie)*EM_obtenirNombre(opDSimplifie));
	} else {
		if (EM_estUnNombre(opGSimplifie)) {
			if (EM_obtenirNombre(opGSimplifie)==0) {
	resultat=EM_creerAPartirDUnNombre(0.);
			} else {
	 if (EM_obtenirNombre(opGSimplifie)==1)
		 resultat=EM_dupliquer(operandeD);
	 else
		 resultat=EM_creerAPartirDUneOperationBinaire(MULTIPLICATION,opGSimplifie,opDSimplifie);
			}
		} else {
			if (EM_estUnNombre(opDSimplifie)) {
	if (EM_obtenirNombre(opDSimplifie)==0) {
		resultat=EM_creerAPartirDUnNombre(0.);
	} else {
		if (EM_obtenirNombre(opDSimplifie)==1)
			resultat=EM_dupliquer(operandeG);
		else
			resultat=EM_creerAPartirDUneOperationBinaire(MULTIPLICATION,opGSimplifie,opDSimplifie);
	}      
			} else
	resultat=EM_creerAPartirDUneOperationBinaire(MULTIPLICATION,opGSimplifie,opDSimplifie);
		}
	}
 
	return resultat;
}

EM_ExpressionMathematique simplifierDiv(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique opGSimplifie=simplifier(operandeG);
	EM_ExpressionMathematique opDSimplifie=simplifier(operandeD);
	
	resultat=EM_creerAPartirDUneOperationBinaire(DIVISION,opGSimplifie,opDSimplifie);

	return resultat;
}

EM_ExpressionMathematique simplifierExposant(EM_ExpressionMathematique operandeG, EM_ExpressionMathematique operandeD) {
	EM_ExpressionMathematique resultat;
	EM_ExpressionMathematique opGSimplifie=simplifier(operandeG);
	EM_ExpressionMathematique opDSimplifie=simplifier(operandeD);
	
	resultat=EM_creerAPartirDUneOperationBinaire(EXPOSANT,opGSimplifie,opDSimplifie);

	return resultat;
}


EM_ExpressionMathematique simplifierOperationBinaire(EM_ExpressionMathematique exp) {
	EM_ExpressionMathematique resultat;
	EM_OperateurBinaire operateur;
	EM_ExpressionMathematique operandeG;
	EM_ExpressionMathematique operandeD;

	EM_obtenirOperationBinaire(exp,&operateur,&operandeG,&operandeD);
	switch(operateur) {
	case ADDITION : resultat=simplifierPlus(operandeG,operandeD); break;
	case SOUSTRACTION : resultat=simplifierMoins(operandeG,operandeD); break;
	case MULTIPLICATION : resultat=simplifierMul(operandeG,operandeD); break;
	case DIVISION : resultat=simplifierDiv(operandeG,operandeD); break;
	case EXPOSANT : resultat=simplifierExposant (operandeG,operandeD);
	}
	return resultat;
}


EM_ExpressionMathematique simplifier(EM_ExpressionMathematique exp) {

	EM_ExpressionMathematique resultat;

	if (EM_estUneOperationBinaire(exp)) {
		resultat = simplifierOperationBinaire(exp);
	} else {
		if (EM_estUneOperationUnaire(exp)) {
			resultat = simplifierOperationUnaire(exp);
		} else {
			resultat=EM_dupliquer(exp);
		}
	}
	return resultat;
}

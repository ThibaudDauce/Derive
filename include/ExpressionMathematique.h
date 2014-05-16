/**
 * \file ExpressionMathematique.h
 * \brief Implantation du TAD expression mathématique
 * \author N. Delestre
 * \version 2.0
 * \date 27/2/2013
 *
 */

/* Partie privee */
#ifndef __EXPRESSION_MATHEMATIQUE__
#define __EXPRESSION_MATHEMATIQUE__

/**
 * \enum EM_Type 
 * \brief Permet de savoir si une expression mathématique est un nombre, une variable ou une opération
 */
typedef enum EM_Type {NOMBRE, VARIABLE, OPERATION} EM_Type;

/**
 * \enum EM_CardinaliteOperation 
 * \brief Dans le cas ou une expression mathématique est une opération, EM_CardinaliteOperation permet de savoir si c'est une opération uniare ou binaire
 */
typedef enum EM_CardinaliteOperation {UNAIRE,BINAIRE} EM_CardinaliteOperation;

/**
 * \enum EM_OperateurUnaire 
 * \brief Dans le cas ou une expression mathématique est une opération composée d'un opérateur unaire, EM_OperateurUnaire parmet de savoir si c'est l'oparteur moins, ou les fonctions sinus, cosinus, tangente, exponentiel ou logarithme
 */
typedef enum EM_OperateurUnaire {MOINS, SIN, COS, TAN, EXP, LOG} EM_OperateurUnaire;

/**
 * \enum EM_OperateurBinaire 
 * \brief Dans le cas ou une expression mathématique est une opération composée d'un opérateur binaire, EM_OperateurBinaire parmet de savoir si c'est l'oparteur d'addition, de soustraction de multiplication de division ou d'exposant
 */
typedef enum EM_OperateurBinaire {ADDITION, SOUSTRACTION, MULTIPLICATION, DIVISION, EXPOSANT} EM_OperateurBinaire; 

/**
 * \type EM_ExpressionMathematique
 * \brief Une expression mathématique est en fait un pointeur sur une struct EM_ExpressionMathematique
 */
typedef struct EM_ExpressionMathematique* EM_ExpressionMathematique;

/**
 * \struct struct EM_OperationUnaire
 * \brief Permet de représenter les opérations uniares
 */
typedef struct EM_OperationUnaire{
  EM_OperateurUnaire operateur;
  EM_ExpressionMathematique operande;
} EM_OperationUnaire;

/**
 * \struct struct EM_OperationBinaire
 * \brief Permet de représenter les opérations binaires
 */
typedef struct EM_OperationBinaire{
  EM_OperateurBinaire operateur;
  EM_ExpressionMathematique operandeGauche;
  EM_ExpressionMathematique operandeDroite;
} EM_OperationBinaire;

/**
 * \struct struct EM_Operation
 * \brief Une struct EM_Operation est soit une opération uniare, soit une opération binaire
 */
typedef struct EM_Operation {
  EM_CardinaliteOperation cardinalite;
  EM_OperationUnaire operationUnaire;
  EM_OperationBinaire operationBinaire;
} EM_Operation;

/**
 * \struct struct EM_ExpressionMathematique
 * \brief Une struct EM_ExpressionMathematique est soit un nombre, soit une variable soit une opération
 */
struct EM_ExpressionMathematique {
  EM_Type type;
  float nombre;
  char* variable;
  EM_Operation operation;
};

/* Partie publique*/ 
/**
 * \fn EM_ExpressionMathematique EM_creerAPartirDUnNombre(float nb)
 * \brief Permet de créer une expression mathématique qui est en fait un nombre
 */
EM_ExpressionMathematique EM_creerAPartirDUnNombre(float nb);

/**
 * \fn EM_ExpressionMathematique EM_creerAPartirDUneVariable(char* var)
 * \brief Permet de créer une expression mathématique qui est en fait une variable
 * \attention La variable est représenter comme une chaîne de caractères. L'allocation de cette chaîne est à la charge de l'utilisateur 
 */
EM_ExpressionMathematique EM_creerAPartirDUneVariable(char* var);

/**
 * \fn EM_ExpressionMathematique EM_creerAPartirDUneOperationUnaire(EM_OperateurUnaire operateur, EM_ExpressionMathematique operande)
 * \brief Permet de créer une expression mathématique qui est en fait une opération unaire
 * \attention Il n'y pas duplication de l'expression arithmétique passée en paramètre 
 */
EM_ExpressionMathematique EM_creerAPartirDUneOperationUnaire(EM_OperateurUnaire operateur, 
							     EM_ExpressionMathematique operande);

/**
 * \fn EM_ExpressionMathematique EM_creerAPartirDUneOperationBinaire(EM_OperateurBinaire operateur, EM_ExpressionMathematique operandeG,  EM_ExpressionMathematique operandeD)
 * \brief Permet de créer une expression mathématique qui est en fait une opération binaire
 * \attention Il n'y pas duplication des deux expressions arithmétiques passées en paramètre 
 */
EM_ExpressionMathematique EM_creerAPartirDUneOperationBinaire(EM_OperateurBinaire operateur, 
							      EM_ExpressionMathematique operandeG, 
							      EM_ExpressionMathematique operandeD);

/**
 * \fn EM_ExpressionMathematique EM_dupliquer(EM_ExpressionMathematique exp)
 * \brief Permet de dupliquer une expression arithmétique
 */
EM_ExpressionMathematique EM_dupliquer(EM_ExpressionMathematique exp); 

/**
 * \fn int EM_estUnNombre(EM_ExpressionMathematique exp)
 * \brief Permet de savoir une expression arithmétique est en fait un nombre
 */
int EM_estUnNombre(EM_ExpressionMathematique exp);

/**
 * \fn int EM_estUneVariable(EM_ExpressionMathematique exp)
 * \brief Permet de savoir une expression arithmétique est en fait une variable
 */
int EM_estUneVariable(EM_ExpressionMathematique exp);

/**
 * \fn int EM_estUneOperationUnaire(EM_ExpressionMathematique exp)
 * \brief Permet de savoir une expression arithmétique est en fait une opération unaire
 */
int EM_estUneOperationUnaire(EM_ExpressionMathematique exp);

/**
 * \fn int EM_estUneOperationBinaire(EM_ExpressionMathematique exp)
 * \brief Permet de savoir une expression arithmétique est en fait une opération binaire
 */
int EM_estUneOperationBinaire(EM_ExpressionMathematique exp);

/* Les fonctions suivantes peuvent genenerer des erreurs  */
#define ERRNO_OK 0
#define ERRNO_PAS_UN_NOMBRE 1
#define ERRNO_PAS_UNE_VARIABLE 2
#define ERRNO_PAS_UNE_OPERATION_UNAIRE 3
#define ERRNO_PAS_UNE_OPERATION_BINAIRE 4

/**
 * \fn EM_obtenirNombre(EM_ExpressionMathematique exp)
 * \brief Permet d'obtrenir le nombre représenté par l'expression mathématique
 * \attention errno vaut ERRNO_PAS_UN_NOMBRE si l'expression mathématique ne représentait pas un nombre
 */
float EM_obtenirNombre(EM_ExpressionMathematique exp);

/**
 * \fn char* EM_obtenirVariable(EM_ExpressionMathematique exp);
 * \brief Permet d'obtrenir la variable représentée par l'expression mathématique
 * \attention errno vaut  ERRNO_PAS_UNE_VARIABLE si l'expression mathématique ne représentait pas une variable
 * \attention la chaîne de caractères retournée n'est pas dupliquée
 */
char* EM_obtenirVariable(EM_ExpressionMathematique exp);

/**
 * \fn void EM_obtenirOperationUnaire(EM_ExpressionMathematique exp, EM_OperateurUnaire* operateur, EM_ExpressionMathematique* operande)
 * \brief Permet d'obtrenir l'opérateur unaire et l'opérande représentés par l'expression mathématique
 * \attention errno vaut ERRNO_PAS_UNE_OPERATION_UNAIRE  si l'expression mathématique ne représentait pas une opération uniare
 * \attention l'expression mathématique (opérande) obtenue n'est pas dupliquée
 */
void EM_obtenirOperationUnaire(EM_ExpressionMathematique exp, 
			       EM_OperateurUnaire* operateur, 
			       EM_ExpressionMathematique* operande);

/**
 * \fn void EM_obtenirOperationBinaire(EM_ExpressionMathematique exp, EM_OperateurBinaire* operateur, EM_ExpressionMathematique* operandeG, EM_ExpressionMathematique* operandeD);
 * \brief Permet d'obtrenir l'opérateur binaire et les deux opérades représentés par l'expression mathématique
 * \attention errno vaut ERRNO_PAS_UNE_OPERATION_BINAIRE  si l'expression mathématique ne représentait pas une opération binaire
 * \attention les deux expressions mathématiques (opérande gauche et droite) obtenues ne sont pas dupliquées
 */
void EM_obtenirOperationBinaire(EM_ExpressionMathematique exp, 
				EM_OperateurBinaire* operateur, 
				EM_ExpressionMathematique* operandeG, 
				EM_ExpressionMathematique* operandeD);

/**
 * \fn EM_detruire(EM_ExpressionMathematique* exp)
 * \brief Permet de détruire (libérer la mémoire) une expression mathématique
 */
void EM_detruire(EM_ExpressionMathematique* exp);

#endif



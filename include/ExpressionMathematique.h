/**
 * \file ExpressionMathematique.h
 * \brief Implantation du TAD expression math�matique
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
 * \brief Permet de savoir si une expression math�matique est un nombre, une variable ou une op�ration
 */
typedef enum EM_Type {NOMBRE, VARIABLE, OPERATION} EM_Type;

/**
 * \enum EM_CardinaliteOperation 
 * \brief Dans le cas ou une expression math�matique est une op�ration, EM_CardinaliteOperation permet de savoir si c'est une op�ration uniare ou binaire
 */
typedef enum EM_CardinaliteOperation {UNAIRE,BINAIRE} EM_CardinaliteOperation;

/**
 * \enum EM_OperateurUnaire 
 * \brief Dans le cas ou une expression math�matique est une op�ration compos�e d'un op�rateur unaire, EM_OperateurUnaire parmet de savoir si c'est l'oparteur moins, ou les fonctions sinus, cosinus, tangente, exponentiel ou logarithme
 */
typedef enum EM_OperateurUnaire {MOINS, SIN, COS, TAN, EXP, LOG} EM_OperateurUnaire;

/**
 * \enum EM_OperateurBinaire 
 * \brief Dans le cas ou une expression math�matique est une op�ration compos�e d'un op�rateur binaire, EM_OperateurBinaire parmet de savoir si c'est l'oparteur d'addition, de soustraction de multiplication de division ou d'exposant
 */
typedef enum EM_OperateurBinaire {ADDITION, SOUSTRACTION, MULTIPLICATION, DIVISION, EXPOSANT} EM_OperateurBinaire; 

/**
 * \type EM_ExpressionMathematique
 * \brief Une expression math�matique est en fait un pointeur sur une struct EM_ExpressionMathematique
 */
typedef struct EM_ExpressionMathematique* EM_ExpressionMathematique;

/**
 * \struct struct EM_OperationUnaire
 * \brief Permet de repr�senter les op�rations uniares
 */
typedef struct EM_OperationUnaire{
  EM_OperateurUnaire operateur;
  EM_ExpressionMathematique operande;
} EM_OperationUnaire;

/**
 * \struct struct EM_OperationBinaire
 * \brief Permet de repr�senter les op�rations binaires
 */
typedef struct EM_OperationBinaire{
  EM_OperateurBinaire operateur;
  EM_ExpressionMathematique operandeGauche;
  EM_ExpressionMathematique operandeDroite;
} EM_OperationBinaire;

/**
 * \struct struct EM_Operation
 * \brief Une struct EM_Operation est soit une op�ration uniare, soit une op�ration binaire
 */
typedef struct EM_Operation {
  EM_CardinaliteOperation cardinalite;
  EM_OperationUnaire operationUnaire;
  EM_OperationBinaire operationBinaire;
} EM_Operation;

/**
 * \struct struct EM_ExpressionMathematique
 * \brief Une struct EM_ExpressionMathematique est soit un nombre, soit une variable soit une op�ration
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
 * \brief Permet de cr�er une expression math�matique qui est en fait un nombre
 */
EM_ExpressionMathematique EM_creerAPartirDUnNombre(float nb);

/**
 * \fn EM_ExpressionMathematique EM_creerAPartirDUneVariable(char* var)
 * \brief Permet de cr�er une expression math�matique qui est en fait une variable
 * \attention La variable est repr�senter comme une cha�ne de caract�res. L'allocation de cette cha�ne est � la charge de l'utilisateur 
 */
EM_ExpressionMathematique EM_creerAPartirDUneVariable(char* var);

/**
 * \fn EM_ExpressionMathematique EM_creerAPartirDUneOperationUnaire(EM_OperateurUnaire operateur, EM_ExpressionMathematique operande)
 * \brief Permet de cr�er une expression math�matique qui est en fait une op�ration unaire
 * \attention Il n'y pas duplication de l'expression arithm�tique pass�e en param�tre 
 */
EM_ExpressionMathematique EM_creerAPartirDUneOperationUnaire(EM_OperateurUnaire operateur, 
							     EM_ExpressionMathematique operande);

/**
 * \fn EM_ExpressionMathematique EM_creerAPartirDUneOperationBinaire(EM_OperateurBinaire operateur, EM_ExpressionMathematique operandeG,  EM_ExpressionMathematique operandeD)
 * \brief Permet de cr�er une expression math�matique qui est en fait une op�ration binaire
 * \attention Il n'y pas duplication des deux expressions arithm�tiques pass�es en param�tre 
 */
EM_ExpressionMathematique EM_creerAPartirDUneOperationBinaire(EM_OperateurBinaire operateur, 
							      EM_ExpressionMathematique operandeG, 
							      EM_ExpressionMathematique operandeD);

/**
 * \fn EM_ExpressionMathematique EM_dupliquer(EM_ExpressionMathematique exp)
 * \brief Permet de dupliquer une expression arithm�tique
 */
EM_ExpressionMathematique EM_dupliquer(EM_ExpressionMathematique exp); 

/**
 * \fn int EM_estUnNombre(EM_ExpressionMathematique exp)
 * \brief Permet de savoir une expression arithm�tique est en fait un nombre
 */
int EM_estUnNombre(EM_ExpressionMathematique exp);

/**
 * \fn int EM_estUneVariable(EM_ExpressionMathematique exp)
 * \brief Permet de savoir une expression arithm�tique est en fait une variable
 */
int EM_estUneVariable(EM_ExpressionMathematique exp);

/**
 * \fn int EM_estUneOperationUnaire(EM_ExpressionMathematique exp)
 * \brief Permet de savoir une expression arithm�tique est en fait une op�ration unaire
 */
int EM_estUneOperationUnaire(EM_ExpressionMathematique exp);

/**
 * \fn int EM_estUneOperationBinaire(EM_ExpressionMathematique exp)
 * \brief Permet de savoir une expression arithm�tique est en fait une op�ration binaire
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
 * \brief Permet d'obtrenir le nombre repr�sent� par l'expression math�matique
 * \attention errno vaut ERRNO_PAS_UN_NOMBRE si l'expression math�matique ne repr�sentait pas un nombre
 */
float EM_obtenirNombre(EM_ExpressionMathematique exp);

/**
 * \fn char* EM_obtenirVariable(EM_ExpressionMathematique exp);
 * \brief Permet d'obtrenir la variable repr�sent�e par l'expression math�matique
 * \attention errno vaut  ERRNO_PAS_UNE_VARIABLE si l'expression math�matique ne repr�sentait pas une variable
 * \attention la cha�ne de caract�res retourn�e n'est pas dupliqu�e
 */
char* EM_obtenirVariable(EM_ExpressionMathematique exp);

/**
 * \fn void EM_obtenirOperationUnaire(EM_ExpressionMathematique exp, EM_OperateurUnaire* operateur, EM_ExpressionMathematique* operande)
 * \brief Permet d'obtrenir l'op�rateur unaire et l'op�rande repr�sent�s par l'expression math�matique
 * \attention errno vaut ERRNO_PAS_UNE_OPERATION_UNAIRE  si l'expression math�matique ne repr�sentait pas une op�ration uniare
 * \attention l'expression math�matique (op�rande) obtenue n'est pas dupliqu�e
 */
void EM_obtenirOperationUnaire(EM_ExpressionMathematique exp, 
			       EM_OperateurUnaire* operateur, 
			       EM_ExpressionMathematique* operande);

/**
 * \fn void EM_obtenirOperationBinaire(EM_ExpressionMathematique exp, EM_OperateurBinaire* operateur, EM_ExpressionMathematique* operandeG, EM_ExpressionMathematique* operandeD);
 * \brief Permet d'obtrenir l'op�rateur binaire et les deux op�rades repr�sent�s par l'expression math�matique
 * \attention errno vaut ERRNO_PAS_UNE_OPERATION_BINAIRE  si l'expression math�matique ne repr�sentait pas une op�ration binaire
 * \attention les deux expressions math�matiques (op�rande gauche et droite) obtenues ne sont pas dupliqu�es
 */
void EM_obtenirOperationBinaire(EM_ExpressionMathematique exp, 
				EM_OperateurBinaire* operateur, 
				EM_ExpressionMathematique* operandeG, 
				EM_ExpressionMathematique* operandeD);

/**
 * \fn EM_detruire(EM_ExpressionMathematique* exp)
 * \brief Permet de d�truire (lib�rer la m�moire) une expression math�matique
 */
void EM_detruire(EM_ExpressionMathematique* exp);

#endif



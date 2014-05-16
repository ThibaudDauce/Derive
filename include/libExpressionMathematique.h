/**
 * \file libExpressionMathematique.h
 * \brief Implantation d'une librairie sur les expressions arim�thiques
 * \author N. Delestre
 * \version 2.0
 * \date 27/2/2013
 *
 */


#ifndef __LIB_EXPRESSION_MATHEMATIQUE__
#define __LIB_EXPRESSION_MATHEMATIQUE__
#include "ExpressionMathematique.h"

/**
 * \fn expressionMathematiqueEnChaine(EM_ExpressionMathematique exp)
 * \brief Permet de repr�senter une expression math�matique en cha�ne de caract�res
 * \attention L'espace m�moire pour stocker la cha�ne est allou� par la fonction
 */
char* expressionMathematiqueEnChaine(EM_ExpressionMathematique exp);

/**
 * \fn EM_ExpressionMathematique calculerDerivee(EM_ExpressionMathematique exp, char* variable)
 * \brief Permet de calculer la d�riv�e d'une expression math�matique
 * \attention Aucune simlpification n'est faite
 */
EM_ExpressionMathematique calculerDerivee(EM_ExpressionMathematique exp, char* variable);

/**
 * \fn EM_ExpressionMathematique simplifier(EM_ExpressionMathematique exp)
 * \brief Permet de simplifier une xepression math�matique
 */
EM_ExpressionMathematique simplifier(EM_ExpressionMathematique exp);
#endif

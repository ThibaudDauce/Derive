/**
 * \file libExpressionMathematique.h
 * \brief Implantation d'une librairie sur les expressions ariméthiques
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
 * \brief Permet de représenter une expression mathématique en chaîne de caractères
 * \attention L'espace mémoire pour stocker la chaîne est alloué par la fonction
 */
char* expressionMathematiqueEnChaine(EM_ExpressionMathematique exp);

/**
 * \fn EM_ExpressionMathematique calculerDerivee(EM_ExpressionMathematique exp, char* variable)
 * \brief Permet de calculer la dérivée d'une expression mathématique
 * \attention Aucune simlpification n'est faite
 */
EM_ExpressionMathematique calculerDerivee(EM_ExpressionMathematique exp, char* variable);

/**
 * \fn EM_ExpressionMathematique simplifier(EM_ExpressionMathematique exp)
 * \brief Permet de simplifier une xepression mathématique
 */
EM_ExpressionMathematique simplifier(EM_ExpressionMathematique exp);
#endif

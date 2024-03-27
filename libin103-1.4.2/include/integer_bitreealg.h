/*! \file integer_bitreealg.h
 *
 * \brief Fonctions de parcours d'arbres binaires
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------ traverse.h ------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef integer_BITREEALG_H
#define integer_BITREEALG_H

#include "integer_bitree.h"
#include "integer_list.h"

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/


/*! \brief Parcours d'arbre binaire suivant l'ordre préfixe
 *
 * Fonction récursive qui parcours l'arbre binaire dans l'ordre préfixe
 * 1. Stock la valeur du noeud dans la liste
 * 2. Appel récursif sur fils gauche si non NULL
 * 3. Appel récursif sur fils droit si non NULL
 *
 * @param node pointeur vers la racine de l'arbre
 *
 * @param list liste chaînée des valeurs des noeuds de l'arbre dans
 * l'ordre du parcours
 *
 * @return valeur entière indiquant si tout s'est bien passé (0 pour
 * ok, -1 pour erreur)
 */
int integer_preorder(integer_bitreenode_t *node, integer_list_t *list);

/*! \brief Parcours d'arbre binaire suivant l'ordre infixe
 *
 * Fonction récursive qui parcours l'arbre binaire dans l'ordre infixe
 * 1. Appel récursif sur fils gauche si non NULL
 * 2. Stock la valeur du noeud dans la liste
 * 3. Appel récursif sur fils droit si non NULL
 *
 * @param node pointeur vers la racine de l'arbre
 *
 * @param list liste chaînée des valeurs des noeuds de l'arbre dans
 * l'ordre du parcours
 *
 * @return valeur entière indiquant si tout s'est bien passé (0 pour
 * ok, -1 pour erreur)
 */
int integer_inorder(integer_bitreenode_t *node, integer_list_t *list);

/*! \brief Parcours d'arbre binaire suivant l'ordre postfixe
 *
 * Fonction récursive qui parcours l'arbre binaire dans l'ordre postfixe
 * 1. Appel récursif sur fils gauche si non NULL
 * 2. Appel récursif sur fils droit si non NULL
 * 3. Stock la valeur du noeud dans la liste
 *
 * @param node pointeur vers la racine de l'arbre
 *
 * @param list liste chaînée des valeurs des noeuds de l'arbre dans
 * l'ordre du parcours
 *
 * @return valeur entière indiquant si tout s'est bien passé (0 pour
 * ok, -1 pour erreur)
 */
int integer_postorder(integer_bitreenode_t *node, integer_list_t *list);

#endif

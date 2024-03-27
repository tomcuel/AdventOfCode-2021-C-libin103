/*! \file real_stack.h
 * \brief Pile (FILO) contenant des valeurs de type <b> double </b>
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- stack.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef _real_STACK_H

#define _real_STACK_H


#include <stdlib.h>

#include "real_list.h"

/*****************************************************************************
*                                                                            *
*  Implement stacks as linked lists.                                         *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter une pile contenant des
    valeurs de type <b> double </b>
 *
 * Une pile est une liste chaînée gérée de manière adéquate: insertion
 * en tête et suppression en tête.
 *
 */
typedef real_list_t real_stack_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

/*! \brief Initialisation d'une nouvelle pile contenant des valeurs de
    type <b> double </b>
 *
 * Utilise la fonction d'initalisation des listes chaînée pour mettre
 * à zéro la taille et à NULL les pointeurs vers le premier et le
 * dernier élément de la liste, i.e., de la pile.
 *
 * @param stack est un pointeur vers la structure de données des piles
 * real_stack_t
 */
void real_stack_init (real_stack_t* stack);

/*! \brief Destruction d'une pile
 *
 * Utilise la fonction de destruction des listes chaînées pour
 * parcourir la liste et détruire tous les éléments de la pile.
 *
 * @param stack est un pointeur vers la structure de données des piles
 * real_stack_t
 */
void real_stack_destroy (real_stack_t *stack);

/*! \brief Accesseur sur la taille d'une pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), retourne la valeur du champ size
 *
 * @param stack est un pointeur vers la structure de données real_stack_t
 *
 * @return un entier indiquant la taille de la pile
 */
int real_stack_size (real_stack_t * stack);

/*! \brief Ajouter un élément de type <b>double</b> sur la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée) et une valeur de type <b>double</b>, ajoute un nouvel
 * élément à la pile (en "haut" de la pile) avec cette valeur
 *
 * @param stack est un pointeur vers la structure de données
 * real_stack_t
 *
 * @pram data une valeur de type <b>double</b> à ajouter à la pile
 *
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et
 * -1 en cas de problème mémoire)
 */
int real_stack_push(real_stack_t *stack, double data);

/*! \brief Supprime un élément de type <b>double</b> du haut de la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), supprime l'élément en haut de la pile (le dernier à avoir
 * été inséré)
 *
 * @param stack est un pointeur vers la structure de données
 * real_stack_t
 *
 * @pram data un pointeur sur type <b>double</b> qui permet de
 * récupérer la valeur de l'élément supprimer de la pile
 *
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et
 * -1 en cas de problème mémoire)
 *
 */
int real_stack_pop(real_stack_t *stack, double* data);

/*! \brief Récupère la valeur de type <b>double</b> du haut de la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), récupère la valeur de l'élément au dessus de la pile sans le supprimer.
 *
 * @param stack est un pointeur vers la structure de données real_stack_t
 * @return une valeur de <b>double</b> de l'élément en haut de la pile.
 */
double real_stack_peek(real_stack_t * stack);
#endif

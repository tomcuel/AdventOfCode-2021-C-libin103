/*! \file integer_stack.h
 * \brief Pile (FILO) contenant des valeurs de type <b> int </b>
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- stack.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef _integer_STACK_H

#define _integer_STACK_H


#include <stdlib.h>

#include "integer_list.h"

/*****************************************************************************
*                                                                            *
*  Implement stacks as linked lists.                                         *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter une pile contenant des
    valeurs de type <b> int </b>
 *
 * Une pile est une liste chaînée gérée de manière adéquate: insertion
 * en tête et suppression en tête.
 *
 */
typedef integer_list_t integer_stack_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

/*! \brief Initialisation d'une nouvelle pile contenant des valeurs de
    type <b> int </b>
 *
 * Utilise la fonction d'initalisation des listes chaînée pour mettre
 * à zéro la taille et à NULL les pointeurs vers le premier et le
 * dernier élément de la liste, i.e., de la pile.
 *
 * @param stack est un pointeur vers la structure de données des piles
 * integer_stack_t
 */
void integer_stack_init (integer_stack_t* stack);

/*! \brief Destruction d'une pile
 *
 * Utilise la fonction de destruction des listes chaînées pour
 * parcourir la liste et détruire tous les éléments de la pile.
 *
 * @param stack est un pointeur vers la structure de données des piles
 * integer_stack_t
 */
void integer_stack_destroy (integer_stack_t *stack);

/*! \brief Accesseur sur la taille d'une pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), retourne la valeur du champ size
 *
 * @param stack est un pointeur vers la structure de données integer_stack_t
 *
 * @return un entier indiquant la taille de la pile
 */
int integer_stack_size (integer_stack_t * stack);

/*! \brief Ajouter un élément de type <b>int</b> sur la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée) et une valeur de type <b>int</b>, ajoute un nouvel
 * élément à la pile (en "haut" de la pile) avec cette valeur
 *
 * @param stack est un pointeur vers la structure de données
 * integer_stack_t
 *
 * @pram data une valeur de type <b>int</b> à ajouter à la pile
 *
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et
 * -1 en cas de problème mémoire)
 */
int integer_stack_push(integer_stack_t *stack, int data);

/*! \brief Supprime un élément de type <b>int</b> du haut de la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), supprime l'élément en haut de la pile (le dernier à avoir
 * été inséré)
 *
 * @param stack est un pointeur vers la structure de données
 * integer_stack_t
 *
 * @pram data un pointeur sur type <b>int</b> qui permet de
 * récupérer la valeur de l'élément supprimer de la pile
 *
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et
 * -1 en cas de problème mémoire)
 *
 */
int integer_stack_pop(integer_stack_t *stack, int* data);

/*! \brief Récupère la valeur de type <b>int</b> du haut de la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), récupère la valeur de l'élément au dessus de la pile sans le supprimer.
 *
 * @param stack est un pointeur vers la structure de données integer_stack_t
 * @return une valeur de <b>int</b> de l'élément en haut de la pile.
 */
int integer_stack_peek(integer_stack_t * stack);
#endif

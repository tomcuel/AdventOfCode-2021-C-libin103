/*! \file character_stack.h
 * \brief Pile (FILO) contenant des valeurs de type <b> char </b>
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- stack.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef _character_STACK_H

#define _character_STACK_H


#include <stdlib.h>

#include "character_list.h"

/*****************************************************************************
*                                                                            *
*  Implement stacks as linked lists.                                         *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter une pile contenant des
    valeurs de type <b> char </b>
 *
 * Une pile est une liste chaînée gérée de manière adéquate: insertion
 * en tête et suppression en tête.
 *
 */
typedef character_list_t character_stack_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

/*! \brief Initialisation d'une nouvelle pile contenant des valeurs de
    type <b> char </b>
 *
 * Utilise la fonction d'initalisation des listes chaînée pour mettre
 * à zéro la taille et à NULL les pointeurs vers le premier et le
 * dernier élément de la liste, i.e., de la pile.
 *
 * @param stack est un pointeur vers la structure de données des piles
 * character_stack_t
 */
void character_stack_init (character_stack_t* stack);

/*! \brief Destruction d'une pile
 *
 * Utilise la fonction de destruction des listes chaînées pour
 * parcourir la liste et détruire tous les éléments de la pile.
 *
 * @param stack est un pointeur vers la structure de données des piles
 * character_stack_t
 */
void character_stack_destroy (character_stack_t *stack);

/*! \brief Accesseur sur la taille d'une pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), retourne la valeur du champ size
 *
 * @param stack est un pointeur vers la structure de données character_stack_t
 *
 * @return un entier indiquant la taille de la pile
 */
int character_stack_size (character_stack_t * stack);

/*! \brief Ajouter un élément de type <b>char</b> sur la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée) et une valeur de type <b>char</b>, ajoute un nouvel
 * élément à la pile (en "haut" de la pile) avec cette valeur
 *
 * @param stack est un pointeur vers la structure de données
 * character_stack_t
 *
 * @pram data une valeur de type <b>char</b> à ajouter à la pile
 *
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et
 * -1 en cas de problème mémoire)
 */
int character_stack_push(character_stack_t *stack, char data);

/*! \brief Supprime un élément de type <b>char</b> du haut de la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), supprime l'élément en haut de la pile (le dernier à avoir
 * été inséré)
 *
 * @param stack est un pointeur vers la structure de données
 * character_stack_t
 *
 * @pram data un pointeur sur type <b>char</b> qui permet de
 * récupérer la valeur de l'élément supprimer de la pile
 *
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et
 * -1 en cas de problème mémoire)
 *
 */
int character_stack_pop(character_stack_t *stack, char* data);

/*! \brief Récupère la valeur de type <b>char</b> du haut de la pile
 *
 * Etant donné un pointeur vers une pile (représentée par une liste
 * chaînée), récupère la valeur de l'élément au dessus de la pile sans le supprimer.
 *
 * @param stack est un pointeur vers la structure de données character_stack_t
 * @return une valeur de <b>char</b> de l'élément en haut de la pile.
 */
char character_stack_peek(character_stack_t * stack);
#endif

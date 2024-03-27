/*! \file character_queue.h
 * \brief File (FIFO) contenant des valeurs de type <b> char </b>
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- queue.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef _character_QUEUE_H
#define _character_QUEUE_H

#include <stdlib.h>

#include "character_list.h"

/*****************************************************************************
*                                                                            *
*  Implement queues as linked lists.                                         *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter une file contenant des
    valeurs de type <b> char </b>
 *
 * Une file est une liste chaînée gérée de manière adéquate: insertion
 * en tête et suppression en queue.
 *
 */
typedef character_list_t character_queue_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/


/*! \brief Initialisation d'une nouvelle file contenant des valeurs de
    type <b> char </b>
 *
 * Utilise la fonction d'initalisation des listes chaînée pour mettre
 * à zéro la taille et à NULL les pointeurs vers le premier et le
 * dernier élément de la liste, i.e., de la file.
 *
 * @param queue est un pointeur vers la structure de données des files
 * character_queue_t
 */
void character_queue_init (character_queue_t* queue);

/*! \brief Destruction d'une file
 *
 * Utilise la fonction de destruction des listes chaînées pour
 * parcourir la liste et détruire tous les éléments de la file.
 *
 * @param queue est un pointeur vers la structure de données des piles
 * character_queue_t
 */
void character_queue_destroy (character_queue_t* queue);

/*! \brief Accesseur sur la taille d'une file
 *
 * Etant donné un pointeur vers une file (représentée par une liste chaînée), retourne la valeur du champ size
 *
 * @param queue est un pointeur vers la structure de données character_queue_t
 * @return un entier indiquant la taille de la file
 */
int character_queue_size (character_queue_t* queue);

/*! \brief Ajouter un élément de type <b>char</b> dans la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée) et une valeur de type <b>char</b>, ajoute un nouvel
 * élément à la file avec cette valeur.
 *
 * @param queue est un pointeur vers la structure de données character_queue_t
 * @pram data une valeur de type <b>char</b> à ajouter à la file
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème mémoire)
 */
int character_queue_enqueue(character_queue_t* queue, char data);

/*! \brief Supprime un élément de type <b>char</b> dans la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée), supprime l'élément le plus ancien de la file.
 *
 * @param queue est un pointeur vers la structure de données character_queue_t
 * @pram data un pointeur sur type <b>char</b> qui permet de récupérer la valeur de l'élément supprimer de la file
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème mémoire)
 */
int character_queue_dequeue(character_queue_t* queue, char* data);

/*! \brief Récupère la valeur de type <b>char</b> le plus ancien de la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée), récupère la valeur de l'élément le plus ancien de la file
 * sans le supprimer.
 *
 * @param queue est un pointeur vers la structure de données character_queue_t
 * @return une valeur de <b>char</b> de l'élément le plus ancien de la file
 */
char character_queue_peek(character_queue_t* queue);

#endif

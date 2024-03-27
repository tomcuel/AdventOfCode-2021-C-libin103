/*! \file integer_queue.h
 * \brief File (FIFO) contenant des valeurs de type <b> int </b>
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- queue.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef _integer_QUEUE_H
#define _integer_QUEUE_H

#include <stdlib.h>

#include "integer_list.h"

/*****************************************************************************
*                                                                            *
*  Implement queues as linked lists.                                         *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter une file contenant des
    valeurs de type <b> int </b>
 *
 * Une file est une liste chaînée gérée de manière adéquate: insertion
 * en tête et suppression en queue.
 *
 */
typedef integer_list_t integer_queue_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/


/*! \brief Initialisation d'une nouvelle file contenant des valeurs de
    type <b> int </b>
 *
 * Utilise la fonction d'initalisation des listes chaînée pour mettre
 * à zéro la taille et à NULL les pointeurs vers le premier et le
 * dernier élément de la liste, i.e., de la file.
 *
 * @param queue est un pointeur vers la structure de données des files
 * integer_queue_t
 */
void integer_queue_init (integer_queue_t* queue);

/*! \brief Destruction d'une file
 *
 * Utilise la fonction de destruction des listes chaînées pour
 * parcourir la liste et détruire tous les éléments de la file.
 *
 * @param queue est un pointeur vers la structure de données des piles
 * integer_queue_t
 */
void integer_queue_destroy (integer_queue_t* queue);

/*! \brief Accesseur sur la taille d'une file
 *
 * Etant donné un pointeur vers une file (représentée par une liste chaînée), retourne la valeur du champ size
 *
 * @param queue est un pointeur vers la structure de données integer_queue_t
 * @return un entier indiquant la taille de la file
 */
int integer_queue_size (integer_queue_t* queue);

/*! \brief Ajouter un élément de type <b>int</b> dans la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée) et une valeur de type <b>int</b>, ajoute un nouvel
 * élément à la file avec cette valeur.
 *
 * @param queue est un pointeur vers la structure de données integer_queue_t
 * @pram data une valeur de type <b>int</b> à ajouter à la file
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème mémoire)
 */
int integer_queue_enqueue(integer_queue_t* queue, int data);

/*! \brief Supprime un élément de type <b>int</b> dans la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée), supprime l'élément le plus ancien de la file.
 *
 * @param queue est un pointeur vers la structure de données integer_queue_t
 * @pram data un pointeur sur type <b>int</b> qui permet de récupérer la valeur de l'élément supprimer de la file
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème mémoire)
 */
int integer_queue_dequeue(integer_queue_t* queue, int* data);

/*! \brief Récupère la valeur de type <b>int</b> le plus ancien de la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée), récupère la valeur de l'élément le plus ancien de la file
 * sans le supprimer.
 *
 * @param queue est un pointeur vers la structure de données integer_queue_t
 * @return une valeur de <b>int</b> de l'élément le plus ancien de la file
 */
int integer_queue_peek(integer_queue_t* queue);

#endif

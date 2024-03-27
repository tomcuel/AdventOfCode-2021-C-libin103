/*! \file real_queue.h
 * \brief File (FIFO) contenant des valeurs de type <b> double </b>
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- queue.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef _real_QUEUE_H
#define _real_QUEUE_H

#include <stdlib.h>

#include "real_list.h"

/*****************************************************************************
*                                                                            *
*  Implement queues as linked lists.                                         *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter une file contenant des
    valeurs de type <b> double </b>
 *
 * Une file est une liste chaînée gérée de manière adéquate: insertion
 * en tête et suppression en queue.
 *
 */
typedef real_list_t real_queue_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/


/*! \brief Initialisation d'une nouvelle file contenant des valeurs de
    type <b> double </b>
 *
 * Utilise la fonction d'initalisation des listes chaînée pour mettre
 * à zéro la taille et à NULL les pointeurs vers le premier et le
 * dernier élément de la liste, i.e., de la file.
 *
 * @param queue est un pointeur vers la structure de données des files
 * real_queue_t
 */
void real_queue_init (real_queue_t* queue);

/*! \brief Destruction d'une file
 *
 * Utilise la fonction de destruction des listes chaînées pour
 * parcourir la liste et détruire tous les éléments de la file.
 *
 * @param queue est un pointeur vers la structure de données des piles
 * real_queue_t
 */
void real_queue_destroy (real_queue_t* queue);

/*! \brief Accesseur sur la taille d'une file
 *
 * Etant donné un pointeur vers une file (représentée par une liste chaînée), retourne la valeur du champ size
 *
 * @param queue est un pointeur vers la structure de données real_queue_t
 * @return un entier indiquant la taille de la file
 */
int real_queue_size (real_queue_t* queue);

/*! \brief Ajouter un élément de type <b>double</b> dans la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée) et une valeur de type <b>double</b>, ajoute un nouvel
 * élément à la file avec cette valeur.
 *
 * @param queue est un pointeur vers la structure de données real_queue_t
 * @pram data une valeur de type <b>double</b> à ajouter à la file
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème mémoire)
 */
int real_queue_enqueue(real_queue_t* queue, double data);

/*! \brief Supprime un élément de type <b>double</b> dans la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée), supprime l'élément le plus ancien de la file.
 *
 * @param queue est un pointeur vers la structure de données real_queue_t
 * @pram data un pointeur sur type <b>double</b> qui permet de récupérer la valeur de l'élément supprimer de la file
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème mémoire)
 */
int real_queue_dequeue(real_queue_t* queue, double* data);

/*! \brief Récupère la valeur de type <b>double</b> le plus ancien de la file
 *
 * Etant donné un pointeur vers une file (représentée par une liste
 * chaînée), récupère la valeur de l'élément le plus ancien de la file
 * sans le supprimer.
 *
 * @param queue est un pointeur vers la structure de données real_queue_t
 * @return une valeur de <b>double</b> de l'élément le plus ancien de la file
 */
double real_queue_peek(real_queue_t* queue);

#endif

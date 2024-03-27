/*! \file character_set.h
 * \brief Ensemble contenant des valeurs de type <b> char </b>
 *
 */

/*****************************************************************************
*                                                                            *
*  -------------------------------- set.h ---------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef character_SET_H
#define character_SET_H

#include <stdlib.h>
#include <stdbool.h>

#include "character_list.h"

/*****************************************************************************
*                                                                            *
*  Implement sets as linked lists.                                           *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter un ensemble contenant des
    valeurs de type <b> char </b>
 *
 * Un ensemble est une liste chaînée gérée de manière adéquate:
 * insertion en queue de liste avec un maintien de la propriété
 * d'unicité des éléments dans l'ensemble.
 *
 */
typedef character_list_t character_set_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

/*! \brief Initialisation d'un nouvel ensemble contenant des valeurs
    de type <b> char </b>
 *
 * Utilise la fonction d'initalisation des listes chaînée pour mettre
 * à zéro la taille et à NULL les pointeurs vers le premier et le
 * dernier élément de la liste, i.e., de l'ensemble
 *
 * @param set est un pointeur vers la structure de données des ensembles
 * character_set_t
 */
void character_set_init(character_set_t *set);

/*! \brief Destruction d'un ensemble
 *
 * Utilise la fonction de destruction des listes chaînées pour
 * parcourir la liste et détruire tous les éléments de l'ensemble.
 *
 * @param set est un pointeur vers la structure de données des ensembles
 * character_set_t
 */
void character_set_destroy (character_set_t *set);

/*! \brief Ajouter un élément de type <b>char</b> dans l'ensemble
 *
 * Etant donné un pointeur vers un ensemble (représenté par une liste
 * chaînée) et une valeur de type <b>char</b>, ajoute un nouvel
 * élément à l'ensemble avec cette valeur en maintenant l'unicité de
 * la valeur dans l'ensemble.
 *
 * @param set est un pointeur vers la structure de données character_set_t
 * @pram data une valeur de type <b>char</b> à ajouter à la file
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème mémoire)
 */
int character_set_insert(character_set_t *set, char data);

/*! \brief Supprimer un élément de type <b>char</b> dans l'ensemble
 *
 * Etant donné un pointeur vers un ensemble (représenté par une liste
 * chaînée) et un pointeur vers une valeur de type <b>char</b>,
 * supprime l'élément de l'ensemble.
 *
 * @param set est un pointeur vers la structure de données character_set_t
 * @pram data est pointeur vers une variable de type <b>char</b> qui représente la valeur à supprimer
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème mémoire)
 */
int character_set_remove(character_set_t *set, char *data);

/*! \brief Union de deux ensembles
 *
 * Etant donné un pointeur vers un ensemble et un pointeur vers un
 * autre ensemble, crée un troisième ensemble représentant l'union des
 * deux ensembles
 *
 * @param setu l'ensemble résultat de l'union de type character_set_t
 * @param set1 premier argument de l'opération d'union de type character_set_t
 * @param set2 second argument de l'opération d'union de type character_set_t
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème)
 */
int character_set_union(character_set_t *setu, const character_set_t *set1,
    const character_set_t *set2);

/*! \brief Intersection de deux ensembles
 *
 * Etant donné un pointeur vers un ensemble et un pointeur vers un
 * autre ensemble, crée un troisième ensemble représentant l'intersection des
 * deux ensembles
 *
 * @param seti l'ensemble résultat de l'intersection de type character_set_t
 * @param set1 premier argument de l'opération d'union de type character_set_t
 * @param set2 second argument de l'opération d'union de type character_set_t
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème)
 */
int character_set_intersection(character_set_t *seti, const character_set_t *set1,
    const character_set_t *set2);

/*! \brief Différence de deux ensembles
 *
 * Etant donné un pointeur vers un ensemble et un pointeur vers un
 * autre ensemble, crée un troisième ensemble représentant la
 * différence des deux ensembles, i.e., l'ensemble des éléments
 * appartenant au premier ensemble et pas au second.
 *
 * @param setd l'ensemble résultat de la différence de type character_set_t
 * @param set1 premier argument de l'opération d'union de type character_set_t
 * @param set2 second argument de l'opération d'union de type character_set_t
 * @return un entier indiquant si tout s'est bien passé (0 pour OK, et -1 en cas de problème)
 */
int character_set_difference(character_set_t *setd, const character_set_t *set1,
    const character_set_t *set2);

/*! \brief Fonction testant l'appartenance d'une valeur à un ensemble
 *
 * Etant donné un pointeur vers un ensemble et une valeur indique si
 * cette valeur est dans l'ensembe ou non
 *
 * @param set ensemble de type character_set_t
 * @param data valeur de type <b>char</b> que l'on souhaite tester la présence dans set
 * @return une valeur booléenne indiquant data appartient à l'ensemble set
 */
bool character_set_is_member(const character_set_t *set, char data);

/*! \brief Fonction testant si un ensemble est sous-ensemble d'un autre
 *
 * Etant donné un pointeur vers un ensemble et un pointeur vers un
 * second ensemble indique si le premier ensemble est inclus dans le
 * second, i.e., tous les élements du premier ensemble sont dans le
 * second.
 *
 * @param set1 ensemble de type character_set_t
 * @param set2 ensemble de type character_set_t
 * @return une valeur booléenne indiquant si set1 est inclus dans set2
 */
bool character_set_is_subset(const character_set_t *set1, const character_set_t *set2);

/*! \brief Fonction testant si un ensemble est égale à un autre
 *
 * Etant donné un pointeur vers un ensemble et un pointeur vers un
 * second ensemble indique si le premier ensemble est égale au second,
 * i.e., tous les élements du premier ensemble sont dans le second et
 * réciproquement
 *
 * @param set1 ensemble de type character_set_t
 * @param set2 ensemble de type character_set_t
 * @return une valeur booléenne indiquant si set1 est égale à set2
 */
bool character_set_is_equal(const character_set_t *set1, const character_set_t *set2);

/*! \brief Accesseur sur la taille d'un ensemble
 *
 * Etant donné un pointeur vers un ensemble (représentée par une liste
 * chaînée), retourne la valeur du champ size
 *
 * @param set est un pointeur vers la structure de données
 * character_set_t
 *
 * @return un entier indiquant la taille (i.e., le nombre d'éléments)
 * de l'ensemble
 */
int character_set_size(const character_set_t *set);

#endif

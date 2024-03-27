/*! \file real_heap.h
 *
 * \brief structure de données tas contenant des valeurs de type <b>
 * double </b>. Le tas peut être configuré pour être tas-min ou
 * tas-max.
 *
 */

/*****************************************************************************
*                                                                            *
*  -------------------------------- heap.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef real_HEAP_H
#define real_HEAP_H

/*****************************************************************************
*                                                                            *
*  Define a structure for heaps.                                             *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter le drapeau pour choisir un
 *    tas-min ou un tas-max avec des données de type <b>double</b>
 */
typedef enum real_heap_type_ {
  real_MAX_HEAP, /**< drapeau pour créer un tas-max */
    real_MIN_HEAP /**< drapeau pour créer un tas-min */
    } real_heap_type_t;

/*! \brief Type de données pour représenter un tas contenant des
 *  valeurs de type <b> double </b>
 *
 * Un tas est une strcture arborescente représentée par un tableau
 * dont les valeurs sont de type <b> double </b>. Le tableau change de
 * taille automatiquement pour stocker plus ou moins de valeurs.
 */
typedef struct real_heap_ {
  int size; /**< nombre d'éléments dans le tableau */
  real_heap_type_t heap_type; /**< drapeau pour indiquer si on a un tas-min ou un tas-max */
  double *tree; /**< tableau représentant le tas */
} real_heap_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

/*! \brief Initialisation d'un nouveau tas
 *
 * Met à zéro la taille et à NULL le pointeur vers le tableau
 * représentant le tas
 *
 * @param heap est un pointeur vers la structure de données de tas
 * real_heap_t
 * @param heap_type drapeau indiquant si heap sera un tas-min ou un tas-max
 */
void real_heap_init(real_heap_t *heap, real_heap_type_t heap_type);

/*! \brief Destruction d'un tas
 *
 * Met à zéro la taille et désalloue le tableau représentant le tas
 *
 * @param heap est un pointeur vers la structure de données de tas
 * real_heap_t
 */
void real_heap_destroy(real_heap_t *heap);

/*! \brief Insertion d'un nouvel élément dans le tas
 *
 * Augmente la taille du tableau pour ajouter un nouvel élément. Puis,
 * à partir du nouvel élément remonte jusqu'à la racine en faisant des
 * permutations pour maintenir la propriété de tas-min ou tas-max
 *
 * @param heap est un pointeur vers la structure de données de tas
 * real_heap_t
 *
 * @param data valeur de type <b>double</b> à ajouter dans le tas
 *
 * @return un entier indiquant si tout s'est bien passé (0 pour ok, -1
 * pour problème)
 */
int real_heap_insert(real_heap_t *heap, double data);

/*! \brief Extraction du plus petit (tas-min) ou du plus grand
 *  (tas-max) élément contenu dans le tas, i.e., à la racine.
 *
 * Affecte au paramètre data, la valeur du premier élément du
 * tableau. Echange la valeur du dernier élément avec la racine, puis
 * réduit la taille du tableau et descent de la racine jusqu'à une
 * feuille en faisant des permutations pour maintenir la propriété de
 * tas-min ou tas-max.
 *
 * @param heap est un pointeur vers la structure de données de tas
 * real_heap_t
 *
 * @param data valeur de type <b>double</b> de la valeur extraite du tas
 *
 * @return un entier indiquant si tout s'est bien passé (0 pour ok, -1
 * pour problème)
 */
int real_heap_extract(real_heap_t *heap, double *data);

/*! \brief Accesseur pour récupérer le nombre d'éléments dans le tas
 *
 * @param heap est un pointeur vers la structure de données de tas
 * real_heap_t
 *
 * @return le nombre d'éléments dans le tas
 */
int real_heap_size(real_heap_t *heap);

#endif

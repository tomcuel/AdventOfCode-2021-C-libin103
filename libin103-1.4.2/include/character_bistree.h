/*! \file character_bistree.h
 *
 * \brief Structure de données d'arbres binaires de recherche
 * équilibrés contenant des valeurs de type <b> char </b>.
 *
 * Les arbres binaires de recherche équilibrés sont mis en oeuvre à
 * partir des arbres binaires dans leur version générique (avec des
 * type <b>void*</b>). Pour cette mise en oeuvre une structure de
 * données représentant des valeurs à stocker dans l'arbre binaire est
 * définie.
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- bistree.h ------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef character_BISTREE_H
#define character_BISTREE_H

#include <stdbool.h>
#include "bitree.h"

/*****************************************************************************
*                                                                            *
*  Define balance factors for AVL trees.                                     *
*                                                                            *
*****************************************************************************/

/*! Etiquette pour indiquer qu'un noeud a un sous-arbre gauche plus
    haut que le sous arbre droit */
#define character_AVL_LFT_HEAVY         1
/*! Etiquette pour indiquer qu'noeud a ses deux sous arbres de meme
    hauteur */
#define character_AVL_BALANCED          0
/*! Etiquette pour indiquer qu'un noeud a un sous-arbre droit plus
    haut que le sous arbre guache */
#define character_AVL_RGT_HEAVY        -1

/*****************************************************************************
*                                                                            *
*  Define a structure for nodes in AVL trees.                                *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter l'information stockée dans
 * un noeud d'un arbre binaire
 *
 * Cette structure de données contient la valeur de type <b>char</b>
 * à stocker ainsi que des informations servant à équilibrer l'arbre
 * binaire de recherche au besoin et une étiquette utilisée pour
 * améliorer les performances de l'opération de suppression.
 */
typedef struct character_avlnode_t {
  char data; /**< valeur à stocker <b> char </b> */
  int hidden; /**< étiquette indiquant si le noeud est caché ou non
                  (utile pour la suppression) */
  int factor; /**< étiquette indiquant l'équilibrage des sous arbres
		 gauche et droit du noeud */
} character_avlnode_t;

/*****************************************************************************
*                                                                            *
*  Implement binary search trees as binary trees.                            *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter arbre binaire de recherche
 * équilibrée
 *
 * Ce type est un arbre binaire générique avec des opérations
 * d'insertion et de suppression adaptée pour maintenir l'équilibrage
 * de l'arbre.
 */
typedef generic_bitree_t character_bistree_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

/*! \brief Initialisation d'un nouvel arbre binaire de recherche équilibré
 *
 * Met à zéro la taille et à NULL le pointeur vers la racine
 *
 * @param tree est un pointeur vers la structure de données
 * character_bistree_t
 */
void character_bistree_init(character_bistree_t *tree);

/*! \brief Destruction d'un arbre binaire de recherche équilibré
 *
 * Met à zéro la taille et à NULL le pointeur vers la racine après
 * avoir parcourus l'arbre pour détruire chaque noeud
 *
 * @param tree est un pointeur vers la structure de données
 * character_bistree_t
 */
void character_bistree_destroy(character_bistree_t *tree);

/*! \brief Insertion d'une nouvelle valeur dans un arbre binaire de
 *    recherche équilibré
 *
 * Cette fonction crée un nouveau noeud avec la données et réalise des
 * opérations d'équilibrage (rotations) de la structure de données
 * arbres binaires de recherche au besoin.
 *
 * @param tree est un pointeur vers la structure de données
 * character_bistree_t
 *
 * @param data la valeur de type <b>char</b> à ajouter
 *
 * @return valeur entière indiquant si tout s'est bien passé (0 pour
 * ok, -1 pour erreur)
 */
int character_bistree_insert(character_bistree_t *tree, char data);

/*! \brief Suppression d'une valeur dans un arbre binaire de recherche
 *    équilibré
 *
 * Cette fonction ne supprime pas le noeud associé à la données
 * supprimée mais le cache seulement grâce à l'étiquette
 * hidden. Optimisation pour ne pas réaliser d'opération d'équilibrage
 * après suppression.
 *
 * @param tree est un pointeur vers la structure de données
 * character_bistree_t
 *
 * @param data la valeur de type <b>char</b> à supprimer.
 *
 * @return valeur entière indiquant si tout s'est bien passé (0 pour
 * ok, -1 pour erreur)
 */
int character_bistree_remove(character_bistree_t *tree, char data);

/*! \brief Test la présence d'une valeur dans l'arbre binaire de
    recherche équilibré
 *
 * @param tree est un pointeur vers la structure de données
 * character_bistree_t
 *
 * @param data la valeur de type <b>char</b> cherchée
 *
 * @return valeur booléenne indiquant si data est présent dans tree ou
 * non
 */
bool character_bistree_lookup(character_bistree_t *tree, char data);

/*! \brief Accesseur donnant la taille de l'arbre binaire de recherche
 *  équillibré
 *
 * La taille correspond au nombre de valeurs stockées dans l'arbre
 *
 * @param tree est un pointeur vers la structure de données
 * character_bistree_t
 *
 * @return valeur entière donnant le nombre de valeurs stockées dans
 * l'arbre
 */
int character_bistree_size(character_bistree_t *tree);

#endif

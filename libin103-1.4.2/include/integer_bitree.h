/*! \file integer_bitree.h
 *
 * \brief Structure de données d'arbre binaire contenant des valeurs
 * de type <b> int </b>.
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- bitree.h -------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef integer_BITREE_H
#define integer_BITREE_H

#include <stdlib.h>
#include <stdbool.h>

/*****************************************************************************
*                                                                            *
*  Define a structure for binary tree nodes.                                 *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour un noeud de l'arbre binaire
 *  stockant des valeurs de type <b> int </b>
 */
typedef struct integer_bitreenode_t {
  int data;  /**< valeur stockée  */
  struct integer_bitreenode_t *left;  /**< pointeur vers fils gauche */
  struct integer_bitreenode_t *right;  /**< pointeur vers fils droit */
} integer_bitreenode_t;

/*****************************************************************************
*                                                                            *
*  Define a structure for binary trees.                                      *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour l'arbre binaire
 */
typedef struct integer_bitree_t {
  int size; /**< nombre de noeud dans l'arbre */
  integer_bitreenode_t *root; /**< pointeur vers la racine */
} integer_bitree_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

/*! \brief Initialisation d'un nouvel arbre binaire
 *
 * Met à zéro la taille et à NULL le pointeur vers la racine
 *
 * @param tree est un pointeur vers la structure de données
 * integer_bitree_t
 */
void integer_bitree_init(integer_bitree_t *tree);

/*! \brief Destruction d'un arbre binaire
 *
 * Met à zéro la taille et à NULL le pointeur vers la racine après avoir
 * parcourus l'arbre pour détruire tous les noeuds en utilisant les
 * fonctions integer_bitree_ins_left et integer_bitree_ins_right.
 *
 * @param tree est un pointeur vers la structure de données
 * integer_bitree_t contenant la racine de l'arbre
 */
void integer_bitree_destroy(integer_bitree_t *tree);

/*! \brief Insertion d'un noeud en position fils gauche dans un arbre
 *  binaire à une position donnée
 *
 * 1. On trouve la bonne position où insérer
 *    - si node == NULL alors on ajoute un fils gauche à la racine si emplacement vide autrement erreur
 *    - si node != NULL alors on ajoute un fils gauche au noeud node si emplacement vide autrement erreur
 * 2. On alloue un nouveau noeud et on y stocke la valeur de data
 *
 * @param tree est un pointeur vers la structure de données
 * integer_bitree_t contenant la racine de l'arbre
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud auquel ajouté un fils
 * gauche
 *
 * @param data la valeur à stocker dans le fils gauche créé
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int integer_bitree_ins_left(integer_bitree_t *tree,
			   integer_bitreenode_t *node, int data);

/*! \brief Insertion d'un noeud en position fils droit dans un arbre
 *  binaire à une position donnée
 *
 * 1. On trouve la bonne position où insérer
 *    - si node == NULL alors on ajoute un fils droit à la racine si emplacement vide autrement erreur
 *    - si node != NULL alors on ajoute un fils droit au noeud node si emplacement vide autrement erreur
 * 2. On alloue un nouveau noeud et on y stocke la valeur de data
 *
 * @param tree est un pointeur vers la structure de données
 * integer_bitree_t contenant la racine de l'arbre
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud auquel ajouté un fils
 * droit
 *
 * @param data la valeur à stocker dans le fils droit créé
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int integer_bitree_ins_right(integer_bitree_t *tree,
			    integer_bitreenode_t *node, int data);

/*! \brief Suppression d'un sous arbre en position fils gauche dans un
 *  arbre binaire à une position donnée
 *
 * 1. On trouve la bonne position où insérer
 *    - si node == NULL alors on supprime le sous arbre gauche de la racine
 *    - si node != NULL alors on supprime le sous arbre gauche du noeud node
 * 2. Récursion pour supprimer tous les noeuds jusqu'aux feuilles en utilisant les fonctions integer_bitree_rem_left et integer_bitree_rem_right
 *
 * @param tree est un pointeur vers la structure de données
 * integer_bitree_t contenant la racine de l'arbre
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud auquel il faut supprimer
 * le sous-arbre gauche
 */
void integer_bitree_rem_left(integer_bitree_t *tree, integer_bitreenode_t *node);

/*! \brief Suppression d'un sous arbre en position fils droit dans un
 *  arbre binaire à une position donnée
 *
 * 1. On trouve la bonne position où insérer
 *    - si node == NULL alors on supprime le sous arbre droit de la racine
 *    - si node != NULL alors on supprime le sous arbre droit du noeud node
 * 2. Récursion pour supprimer tous les noeuds jusqu'aux feuilles en utilisant les fonctions integer_bitree_rem_left et integer_bitree_rem_right
 *
 * @param tree est un pointeur vers la structure de données
 * integer_bitree_t contenant la racine de l'arbre
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud auquel il faut supprimer
 * le sous-arbre droit
 */
void integer_bitree_rem_right(integer_bitree_t *tree, integer_bitreenode_t *node);

/*! \brief Fusion de deux arbres binaires
 *
 * 1. Initialisation du nouvel arbre merge
 * 2. Insertion de la donnée data dans ce nouvel arbre (à la racine)
 * 3. Ajout d'un fils gauche avec left et d'un fils droit right
 * 4. Mise à jour de la taille du nouvel arbre
 *
 * @param merge est un pointeur vers la structure de données
 * integer_bitree_t contenant l'arbre issu de la fusion de left et right
 *
 * @param left est un pointeur vers la structure de données
 * integer_bitree_t représentant un arbre binaire qui sera en position
 * sous arbre gauche dans la fusion
 *
 * @param right est un pointeur vers la structure de données
 * integer_bitree_t représentant un arbre binaire qui sera en position
 * sous arbre droit dans la fusion
 *
 * @param data valeur de type <b>int</b> qui sera stockée à la
 * racine de l'arbre binaire issue de la fusion
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int integer_bitree_merge(integer_bitree_t *merge, integer_bitree_t *left,
			integer_bitree_t *right, int data);


/*! \brief Accesseur pour la taille de l'arbre binaire
 *
 * Donne le nombre de noeud dans l'arbre binaire
 *
 * @param tree est un pointeur vers la structure de données
 * integer_bitree_t contenant la racine de l'arbre binaire
 *
 * @return une valeur entière indiquant la taille
 */
int integer_bitree_size(integer_bitree_t *tree);

/*! \brief Accesseur pour récupérer la racine
 *
 * Donne le pointeur vers le noeud racine
 *
 * @param tree est un pointeur vers la structure de données
 * integer_bitree_t contenant la racine de l'arbre binaire
 *
 * @return le pointeur vers la structure integer_bitreenode_t associée
 * à la racine
 */
integer_bitreenode_t* integer_bitree_root(integer_bitree_t *tree);

/*! \brief Test si un noeud est la fin du branche
 *
 * Vérifie si le noeud est NULL ou pas
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud à tester
 *
 * @return la valeur booléenne indiquant si node est NULL ou pas
 */
bool integer_bitree_is_eob(integer_bitreenode_t *node);

/*! \brief Test si un noeud est une feuille
 *
 * Vérifie que le fils gauche et le fils droit d'un noeud sont NULL
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud à tester
 *
 * @return la valeur booléenne indiquant si node est une feuille ou
 * pas
 */
bool integer_bitree_is_leaf(integer_bitreenode_t *node);

/*! \brief Accesseur pour récupérer la valeur stockée dans un noeud
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud pour lequel on veut la
 * valeur
 *
 * @return la valeur de type <b>int</b> stockée dans node
 */
int integer_bitree_data(integer_bitreenode_t *node);

/*! \brief Accesseur pour récupérer le fils gauche d'un noeud
 *
 * Donne le pointeur vers le noeud fils gauche
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud pour lequel on veut le
 * fils gauche
 *
 * @return le pointeur vers la structure integer_bitreenode_t associée
 * au fils gauche
 */
integer_bitreenode_t* integer_bitree_left(integer_bitreenode_t *node);

/*! \brief Accesseur pour récupérer le fils droit d'un noeud
 *
 * Donne le pointeur vers le noeud fils droit
 *
 * @param node est un pointeur vers la structure de données
 * integer_bitreenode_t représentant le noeud pour lequel on veut le
 * fils droit
 *
 * @return le pointeur vers la structure integer_bitreenode_t associée
 * au fils droit
 */
integer_bitreenode_t* integer_bitree_right(integer_bitreenode_t *node);

#endif

/*! \file real_bitree.h
 *
 * \brief Structure de données d'arbre binaire contenant des valeurs
 * de type <b> double </b>.
 *
 */

/*****************************************************************************
*                                                                            *
*  ------------------------------- bitree.h -------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef real_BITREE_H
#define real_BITREE_H

#include <stdlib.h>
#include <stdbool.h>

/*****************************************************************************
*                                                                            *
*  Define a structure for binary tree nodes.                                 *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour un noeud de l'arbre binaire
 *  stockant des valeurs de type <b> double </b>
 */
typedef struct real_bitreenode_t {
  double data;  /**< valeur stockée  */
  struct real_bitreenode_t *left;  /**< pointeur vers fils gauche */
  struct real_bitreenode_t *right;  /**< pointeur vers fils droit */
} real_bitreenode_t;

/*****************************************************************************
*                                                                            *
*  Define a structure for binary trees.                                      *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour l'arbre binaire
 */
typedef struct real_bitree_t {
  int size; /**< nombre de noeud dans l'arbre */
  real_bitreenode_t *root; /**< pointeur vers la racine */
} real_bitree_t;

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
 * real_bitree_t
 */
void real_bitree_init(real_bitree_t *tree);

/*! \brief Destruction d'un arbre binaire
 *
 * Met à zéro la taille et à NULL le pointeur vers la racine après avoir
 * parcourus l'arbre pour détruire tous les noeuds en utilisant les
 * fonctions real_bitree_ins_left et real_bitree_ins_right.
 *
 * @param tree est un pointeur vers la structure de données
 * real_bitree_t contenant la racine de l'arbre
 */
void real_bitree_destroy(real_bitree_t *tree);

/*! \brief Insertion d'un noeud en position fils gauche dans un arbre
 *  binaire à une position donnée
 *
 * 1. On trouve la bonne position où insérer
 *    - si node == NULL alors on ajoute un fils gauche à la racine si emplacement vide autrement erreur
 *    - si node != NULL alors on ajoute un fils gauche au noeud node si emplacement vide autrement erreur
 * 2. On alloue un nouveau noeud et on y stocke la valeur de data
 *
 * @param tree est un pointeur vers la structure de données
 * real_bitree_t contenant la racine de l'arbre
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud auquel ajouté un fils
 * gauche
 *
 * @param data la valeur à stocker dans le fils gauche créé
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int real_bitree_ins_left(real_bitree_t *tree,
			   real_bitreenode_t *node, double data);

/*! \brief Insertion d'un noeud en position fils droit dans un arbre
 *  binaire à une position donnée
 *
 * 1. On trouve la bonne position où insérer
 *    - si node == NULL alors on ajoute un fils droit à la racine si emplacement vide autrement erreur
 *    - si node != NULL alors on ajoute un fils droit au noeud node si emplacement vide autrement erreur
 * 2. On alloue un nouveau noeud et on y stocke la valeur de data
 *
 * @param tree est un pointeur vers la structure de données
 * real_bitree_t contenant la racine de l'arbre
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud auquel ajouté un fils
 * droit
 *
 * @param data la valeur à stocker dans le fils droit créé
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int real_bitree_ins_right(real_bitree_t *tree,
			    real_bitreenode_t *node, double data);

/*! \brief Suppression d'un sous arbre en position fils gauche dans un
 *  arbre binaire à une position donnée
 *
 * 1. On trouve la bonne position où insérer
 *    - si node == NULL alors on supprime le sous arbre gauche de la racine
 *    - si node != NULL alors on supprime le sous arbre gauche du noeud node
 * 2. Récursion pour supprimer tous les noeuds jusqu'aux feuilles en utilisant les fonctions real_bitree_rem_left et real_bitree_rem_right
 *
 * @param tree est un pointeur vers la structure de données
 * real_bitree_t contenant la racine de l'arbre
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud auquel il faut supprimer
 * le sous-arbre gauche
 */
void real_bitree_rem_left(real_bitree_t *tree, real_bitreenode_t *node);

/*! \brief Suppression d'un sous arbre en position fils droit dans un
 *  arbre binaire à une position donnée
 *
 * 1. On trouve la bonne position où insérer
 *    - si node == NULL alors on supprime le sous arbre droit de la racine
 *    - si node != NULL alors on supprime le sous arbre droit du noeud node
 * 2. Récursion pour supprimer tous les noeuds jusqu'aux feuilles en utilisant les fonctions real_bitree_rem_left et real_bitree_rem_right
 *
 * @param tree est un pointeur vers la structure de données
 * real_bitree_t contenant la racine de l'arbre
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud auquel il faut supprimer
 * le sous-arbre droit
 */
void real_bitree_rem_right(real_bitree_t *tree, real_bitreenode_t *node);

/*! \brief Fusion de deux arbres binaires
 *
 * 1. Initialisation du nouvel arbre merge
 * 2. Insertion de la donnée data dans ce nouvel arbre (à la racine)
 * 3. Ajout d'un fils gauche avec left et d'un fils droit right
 * 4. Mise à jour de la taille du nouvel arbre
 *
 * @param merge est un pointeur vers la structure de données
 * real_bitree_t contenant l'arbre issu de la fusion de left et right
 *
 * @param left est un pointeur vers la structure de données
 * real_bitree_t représentant un arbre binaire qui sera en position
 * sous arbre gauche dans la fusion
 *
 * @param right est un pointeur vers la structure de données
 * real_bitree_t représentant un arbre binaire qui sera en position
 * sous arbre droit dans la fusion
 *
 * @param data valeur de type <b>double</b> qui sera stockée à la
 * racine de l'arbre binaire issue de la fusion
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int real_bitree_merge(real_bitree_t *merge, real_bitree_t *left,
			real_bitree_t *right, double data);


/*! \brief Accesseur pour la taille de l'arbre binaire
 *
 * Donne le nombre de noeud dans l'arbre binaire
 *
 * @param tree est un pointeur vers la structure de données
 * real_bitree_t contenant la racine de l'arbre binaire
 *
 * @return une valeur entière indiquant la taille
 */
int real_bitree_size(real_bitree_t *tree);

/*! \brief Accesseur pour récupérer la racine
 *
 * Donne le pointeur vers le noeud racine
 *
 * @param tree est un pointeur vers la structure de données
 * real_bitree_t contenant la racine de l'arbre binaire
 *
 * @return le pointeur vers la structure real_bitreenode_t associée
 * à la racine
 */
real_bitreenode_t* real_bitree_root(real_bitree_t *tree);

/*! \brief Test si un noeud est la fin du branche
 *
 * Vérifie si le noeud est NULL ou pas
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud à tester
 *
 * @return la valeur booléenne indiquant si node est NULL ou pas
 */
bool real_bitree_is_eob(real_bitreenode_t *node);

/*! \brief Test si un noeud est une feuille
 *
 * Vérifie que le fils gauche et le fils droit d'un noeud sont NULL
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud à tester
 *
 * @return la valeur booléenne indiquant si node est une feuille ou
 * pas
 */
bool real_bitree_is_leaf(real_bitreenode_t *node);

/*! \brief Accesseur pour récupérer la valeur stockée dans un noeud
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud pour lequel on veut la
 * valeur
 *
 * @return la valeur de type <b>double</b> stockée dans node
 */
double real_bitree_data(real_bitreenode_t *node);

/*! \brief Accesseur pour récupérer le fils gauche d'un noeud
 *
 * Donne le pointeur vers le noeud fils gauche
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud pour lequel on veut le
 * fils gauche
 *
 * @return le pointeur vers la structure real_bitreenode_t associée
 * au fils gauche
 */
real_bitreenode_t* real_bitree_left(real_bitreenode_t *node);

/*! \brief Accesseur pour récupérer le fils droit d'un noeud
 *
 * Donne le pointeur vers le noeud fils droit
 *
 * @param node est un pointeur vers la structure de données
 * real_bitreenode_t représentant le noeud pour lequel on veut le
 * fils droit
 *
 * @return le pointeur vers la structure real_bitreenode_t associée
 * au fils droit
 */
real_bitreenode_t* real_bitree_right(real_bitreenode_t *node);

#endif

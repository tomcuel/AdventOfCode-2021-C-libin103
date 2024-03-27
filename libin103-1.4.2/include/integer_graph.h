/*! \file integer_graph.h
 *
 * \brief Structure de données de graphes orientés ou non, pondérés ou
 * non, représentés par une liste d'adjacence.
 *
 * Une liste d'adjacence est représentée par une liste simplement
 * chainée (générique) dont les éléments sont des ensembles
 * (génériques) contenant des valeurs et un poids (pondération de
 * l'arc).
 *
 */

/*****************************************************************************
*                                                                            *
*  -------------------------------- graph.h -------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef integer_GRAPH_H
#define integer_GRAPH_H

#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "set.h"

/*****************************************************************************
*                                                                            *
*  Define a structure for adjacency list elements                            *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter un élément dans la liste
 *    des voisins d'un sommet du graphe
 */
typedef struct integer_adjlist_elmt_ {
  int vertex; /**< nom d'un noeud voisin */
  double weight; /**< pondération de l'arc */
} integer_adjlist_elmt_t;

/*****************************************************************************
*                                                                            *
*  Define a structure for adjacency lists.                                   *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter la liste des voisins d'un
 * sommet du graphe
 */
typedef struct integer_adjlist_ {
  int vertex; /**< nom d'un noeud */
  generic_set_t adjacent; /**< liste des voisins */
} integer_adjlist_t;

/*****************************************************************************
*                                                                            *
*  Define a structure for graphs.                                            *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour représenter un graphe comme une liste
 * d'adjacence
 */
typedef struct integer_graph_ {
  int vcount; /**< nombre de sommets */
  int ecount; /**< nombre d'arcs */
  generic_list_t adjlists; /**< liste d'adjacence */
} integer_graph_t;

/*****************************************************************************
*                                                                            *
*  Define colors for vertices in graphs.                                     *
*                                                                            *
*****************************************************************************/

/*! \brief Type de données pour annoter les sommets lors d'un parcours
 * de graphe.
 */
typedef enum integer_vertexcolor_ {
  integer_white, /**< drapeau pour indiquer un sommet non considéré */
    integer_gray, /**< drapeau pour indiquer un sommet en cours de traitement */
    integer_black /**< drapeau pour indiquer un sommet qui a été
		    traité */
    } integer_vertexcolor_t;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

/*! \brief Initialisation d'un nouveau graphe
 *
 * Met à zéro du nombre de sommets, du nombre d'arcs et initialisation
 * de la liste d'adjacence
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 */
void integer_graph_init(integer_graph_t *graph);

/*! \brief Destruction d'un graphe
 *
 * Parcours la liste d'adjacence (adjlists) puis parcours de
 * l'ensemble (adjacent) pour détruire tous les éléments de la liste
 * d'adjacence. Puis, mise à zéro du nombre de sommets, du nombre
 * d'arcs et à NULL la liste d'adjacence (adjlists)
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 */
void integer_graph_destroy(integer_graph_t *graph);

/*! \brief Insertion d'un nouveau sommet dans un graphe
 *
 * 1. Parcours la liste d'adjacence (adjlists) pour savoir si le
 * sommet est déjà présent ou pas
 * 2. Si pas présent, ajout d'un nouvel élément à la liste d'adjacence
 * (adjlists)
 * 3. Mise à jour du nombre de sommets dans le graphe
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 *
 * @param vertex nom du nouveau noeud, représenté par une valeur de
 * type <b>int</b>, à ajouter
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int integer_graph_ins_vertex(integer_graph_t *graph,
			     int vertex);

/*! \brief Insertion d'un nouvel arc dans un graphe
 *
 * <b>Remarque:</b> par défaut on considère un arc directionnel donc
 * un graphe dirigé.
 *
 * 1. Vérifie que l'arc n'existe pas déjà
 * 2. Ajoute un nouveau voisin au sommet vertex1 avec la pondération
 * 3. Mise à jour du nombre d'arcs dans le graphe
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 *
 * @param vertex1 nom de la source de l'arc, représenté par une valeur
 * de type <b>int</b>
 *
 * @param vertex2 nom de la destination de l'arc, représenté par une
 * valeur de type <b>int</b>
 *
 * @param weight la valeur de la pondération de l'arc (0.0 si arc non
 * pondéré)
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int integer_graph_ins_edge(integer_graph_t *graph,
			   int vertex1,
			   int vertex2,
			   double weight);

/*! \brief Suppression d'un sommet dans un graphe
 *
 * On peut supprimer un sommet que s'il n'a plus de voisins, c'est à dire,
 * plus d'arc entre lui et les autres sommets du graphe.
 *
 * 1. Vérifie que le sommet ne contient pas de voisins (adjlists vide)
 * 2. Si oui suppression du sommet
 * 3. Mise à jour du nombre de sommets dans le graphe
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 *
 * @param vertex nom du sommet à supprimer
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int integer_graph_rem_vertex(integer_graph_t *graph,
			    int vertex);

/*! \brief Suppression d'un arc dans un graphe
 *
 * 1. Vérifie que l'arc existe
 * 2. Si oui suppression du sommet vertex2 dans la liste des voisins de vertex1
 * 3. Mise à jour du nombre de sommets dans le graphe
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 *
 * @param vertex1 nom de la source de l'arc, représenté par une valeur
 * de type <b>int</b>
 *
 * @param vertex2 nom de la destination de l'arc, représenté par une
 * valeur de type <b>int</b>
 *
 * @return une valeur entière indiquant si tout s'est bien passé (0
 * pour ok, -1 pour erreur)
 */
int integer_graph_rem_edge(integer_graph_t *graph,
			  int vertex1,
			  int vertex2);

/*! \brief Accesseur de la liste des voisins d'un sommet
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 *
 * @param vertex nom du sommet pour lequel la liste des voisins est voulue
 *
 * @return un pointeur vers une liste chainée de type
 * <b>integer_list_t</b> contenant la liste des voisins (sans
 * pondération)
 */
integer_list_t* integer_graph_adjlist (integer_graph_t* graph, int vertex);


/*! \brief Prédicat indiquant si deux sommets sont liés par un arc
 *
 * <b>Remarque</b>: on considère le lien directionnel entre deux
 * sommets.
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 *
 * @param vertex1 nom du sommet source
 *
 * @param vertex2 nom du sommet destination
 *
 * @return une valeur booléenne indiquant s'il y a un arc entre
 * vertex1 et vertex2 (orienté).
 */
bool integer_graph_is_adjacent(const integer_graph_t *graph,
			      int vertex1,
			      int vertex2);

/*! \brief Accesseur du nombre de sommets du graphe
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 *
 * @return valeur entière donnant le nombre de sommets du graphe
 */
int integer_graph_vcount(integer_graph_t *graph);

/*! \brief Accesseur du nombre d'arcs du graphe
 *
 * @param graph est un pointeur vers la structure de données de graphe
 * integer_graph_t
 *
 * @return valeur entière donnant le nombre d'arcs du graphe
 */
int integer_graph_ecount(integer_graph_t *graph);

#endif

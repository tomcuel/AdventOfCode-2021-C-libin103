/*****************************************************************************
*                                                                            *
*  -------------------------------- graph.c -------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "integer_graph.h"
#include "list.h"
#include "set.h"

#ifdef DEBUG
#pragma message "activate debug mode integer_graph"
#endif

static int compareSetElement (const void* data1, const void* data2) {
  integer_adjlist_elmt_t* elem1 = (integer_adjlist_elmt_t*) data1;
  integer_adjlist_elmt_t* elem2 = (integer_adjlist_elmt_t*) data2;

  return (elem1->vertex < elem2->vertex) ? -1 : (elem1->vertex > elem2->vertex) ? 1 : 0;
}


/*****************************************************************************
*                                                                            *
*  ------------------------------ graph_init ------------------------------  *
*                                                                            *
*****************************************************************************/

void integer_graph_init(integer_graph_t *graph)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  /* Initialize the graph. */

  graph->vcount = 0;
  graph->ecount = 0;

  /* Initialize the list of adjacency-list structures. */
  generic_list_init(&graph->adjlists, NULL, NULL, NULL);
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- graph_destroy ----------------------------  *
*                                                                            *
*****************************************************************************/

void integer_graph_destroy(integer_graph_t *graph)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  integer_adjlist_t *adjlist;

  /* Remove each adjacency-list structure and destroy its adjacency list. */
  while (generic_list_size(&graph->adjlists) > 0) {

    if (generic_list_rem_next(&graph->adjlists, NULL, (void **)&adjlist) == 0) {
      generic_set_destroy(&adjlist->adjacent);

      /* free(adjlist->vertex); */


      /* Why this line of code generates an error ? */
      free(adjlist);
    }
  }

  /* Destroy the list of adjacency-list structures, which is now empty. */
  generic_list_destroy(&graph->adjlists);

  /* No operations are allowed now, but clear the structure as a precaution. */
  memset(graph, 0, sizeof(integer_graph_t));
}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_ins_vertex ---------------------------  *
*                                                                            *
*****************************************************************************/

int integer_graph_ins_vertex(integer_graph_t *graph,
			     int vertex)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  generic_list_elmt_t *element;
  integer_adjlist_t *adjlist;
  int retval;

  /* Do not allow the insertion of duplicate vertices. */
  for (element = generic_list_head(&graph->adjlists); element != NULL; element = generic_list_next(element)) {
    if (vertex == ((integer_adjlist_t *)generic_list_data(element))->vertex) { /* Should be a comparison between int or char */
      return 1;
    }
  }

  /* Insert the vertex. */
  adjlist = malloc(sizeof(integer_adjlist_t));
  if (adjlist == NULL) {
   return -1;
  }

  adjlist->vertex = vertex;
  generic_set_init(&adjlist->adjacent, compareSetElement, NULL, NULL);

  retval = generic_list_ins_next(&graph->adjlists,
				 generic_list_tail(&graph->adjlists), (void*)adjlist);

#ifdef DEBUG
  printf ("\t\t\t%s: integer_list_size(&graph->adjlists)=%d\n", __func__, generic_list_size(&graph->adjlists));
  printf ("\t\t\t%s: integer_set_size(tail(&graph->adjlists))=%d\n", __func__, generic_set_size(&((integer_adjlist_t*)generic_list_tail(&graph->adjlists))->adjacent));
#endif

  if (retval != 0) {
    return retval;
  }

  /* Adjust the vertex count to account for the inserted vertex. */
  graph->vcount++;

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- graph_ins_edge ----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_graph_ins_edge(integer_graph_t *graph,
			  int vertex1,
			  int vertex2,
			  double weight)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  generic_list_elmt_t *element1;
  generic_list_elmt_t *element2;
  int retval;

  /* Do not allow insertion of an edge without both its vertices in the graph. */
  for (element2 = generic_list_head(&graph->adjlists); element2 != NULL; element2 = generic_list_next(element2)) {
    if (vertex2 == ((integer_adjlist_t *)generic_list_data(element2))->vertex) {
      break;
    }
  }

#ifdef DEBUG
  printf ("\t\t\t%s END search data2\n", __func__);
#endif

  /* data2 is not in the graph !!*/
  if (element2 == NULL) {
    return -1;
  }

  for (element1 = generic_list_head(&graph->adjlists); element1 != NULL; element1 = generic_list_next(element1)) {
    if (vertex1 == ((integer_adjlist_t *)generic_list_data(element1))->vertex) {
      break;
    }
  }

#ifdef DEBUG
  printf ("\t\t\t%s END search data1\n", __func__);
#endif

  /* data1 is not in the graph !!*/
  if (element1 == NULL) {
    return -1;
  }

  /* For primitive value on vertices, we create a struct for adjacent set */
  integer_adjlist_elmt_t* mydata = malloc (sizeof(integer_adjlist_elmt_t));
  mydata->vertex = vertex2;
  mydata->weight = weight;
  /* NOTE: do not free here this variable as we use sharing between data structures !!! */

  /* Insert the second vertex into the adjacency list of the first vertex. */
  retval = generic_set_insert(&(((integer_adjlist_t *)generic_list_data(element1))->adjacent), (void*) mydata);

#ifdef DEBUG
  printf ("\t\t\t%s END insert data2 in adjacent set of data1\n", __func__);
#endif


  if (retval != 0) {
   return retval;
  }

  /* Adjust the edge count to account for the inserted edge. */
  graph->ecount++;

  return 0;
}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_rem_vertex ---------------------------  *
*                                                                            *
*****************************************************************************/

int integer_graph_rem_vertex(integer_graph_t *graph,
			    int vertex)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  generic_list_elmt_t *element;
  generic_list_elmt_t *temp = NULL;
  generic_list_elmt_t *prev;
  integer_adjlist_t *adjlist;
  bool found;

  /* Traverse each adjacency list and the vertices it contains. */
  prev = NULL;
  found = false;

  for (element = generic_list_head(&graph->adjlists); element != NULL;
       element = generic_list_next(element)) {

    /* Do not allow removal of the vertex if it is in an adjacency list. */
    integer_adjlist_elmt_t* tempV = malloc (sizeof(integer_adjlist_elmt_t));
    tempV->vertex = vertex;
    tempV->weight = 0.0;
    if (generic_set_is_member(&((integer_adjlist_t *)generic_list_data(element))->adjacent, tempV)) {
      free (tempV);
      return -1;
    }
    free (tempV);
    /* Keep a pointer to the vertex to be removed. */
    if (vertex == ((integer_adjlist_t *)generic_list_data(element))->vertex)
      {
	temp = element;
	found = true;
      }

    /* Keep a pointer to the vertex before the vertex to be removed. */
    if (!found) {
      prev = element;
    }
  }

  /* Return if the vertex was not found. */
  if (!found) {
    return -1;
  }
  /* Do not allow removal of the vertex if its adjacency list is not empty. */
  if (generic_set_size(&((integer_adjlist_t *)generic_list_data(temp))->adjacent) > 0) {
   return -1;
  }

  /* Remove the vertex. */
  if (generic_list_rem_next(&graph->adjlists, prev, (void **)&adjlist) != 0) {
   return -1;
  }

  /* Free the storage allocated by the abstract data type. */
  /* &vertex = adjlist->vertex; Useless here */
  free(adjlist);

  /* Adjust the vertex count to account for the removed vertex. */
  graph->vcount--;

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- graph_rem_edge ----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_graph_rem_edge(integer_graph_t *graph,
			   int vertex1,
			   int vertex2)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  generic_list_elmt_t *element;

  /* Locate the adjacency list for the first vertex. */

  for (element = generic_list_head(&graph->adjlists); element != NULL;
       element = generic_list_next(element)) {

    if (vertex1 == ((integer_adjlist_t *)generic_list_data(element))->vertex) {
      break;
    }
  }

  if (element == NULL) {
   return -1;
  }

  /* Remove the second vertex from the adjacency list of the first vertex. */
  integer_adjlist_elmt_t tempV;
  if (generic_set_remove(&((integer_adjlist_t *)generic_list_data(element))->adjacent, (void*)&tempV) != 0) {
    return -1;
  }
  /* Adjust the edge count to account for the removed edge. */
  graph->ecount--;

  return 0;
}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_is_adjacent --------------------------  *
*                                                                            *
*****************************************************************************/

bool integer_graph_is_adjacent(const integer_graph_t *graph,
			      int vertex1,
			      int vertex2)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  generic_list_elmt_t *element;
  generic_list_t tempAdjlist = graph->adjlists;
  for (element = generic_list_head(&tempAdjlist); element != NULL;
       element = generic_list_next(element)) {

    if (vertex1 == ((integer_adjlist_t *)generic_list_data(element))->vertex) {
      break;
    }
  }

  /* Return if the first vertex was not found. */
  if (element == NULL) {
   return false;
  }
  /* Return whether the second vertex is in the adjacency list of the first. */
  integer_adjlist_elmt_t* tempV = malloc (sizeof(integer_adjlist_elmt_t));
  tempV->vertex = vertex2;
  tempV->weight = 0.0;
  bool res = generic_set_is_member(&((integer_adjlist_t *)generic_list_data(element))->adjacent, tempV);

  free(tempV);
  return res;
}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_vcount -------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_graph_vcount(integer_graph_t *graph)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  assert (graph != NULL);
  return graph->vcount;
}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_ecount -------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_graph_ecount(integer_graph_t *graph)
{
#ifdef DEBUG
  printf ("\t\tEnter %s\n", __func__);
#endif

  assert (graph != NULL);
  return graph->ecount;
}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_adjlist -------------------------------  *
*                                                                            *
*****************************************************************************/


integer_list_t* integer_graph_adjlist (integer_graph_t* graph, int vertex) {
  integer_list_t *result = malloc (sizeof(integer_list_t));
  integer_list_init(result);

  generic_list_elmt_t* elem = generic_list_head (&(graph->adjlists));
  for (; elem != NULL; elem = generic_list_next (elem)) {
    integer_adjlist_t* node = (integer_adjlist_t*) generic_list_data (elem);

    if (node->vertex == vertex) {
      generic_list_elmt_t* elem2 = generic_list_head (&(node->adjacent));
      for (; elem2 != NULL; elem2 = generic_list_next (elem2)) {
	integer_adjlist_elmt_t* child =
	  (integer_adjlist_elmt_t*) generic_list_data (elem2);

	integer_list_ins_next (result, integer_list_tail(result), child->vertex);
      }
    }
  }

  return result;
}

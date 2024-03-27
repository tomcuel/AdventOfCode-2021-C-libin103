/*****************************************************************************
*                                                                            *
*  -------------------------------- topological.c ---------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>

#include "graph.h"
#include "list.h"

static int integer_ts_aux (integer_graph_t* graph, int start, integer_set_t* marker, integer_list_t* ordered) {

  if (integer_set_is_member (marker, start)) {
    return 0;
  }

  integer_set_insert (marker, start);

  integer_list_t* neighbors = integer_graph_adjlist (graph, start);

  integer_list_elmt_t* elem = integer_list_head (neighbors);
  for (; elem != NULL; elem = integer_list_next (elem)) {
    int n = integer_list_data (elem);
    integer_ts_aux (graph, n, marker, ordered);
  }

  integer_list_ins_next (ordered, NULL, start);
  free(neighbors);

  return 0;
}



int integer_ts (integer_graph_t* graph, integer_list_t* ordered) {
  integer_set_t set;
  integer_set_init (&set);

  generic_list_elmt_t *elem = generic_list_head (&(graph->adjlists));
  for (; elem != NULL; elem = generic_list_next (elem)) {
    integer_adjlist_t* node = (integer_adjlist_t*)generic_list_data (elem);
    integer_ts_aux (graph, node->vertex, &set, ordered);
  }

  return 0;
}

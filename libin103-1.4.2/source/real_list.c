/*****************************************************************************
 *                                                                            *
 *  -------------------------------- real_list.c -------------------------  *
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "real_list.h"

/*****************************************************************************
 *                                                                            *
 *  ------------------------------- real_list_init -----------------------  *
 *                                                                            *
 *****************************************************************************/


/*!
  @function real_list_init
  @param list

  @abstract This function initializes an empty list.

*/
void real_list_init (real_list_t *list) {

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_destroy ----------------------  *
 *                                                                            *
 *****************************************************************************/

void real_list_destroy(real_list_t *list) {

  int code;
  /*  Remove each element. */
  double data;
  while (real_list_size(list) > 0) {
    code = real_list_rem_next(list, NULL, &data);
    if (code != 0) {
      fprintf (stderr, "Error: %s remove element impossible\n", __func__);
    }
  }

  /*  No operations are allowed now, but clear the structure as a precaution. */
  memset(list, 0, sizeof(real_list_t));
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_size ----------------------  *
 *                                                                            *
 *****************************************************************************/

  int real_list_size (real_list_t* list) {
  return list->size;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_head ----------------------  *
 *                                                                            *
 *****************************************************************************/

real_list_elmt_t* real_list_head(real_list_t* list) {
    assert (list != NULL);
    return list->head;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_tail ----------------------  *
 *                                                                            *
 *****************************************************************************/

real_list_elmt_t* real_list_tail(real_list_t* list) {
    assert (list != NULL);
    return list->tail;
  }

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_is_head ----------------------  *
 *                                                                            *
 *****************************************************************************/

bool real_list_is_head(real_list_t* list, real_list_elmt_t* element) {
  assert (list != NULL);
  if (element == (list)->head) {
    return true;
  }
  else {
    return false;
  }
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_is_tail ----------------------  *
 *                                                                            *
 *****************************************************************************/

bool real_list_is_tail(real_list_elmt_t* element) {
  assert (element != NULL);
  if ((element)->next == NULL) {
    return true;
  }
  else {
    return false;
  }
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_data ----------------------  *
 *                                                                            *
 *****************************************************************************/

double real_list_data(real_list_elmt_t* element) {
  assert (element != NULL);
  return element->data;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_next ----------------------  *
 *                                                                            *
 *****************************************************************************/

real_list_elmt_t* real_list_next(real_list_elmt_t* element) {
  assert (element != NULL);
  return element->next;
}


/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_ins_next ---------------------  *
 *                                                                            *
 *****************************************************************************/

int real_list_ins_next(real_list_t *list, real_list_elmt_t *element, double data) {

  real_list_elmt_t          *new_element;

  /* Allocate storage for the element. */
  new_element = malloc(sizeof(real_list_elmt_t));
  if (new_element == NULL) {
    return -1;
  }

  /* Insert the element into the list. */

  new_element->data = data;

  if (element == NULL) {
    /* Handle insertion at the head of the list. */

    if (real_list_size(list) == 0) {
      list->tail = new_element;
    }

    new_element->next = list->head;
    list->head = new_element;

  }

  else {
    /* Handle insertion somewhere other than at the head. */

    if (element->next == NULL) {
      list->tail = new_element;
    }

    new_element->next = element->next;
    element->next = new_element;

  }

  /* Adjust the size of the list to account for the inserted element. */
  list->size++;

  return 0;

}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- real_list_rem_next ---------------------  *
 *                                                                            *
 *****************************************************************************/

int real_list_rem_next(real_list_t *list,
			 real_list_elmt_t *element,
			 double *data)
{
  assert (data != NULL);
  real_list_elmt_t *old_element;

  /* Do not allow removal from an empty list. */
  if (real_list_size(list) == 0) {
    return -1;
  }

  /* Remove the element from the list. */
  if (element == NULL) {
    /* Handle removal from the head of the list. */

    *data = list->head->data;
    old_element = list->head;
    list->head = list->head->next;

    if (real_list_size(list) == 1) {
      list->tail = NULL;
    }

  }

  else {
    /* Handle removal from somewhere other than the head. */

    if (element->next == NULL) {
      return -1;
    }

    *data = element->next->data;
    old_element = element->next;
    element->next = element->next->next;

    if (element->next == NULL) {
      list->tail = element;
    }

  }

  /* Free the storage allocated by the abstract data type. */
  free(old_element);

  /* Adjust the size of the list to account for the removed element. */
  list->size--;

  return 0;

}

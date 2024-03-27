/*****************************************************************************
 *                                                                            *
 *  -------------------------------- integer_list.c -------------------------  *
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "integer_list.h"

/*****************************************************************************
 *                                                                            *
 *  ------------------------------- integer_list_init -----------------------  *
 *                                                                            *
 *****************************************************************************/


/*!
  @function integer_list_init
  @param list

  @abstract This function initializes an empty list.

*/
void integer_list_init (integer_list_t *list) {

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- integer_list_destroy ----------------------  *
 *                                                                            *
 *****************************************************************************/

void integer_list_destroy(integer_list_t *list) {

  int code;
  /*  Remove each element. */
  int data;
  while (integer_list_size(list) > 0) {
    code = integer_list_rem_next(list, NULL, &data);
    if (code != 0) {
      fprintf (stderr, "Error: %s remove element impossible\n", __func__);
    }
  }

  /*  No operations are allowed now, but clear the structure as a precaution. */
  memset(list, 0, sizeof(integer_list_t));
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- integer_list_size ----------------------  *
 *                                                                            *
 *****************************************************************************/

  int integer_list_size (integer_list_t* list) {
  return list->size;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- integer_list_head ----------------------  *
 *                                                                            *
 *****************************************************************************/

integer_list_elmt_t* integer_list_head(integer_list_t* list) {
    assert (list != NULL);
    return list->head;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- integer_list_tail ----------------------  *
 *                                                                            *
 *****************************************************************************/

integer_list_elmt_t* integer_list_tail(integer_list_t* list) {
    assert (list != NULL);
    return list->tail;
  }

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- integer_list_is_head ----------------------  *
 *                                                                            *
 *****************************************************************************/

bool integer_list_is_head(integer_list_t* list, integer_list_elmt_t* element) {
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
 *  ----------------------------- integer_list_is_tail ----------------------  *
 *                                                                            *
 *****************************************************************************/

bool integer_list_is_tail(integer_list_elmt_t* element) {
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
 *  ----------------------------- integer_list_data ----------------------  *
 *                                                                            *
 *****************************************************************************/

int integer_list_data(integer_list_elmt_t* element) {
  assert (element != NULL);
  return element->data;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- integer_list_next ----------------------  *
 *                                                                            *
 *****************************************************************************/

integer_list_elmt_t* integer_list_next(integer_list_elmt_t* element) {
  assert (element != NULL);
  return element->next;
}


/*****************************************************************************
 *                                                                            *
 *  ----------------------------- integer_list_ins_next ---------------------  *
 *                                                                            *
 *****************************************************************************/

int integer_list_ins_next(integer_list_t *list, integer_list_elmt_t *element, int data) {

  integer_list_elmt_t          *new_element;

  /* Allocate storage for the element. */
  new_element = malloc(sizeof(integer_list_elmt_t));
  if (new_element == NULL) {
    return -1;
  }

  /* Insert the element into the list. */

  new_element->data = data;

  if (element == NULL) {
    /* Handle insertion at the head of the list. */

    if (integer_list_size(list) == 0) {
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
 *  ----------------------------- integer_list_rem_next ---------------------  *
 *                                                                            *
 *****************************************************************************/

int integer_list_rem_next(integer_list_t *list,
			 integer_list_elmt_t *element,
			 int *data)
{
  assert (data != NULL);
  integer_list_elmt_t *old_element;

  /* Do not allow removal from an empty list. */
  if (integer_list_size(list) == 0) {
    return -1;
  }

  /* Remove the element from the list. */
  if (element == NULL) {
    /* Handle removal from the head of the list. */

    *data = list->head->data;
    old_element = list->head;
    list->head = list->head->next;

    if (integer_list_size(list) == 1) {
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

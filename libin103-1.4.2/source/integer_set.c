/*****************************************************************************
*                                                                            *
*  -------------------------------- set.c ---------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "integer_list.h"
#include "integer_set.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- integer_set_init ------------------------  *
*                                                                            *
*****************************************************************************/

void integer_set_init(integer_set_t *set) {
  /* Initialize the set. */
  integer_list_init(set);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------- integer_set_destroy ---------------------  *
*                                                                            *
*****************************************************************************/

void integer_set_destroy(integer_set_t *set) {
  /* Destroy the list. */
  integer_list_destroy(set);
}


/*****************************************************************************
*                                                                            *
*  ----------------------- integer_set_insert ------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_set_insert(integer_set_t *set, int data) {

  /* Do not allow the insertion of duplicates. */
  if (integer_set_is_member(set, data)) {
    return 1;
  }

  /* Insert the data. */
  return integer_list_ins_next(set, integer_list_tail(set), data);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------ integer_set_remove -----------------------  *
*                                                                            *
*****************************************************************************/

int integer_set_remove(integer_set_t *set, int *data) {

  integer_list_elmt_t *member;
  integer_list_elmt_t *prev;

  /* Find the member to remove. */

  prev = NULL;

  for (member = integer_list_head(set); member != NULL;
       member = integer_list_next(member)) {

    if (*data == integer_list_data(member)) {
      break;
    }
    prev = member;
  }

  /* Return if the member was not found. */
  if (member == NULL) {
    return -1;
  }

  /* Remove the member. */
  return integer_list_rem_next(set, prev, data);

}

/*****************************************************************************
*                                                                            *
*  ------------------------ integer_set_union ------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_set_union(integer_set_t *setu, const integer_set_t *set1, const integer_set_t *set2) {

  integer_list_elmt_t *member;
  int data;

  /* Initialize the set for the union. */
  integer_set_init(setu);

  /* Insert the members of the first set. */

  for (member = integer_list_head((integer_list_t*)set1); member != NULL;
       member = integer_list_next(member)) {

    data = integer_list_data(member);

    if (integer_list_ins_next((integer_list_t*)setu, integer_list_tail((integer_list_t*)setu), data) != 0) {
      integer_set_destroy(setu);
      return -1;
    }
  }

  /* Insert the members of the second set. */
  for (member = integer_list_head((integer_list_t*)set2); member != NULL;
       member = integer_list_next(member)) {
   if (integer_set_is_member(set1, integer_list_data(member))) {
      /* Do not allow the insertion of duplicates. */
      continue;
   }
   else {
      data = integer_list_data(member);

      if (integer_list_ins_next(setu, integer_list_tail(setu), data) != 0) {
         integer_set_destroy(setu);
         return -1;
      }
   }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  -------------------- integer_set_intersection ---------------------------  *
*                                                                            *
*****************************************************************************/

int integer_set_intersection(integer_set_t *seti, const integer_set_t *set1,
			    const integer_set_t *set2) {

  integer_list_elmt_t *member;
  int data;

  /* Initialize the set for the intersection. */
  integer_set_init(seti);

  /* Insert the members present in both sets. */
  for (member = integer_list_head((integer_list_t*)set1); member != NULL;
       member = integer_list_next(member)) {

    if (integer_set_is_member(set2, integer_list_data(member))) {

      data = integer_list_data(member);

      if (integer_list_ins_next(seti, integer_list_tail(seti), data) != 0) {
	integer_set_destroy(seti);
	return -1;
      }
    }
  }
  return 0;
}

/*****************************************************************************
*                                                                            *
*  --------------------- integer_set_difference ----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_set_difference(integer_set_t *setd, const integer_set_t *set1,
			  const integer_set_t *set2) {

  integer_list_elmt_t *member;
  int data;

  /* Initialize the set for the difference. */
  integer_set_init(setd);

  /* Insert the members from set1 not in set2. */
  for (member = integer_list_head((integer_list_t*)set1); member != NULL;
       member = integer_list_next(member)) {

    if (!integer_set_is_member(set2, integer_list_data(member))) {

      data = integer_list_data(member);
      if (integer_list_ins_next(setd, integer_list_tail(setd), data) != 0) {
         integer_set_destroy(setd);
	return -1;
      }
    }
  }
  return 0;
}

/*****************************************************************************
*                                                                            *
*  ---------------------- integer_set_is_member ----------------------------  *
*                                                                            *
*****************************************************************************/

bool integer_set_is_member(const integer_set_t *set, int data) {

  integer_list_elmt_t *member;

  /* Determine if the data is a member of the set. */
  for (member = integer_list_head((integer_list_t*)set); member != NULL;
       member = integer_list_next(member)) {

    if (data == integer_list_data(member)) {
      return true;
    }
  }

  return false;
}

/*****************************************************************************
*                                                                            *
*  ---------------------- integer_set_is_subset ----------------------------  *
*                                                                            *
*****************************************************************************/

bool integer_set_is_subset(const integer_set_t *set1, const integer_set_t *set2) {

  integer_list_elmt_t *member;

  /* Do a quick test to rule out some cases. */
  if (integer_set_size(set1) > integer_set_size(set2)) {
    return false;
  }

  /* Determine if set1 is a subset of set2. */
  for (member = integer_list_head((integer_list_t*)set1); member != NULL;
       member = integer_list_next(member)) {

    if (!integer_set_is_member(set2, integer_list_data(member)))
      return false;
  }

  return true;
}

/*****************************************************************************
*                                                                            *
*  ----------------------- integer_set_is_equal ----------------------------  *
*                                                                            *
*****************************************************************************/

bool integer_set_is_equal(const integer_set_t *set1, const integer_set_t *set2) {

  /* Do a quick test to rule out some cases. */
  if (integer_set_size(set1) != integer_set_size(set2)) {
   return false;
  }

  /* Sets of the same size are equal if they are subsets. */
  return integer_set_is_subset(set1, set2);
}

/*****************************************************************************
*                                                                            *
*  --------------------------- integer_set_size ----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_set_size(const integer_set_t *set) {
    return integer_list_size ((integer_list_t*)set);
}

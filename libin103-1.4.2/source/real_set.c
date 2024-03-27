/*****************************************************************************
*                                                                            *
*  -------------------------------- set.c ---------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "real_list.h"
#include "real_set.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- real_set_init ------------------------  *
*                                                                            *
*****************************************************************************/

void real_set_init(real_set_t *set) {
  /* Initialize the set. */
  real_list_init(set);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------- real_set_destroy ---------------------  *
*                                                                            *
*****************************************************************************/

void real_set_destroy(real_set_t *set) {
  /* Destroy the list. */
  real_list_destroy(set);
}


/*****************************************************************************
*                                                                            *
*  ----------------------- real_set_insert ------------------------------  *
*                                                                            *
*****************************************************************************/

int real_set_insert(real_set_t *set, double data) {

  /* Do not allow the insertion of duplicates. */
  if (real_set_is_member(set, data)) {
    return 1;
  }

  /* Insert the data. */
  return real_list_ins_next(set, real_list_tail(set), data);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------ real_set_remove -----------------------  *
*                                                                            *
*****************************************************************************/

int real_set_remove(real_set_t *set, double *data) {

  real_list_elmt_t *member;
  real_list_elmt_t *prev;

  /* Find the member to remove. */

  prev = NULL;

  for (member = real_list_head(set); member != NULL;
       member = real_list_next(member)) {

    if (*data == real_list_data(member)) {
      break;
    }
    prev = member;
  }

  /* Return if the member was not found. */
  if (member == NULL) {
    return -1;
  }

  /* Remove the member. */
  return real_list_rem_next(set, prev, data);

}

/*****************************************************************************
*                                                                            *
*  ------------------------ real_set_union ------------------------------  *
*                                                                            *
*****************************************************************************/

int real_set_union(real_set_t *setu, const real_set_t *set1, const real_set_t *set2) {

  real_list_elmt_t *member;
  double data;

  /* Initialize the set for the union. */
  real_set_init(setu);

  /* Insert the members of the first set. */

  for (member = real_list_head((real_list_t*)set1); member != NULL;
       member = real_list_next(member)) {

    data = real_list_data(member);

    if (real_list_ins_next((real_list_t*)setu, real_list_tail((real_list_t*)setu), data) != 0) {
      real_set_destroy(setu);
      return -1;
    }
  }

  /* Insert the members of the second set. */
  for (member = real_list_head((real_list_t*)set2); member != NULL;
       member = real_list_next(member)) {
   if (real_set_is_member(set1, real_list_data(member))) {
      /* Do not allow the insertion of duplicates. */
      continue;
   }
   else {
      data = real_list_data(member);

      if (real_list_ins_next(setu, real_list_tail(setu), data) != 0) {
         real_set_destroy(setu);
         return -1;
      }
   }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  -------------------- real_set_intersection ---------------------------  *
*                                                                            *
*****************************************************************************/

int real_set_intersection(real_set_t *seti, const real_set_t *set1,
			    const real_set_t *set2) {

  real_list_elmt_t *member;
  double data;

  /* Initialize the set for the intersection. */
  real_set_init(seti);

  /* Insert the members present in both sets. */
  for (member = real_list_head((real_list_t*)set1); member != NULL;
       member = real_list_next(member)) {

    if (real_set_is_member(set2, real_list_data(member))) {

      data = real_list_data(member);

      if (real_list_ins_next(seti, real_list_tail(seti), data) != 0) {
	real_set_destroy(seti);
	return -1;
      }
    }
  }
  return 0;
}

/*****************************************************************************
*                                                                            *
*  --------------------- real_set_difference ----------------------------  *
*                                                                            *
*****************************************************************************/

int real_set_difference(real_set_t *setd, const real_set_t *set1,
			  const real_set_t *set2) {

  real_list_elmt_t *member;
  double data;

  /* Initialize the set for the difference. */
  real_set_init(setd);

  /* Insert the members from set1 not in set2. */
  for (member = real_list_head((real_list_t*)set1); member != NULL;
       member = real_list_next(member)) {

    if (!real_set_is_member(set2, real_list_data(member))) {

      data = real_list_data(member);
      if (real_list_ins_next(setd, real_list_tail(setd), data) != 0) {
         real_set_destroy(setd);
	return -1;
      }
    }
  }
  return 0;
}

/*****************************************************************************
*                                                                            *
*  ---------------------- real_set_is_member ----------------------------  *
*                                                                            *
*****************************************************************************/

bool real_set_is_member(const real_set_t *set, double data) {

  real_list_elmt_t *member;

  /* Determine if the data is a member of the set. */
  for (member = real_list_head((real_list_t*)set); member != NULL;
       member = real_list_next(member)) {

    if (data == real_list_data(member)) {
      return true;
    }
  }

  return false;
}

/*****************************************************************************
*                                                                            *
*  ---------------------- real_set_is_subset ----------------------------  *
*                                                                            *
*****************************************************************************/

bool real_set_is_subset(const real_set_t *set1, const real_set_t *set2) {

  real_list_elmt_t *member;

  /* Do a quick test to rule out some cases. */
  if (real_set_size(set1) > real_set_size(set2)) {
    return false;
  }

  /* Determine if set1 is a subset of set2. */
  for (member = real_list_head((real_list_t*)set1); member != NULL;
       member = real_list_next(member)) {

    if (!real_set_is_member(set2, real_list_data(member)))
      return false;
  }

  return true;
}

/*****************************************************************************
*                                                                            *
*  ----------------------- real_set_is_equal ----------------------------  *
*                                                                            *
*****************************************************************************/

bool real_set_is_equal(const real_set_t *set1, const real_set_t *set2) {

  /* Do a quick test to rule out some cases. */
  if (real_set_size(set1) != real_set_size(set2)) {
   return false;
  }

  /* Sets of the same size are equal if they are subsets. */
  return real_set_is_subset(set1, set2);
}

/*****************************************************************************
*                                                                            *
*  --------------------------- real_set_size ----------------------------  *
*                                                                            *
*****************************************************************************/

int real_set_size(const real_set_t *set) {
    return real_list_size ((real_list_t*)set);
}

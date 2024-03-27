/*****************************************************************************
*                                                                            *
*  -------------------------------- set.c ---------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "character_list.h"
#include "character_set.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- character_set_init ------------------------  *
*                                                                            *
*****************************************************************************/

void character_set_init(character_set_t *set) {
  /* Initialize the set. */
  character_list_init(set);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------- character_set_destroy ---------------------  *
*                                                                            *
*****************************************************************************/

void character_set_destroy(character_set_t *set) {
  /* Destroy the list. */
  character_list_destroy(set);
}


/*****************************************************************************
*                                                                            *
*  ----------------------- character_set_insert ------------------------------  *
*                                                                            *
*****************************************************************************/

int character_set_insert(character_set_t *set, char data) {

  /* Do not allow the insertion of duplicates. */
  if (character_set_is_member(set, data)) {
    return 1;
  }

  /* Insert the data. */
  return character_list_ins_next(set, character_list_tail(set), data);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------ character_set_remove -----------------------  *
*                                                                            *
*****************************************************************************/

int character_set_remove(character_set_t *set, char *data) {

  character_list_elmt_t *member;
  character_list_elmt_t *prev;

  /* Find the member to remove. */

  prev = NULL;

  for (member = character_list_head(set); member != NULL;
       member = character_list_next(member)) {

    if (*data == character_list_data(member)) {
      break;
    }
    prev = member;
  }

  /* Return if the member was not found. */
  if (member == NULL) {
    return -1;
  }

  /* Remove the member. */
  return character_list_rem_next(set, prev, data);

}

/*****************************************************************************
*                                                                            *
*  ------------------------ character_set_union ------------------------------  *
*                                                                            *
*****************************************************************************/

int character_set_union(character_set_t *setu, const character_set_t *set1, const character_set_t *set2) {

  character_list_elmt_t *member;
  char data;

  /* Initialize the set for the union. */
  character_set_init(setu);

  /* Insert the members of the first set. */

  for (member = character_list_head((character_list_t*)set1); member != NULL;
       member = character_list_next(member)) {

    data = character_list_data(member);

    if (character_list_ins_next((character_list_t*)setu, character_list_tail((character_list_t*)setu), data) != 0) {
      character_set_destroy(setu);
      return -1;
    }
  }

  /* Insert the members of the second set. */
  for (member = character_list_head((character_list_t*)set2); member != NULL;
       member = character_list_next(member)) {
   if (character_set_is_member(set1, character_list_data(member))) {
      /* Do not allow the insertion of duplicates. */
      continue;
   }
   else {
      data = character_list_data(member);

      if (character_list_ins_next(setu, character_list_tail(setu), data) != 0) {
         character_set_destroy(setu);
         return -1;
      }
   }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  -------------------- character_set_intersection ---------------------------  *
*                                                                            *
*****************************************************************************/

int character_set_intersection(character_set_t *seti, const character_set_t *set1,
			    const character_set_t *set2) {

  character_list_elmt_t *member;
  char data;

  /* Initialize the set for the intersection. */
  character_set_init(seti);

  /* Insert the members present in both sets. */
  for (member = character_list_head((character_list_t*)set1); member != NULL;
       member = character_list_next(member)) {

    if (character_set_is_member(set2, character_list_data(member))) {

      data = character_list_data(member);

      if (character_list_ins_next(seti, character_list_tail(seti), data) != 0) {
	character_set_destroy(seti);
	return -1;
      }
    }
  }
  return 0;
}

/*****************************************************************************
*                                                                            *
*  --------------------- character_set_difference ----------------------------  *
*                                                                            *
*****************************************************************************/

int character_set_difference(character_set_t *setd, const character_set_t *set1,
			  const character_set_t *set2) {

  character_list_elmt_t *member;
  char data;

  /* Initialize the set for the difference. */
  character_set_init(setd);

  /* Insert the members from set1 not in set2. */
  for (member = character_list_head((character_list_t*)set1); member != NULL;
       member = character_list_next(member)) {

    if (!character_set_is_member(set2, character_list_data(member))) {

      data = character_list_data(member);
      if (character_list_ins_next(setd, character_list_tail(setd), data) != 0) {
         character_set_destroy(setd);
	return -1;
      }
    }
  }
  return 0;
}

/*****************************************************************************
*                                                                            *
*  ---------------------- character_set_is_member ----------------------------  *
*                                                                            *
*****************************************************************************/

bool character_set_is_member(const character_set_t *set, char data) {

  character_list_elmt_t *member;

  /* Determine if the data is a member of the set. */
  for (member = character_list_head((character_list_t*)set); member != NULL;
       member = character_list_next(member)) {

    if (data == character_list_data(member)) {
      return true;
    }
  }

  return false;
}

/*****************************************************************************
*                                                                            *
*  ---------------------- character_set_is_subset ----------------------------  *
*                                                                            *
*****************************************************************************/

bool character_set_is_subset(const character_set_t *set1, const character_set_t *set2) {

  character_list_elmt_t *member;

  /* Do a quick test to rule out some cases. */
  if (character_set_size(set1) > character_set_size(set2)) {
    return false;
  }

  /* Determine if set1 is a subset of set2. */
  for (member = character_list_head((character_list_t*)set1); member != NULL;
       member = character_list_next(member)) {

    if (!character_set_is_member(set2, character_list_data(member)))
      return false;
  }

  return true;
}

/*****************************************************************************
*                                                                            *
*  ----------------------- character_set_is_equal ----------------------------  *
*                                                                            *
*****************************************************************************/

bool character_set_is_equal(const character_set_t *set1, const character_set_t *set2) {

  /* Do a quick test to rule out some cases. */
  if (character_set_size(set1) != character_set_size(set2)) {
   return false;
  }

  /* Sets of the same size are equal if they are subsets. */
  return character_set_is_subset(set1, set2);
}

/*****************************************************************************
*                                                                            *
*  --------------------------- character_set_size ----------------------------  *
*                                                                            *
*****************************************************************************/

int character_set_size(const character_set_t *set) {
    return character_list_size ((character_list_t*)set);
}

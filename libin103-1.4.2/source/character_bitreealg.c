/*****************************************************************************
*                                                                            *
*  ------------------------------ traverse.c ------------------------------  *
*                                                                            *
*****************************************************************************/

#include "character_list.h"
#include "character_bitreealg.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- preorder -------------------------------  *
*                                                                            *
*****************************************************************************/

int character_preorder(character_bitreenode_t *node, character_list_t *list) {

  /* Load the list with a preorder listing of the tree. */
  if (!character_bitree_is_eob(node)) {
    if (character_list_ins_next(list, character_list_tail(list),
			     character_bitree_data(node)) != 0) {
      return -1;
    }

    if (!character_bitree_is_eob(character_bitree_left(node))) {
      if (character_preorder(character_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (!character_bitree_is_eob(character_bitree_right(node))) {
      if (character_preorder(character_bitree_right(node), list) != 0) {
      return -1;
      }
    }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  -------------------------------- inorder -------------------------------  *
*                                                                            *
*****************************************************************************/

int character_inorder(character_bitreenode_t *node, character_list_t *list) {

  /* Load the list with an character_inorder listing of the tree. */
  if (!character_bitree_is_eob(node)) {

    if (!character_bitree_is_eob(character_bitree_left(node))) {
      if (character_inorder(character_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (character_list_ins_next(list, character_list_tail(list),
			      character_bitree_data(node)) != 0) {
      return -1;
    }

    if (!character_bitree_is_eob(character_bitree_right(node))) {
      if (character_inorder(character_bitree_right(node), list) != 0) {
	return -1;
      }
    }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ------------------------------- character_postorder ----------------------  *
*                                                                            *
*****************************************************************************/

int character_postorder(character_bitreenode_t *node, character_list_t *list) {

  /* Load the list with a postorder listing of the tree. */
  if (!character_bitree_is_eob(node)) {

    if (!character_bitree_is_eob(character_bitree_left(node))) {
      if (character_postorder(character_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (!character_bitree_is_eob(character_bitree_right(node))) {
      if (character_postorder(character_bitree_right(node), list) != 0) {
	return -1;
      }
    }

    if (character_list_ins_next(list, character_list_tail(list),
			      character_bitree_data(node)) != 0) {
      return -1;
    }
  }

  return 0;
}

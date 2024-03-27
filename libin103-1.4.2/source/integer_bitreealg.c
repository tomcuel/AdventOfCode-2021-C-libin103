/*****************************************************************************
*                                                                            *
*  ------------------------------ traverse.c ------------------------------  *
*                                                                            *
*****************************************************************************/

#include "integer_list.h"
#include "integer_bitreealg.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- preorder -------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_preorder(integer_bitreenode_t *node, integer_list_t *list) {

  /* Load the list with a preorder listing of the tree. */
  if (!integer_bitree_is_eob(node)) {
    if (integer_list_ins_next(list, integer_list_tail(list),
			     integer_bitree_data(node)) != 0) {
      return -1;
    }

    if (!integer_bitree_is_eob(integer_bitree_left(node))) {
      if (integer_preorder(integer_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (!integer_bitree_is_eob(integer_bitree_right(node))) {
      if (integer_preorder(integer_bitree_right(node), list) != 0) {
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

int integer_inorder(integer_bitreenode_t *node, integer_list_t *list) {

  /* Load the list with an integer_inorder listing of the tree. */
  if (!integer_bitree_is_eob(node)) {

    if (!integer_bitree_is_eob(integer_bitree_left(node))) {
      if (integer_inorder(integer_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (integer_list_ins_next(list, integer_list_tail(list),
			      integer_bitree_data(node)) != 0) {
      return -1;
    }

    if (!integer_bitree_is_eob(integer_bitree_right(node))) {
      if (integer_inorder(integer_bitree_right(node), list) != 0) {
	return -1;
      }
    }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ------------------------------- integer_postorder ----------------------  *
*                                                                            *
*****************************************************************************/

int integer_postorder(integer_bitreenode_t *node, integer_list_t *list) {

  /* Load the list with a postorder listing of the tree. */
  if (!integer_bitree_is_eob(node)) {

    if (!integer_bitree_is_eob(integer_bitree_left(node))) {
      if (integer_postorder(integer_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (!integer_bitree_is_eob(integer_bitree_right(node))) {
      if (integer_postorder(integer_bitree_right(node), list) != 0) {
	return -1;
      }
    }

    if (integer_list_ins_next(list, integer_list_tail(list),
			      integer_bitree_data(node)) != 0) {
      return -1;
    }
  }

  return 0;
}

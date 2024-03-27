/*****************************************************************************
*                                                                            *
*  ------------------------------ traverse.c ------------------------------  *
*                                                                            *
*****************************************************************************/

#include "real_list.h"
#include "real_bitreealg.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- preorder -------------------------------  *
*                                                                            *
*****************************************************************************/

int real_preorder(real_bitreenode_t *node, real_list_t *list) {

  /* Load the list with a preorder listing of the tree. */
  if (!real_bitree_is_eob(node)) {
    if (real_list_ins_next(list, real_list_tail(list),
			     real_bitree_data(node)) != 0) {
      return -1;
    }

    if (!real_bitree_is_eob(real_bitree_left(node))) {
      if (real_preorder(real_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (!real_bitree_is_eob(real_bitree_right(node))) {
      if (real_preorder(real_bitree_right(node), list) != 0) {
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

int real_inorder(real_bitreenode_t *node, real_list_t *list) {

  /* Load the list with an real_inorder listing of the tree. */
  if (!real_bitree_is_eob(node)) {

    if (!real_bitree_is_eob(real_bitree_left(node))) {
      if (real_inorder(real_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (real_list_ins_next(list, real_list_tail(list),
			      real_bitree_data(node)) != 0) {
      return -1;
    }

    if (!real_bitree_is_eob(real_bitree_right(node))) {
      if (real_inorder(real_bitree_right(node), list) != 0) {
	return -1;
      }
    }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ------------------------------- real_postorder ----------------------  *
*                                                                            *
*****************************************************************************/

int real_postorder(real_bitreenode_t *node, real_list_t *list) {

  /* Load the list with a postorder listing of the tree. */
  if (!real_bitree_is_eob(node)) {

    if (!real_bitree_is_eob(real_bitree_left(node))) {
      if (real_postorder(real_bitree_left(node), list) != 0) {
	return -1;
      }
    }

    if (!real_bitree_is_eob(real_bitree_right(node))) {
      if (real_postorder(real_bitree_right(node), list) != 0) {
	return -1;
      }
    }

    if (real_list_ins_next(list, real_list_tail(list),
			      real_bitree_data(node)) != 0) {
      return -1;
    }
  }

  return 0;
}

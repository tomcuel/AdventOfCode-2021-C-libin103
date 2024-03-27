/*****************************************************************************
*                                                                            *
*  ------------------------------- bitree.c -------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "integer_bitree.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------ bitree_init -----------------------------  *
*                                                                            *
*****************************************************************************/

void integer_bitree_init(integer_bitree_t *tree) {
  /* Initialize the binary tree. */
  tree->size = 0;
  tree->root = NULL;
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bitree_destroy ----------------------------  *
*                                                                            *
*****************************************************************************/

void integer_bitree_destroy(integer_bitree_t *tree) {

  /* Remove all the nodes from the tree. */
  integer_bitree_rem_left(tree, NULL);

  /* No operations are allowed now, but clear the structure as a precaution. */
  memset(tree, 0, sizeof(integer_bitree_t));
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bitree_ins_left ---------------------------  *
*                                                                            *
*****************************************************************************/

int integer_bitree_ins_left(integer_bitree_t *tree,
			   integer_bitreenode_t *node, int data) {

  integer_bitreenode_t *new_node;
  integer_bitreenode_t **position;

  /* Determine where to insert the node. */
  if (node == NULL) {
   /* Allow insertion at the root only in an empty tree. */
    if (integer_bitree_size(tree) > 0) {
      return -1;
    }
    position = &tree->root;
  }
  else {
    /* Normally allow insertion only at the end of a branch. */
    if (integer_bitree_left(node) != NULL) {
      return -1;
    }
    position = &node->left;
  }

  /* Allocate storage for the node. */
  new_node = malloc(sizeof(integer_bitreenode_t));
  if (new_node == NULL) {
    return -1;
  }

  /* Insert the node into the tree. */
  new_node->data = data;
  new_node->left = NULL;
  new_node->right = NULL;
  *position = new_node;

  /* Adjust the size of the tree to account for the inserted node. */
  tree->size++;

  return 0;
}

/*****************************************************************************
*                                                                            *
*  --------------------------- bitree_ins_right ---------------------------  *
*                                                                            *
*****************************************************************************/

int integer_bitree_ins_right(integer_bitree_t *tree,
			    integer_bitreenode_t *node, int data) {

  integer_bitreenode_t *new_node;
  integer_bitreenode_t **position;

  /* Determine where to insert the node. */
  if (node == NULL) {
   /* Allow insertion at the root only in an empty tree. */
    if (integer_bitree_size(tree) > 0) {
      return -1;
    }
    position = &tree->root;
   }
  else {
   /* Normally allow insertion only at the end of a branch. */
    if (integer_bitree_right(node) != NULL) {
      return -1;
    }
    position = &node->right;
  }

  /* Allocate storage for the node. */
  new_node = malloc(sizeof(integer_bitreenode_t));
  if (new_node == NULL) {
    return -1;
  }
  /* Insert the node into the tree. */

  new_node->data = data;
  new_node->left = NULL;
  new_node->right = NULL;
  *position = new_node;

  /* Adjust the size of the tree to account for the inserted node. */
  tree->size++;

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bitree_rem_left ---------------------------  *
*                                                                            *
*****************************************************************************/

void integer_bitree_rem_left(integer_bitree_t *tree, integer_bitreenode_t *node) {

  integer_bitreenode_t        **position;

  /* Do not allow removal from an empty tree. */
  if (integer_bitree_size(tree) == 0)
    return;

  /* Determine where to remove nodes. */
  if (node == NULL) {
    position = &tree->root;
  }
  else {
    position = &node->left;
  }

  /* Remove the nodes. */
  if (*position != NULL) {

   integer_bitree_rem_left(tree, *position);
   integer_bitree_rem_right(tree, *position);

   free(*position);
   *position = NULL;

   /* Adjust the size of the tree to account for the removed node. */
   tree->size--;

  }

  return;
}

/*****************************************************************************
*                                                                            *
*  --------------------------- bitree_rem_right ---------------------------  *
*                                                                            *
*****************************************************************************/

void integer_bitree_rem_right(integer_bitree_t *tree, integer_bitreenode_t *node) {

  integer_bitreenode_t **position;

  /* Do not allow removal from an empty tree. */
  if (integer_bitree_size(tree) == 0) {
    return;
  }

  /* Determine where to remove nodes. */
  if (node == NULL) {
    position = &tree->root;
  }
  else {
    position = &node->right;
  }

  /* Remove the nodes. */
  if (*position != NULL) {

   integer_bitree_rem_left(tree, *position);
   integer_bitree_rem_right(tree, *position);
   free(*position);
   *position = NULL;

   /* Adjust the size of the tree to account for the removed node. */
   tree->size--;
  }

  return;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_merge -----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_bitree_merge(integer_bitree_t *merge, integer_bitree_t *left,
			integer_bitree_t *right, int data) {

  /* Initialize the merged tree. */

  integer_bitree_init(merge);

  /* Insert the data for the root node of the merged tree. */
  if (integer_bitree_ins_left(merge, NULL, data) != 0) {
    integer_bitree_destroy(merge);
    return -1;
  }

  /* Merge the two binary trees into a single binary tree. */
  integer_bitree_root(merge)->left = integer_bitree_root(left);
  integer_bitree_root(merge)->right = integer_bitree_root(right);

  /* Adjust the size of the new binary tree. */
  merge->size = integer_bitree_size(merge) + integer_bitree_size(left)
    + integer_bitree_size(right);

  /* Do not let the original trees access the merged nodes. */
  left->root = NULL;
  left->size = 0;
  right->root = NULL;
  right->size = 0;

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_size ------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_bitree_size(integer_bitree_t *tree) {
  return tree->size;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_root ------------------------------  *
*                                                                            *
*****************************************************************************/

integer_bitreenode_t* integer_bitree_root(integer_bitree_t *tree) {
  return tree->root;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_is_eob ----------------------------  *
*                                                                            *
*****************************************************************************/

bool integer_bitree_is_eob(integer_bitreenode_t *node) {
  return node==NULL;
}


/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_is_leaf ---------------------------  *
*                                                                            *
*****************************************************************************/

bool integer_bitree_is_leaf(integer_bitreenode_t *node) {
  return node->left==NULL && node->right==NULL;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_data ------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_bitree_data(integer_bitreenode_t *node) {
  return node->data;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_left ------------------------------  *
*                                                                            *
*****************************************************************************/

integer_bitreenode_t* integer_bitree_left(integer_bitreenode_t *node) {
  return node->left;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_right ------------------------------  *
*                                                                            *
*****************************************************************************/

integer_bitreenode_t* integer_bitree_right(integer_bitreenode_t *node) {
  return node->right;
}

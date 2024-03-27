/*****************************************************************************
*                                                                            *
*  ------------------------------- bitree.c -------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "real_bitree.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------ bitree_init -----------------------------  *
*                                                                            *
*****************************************************************************/

void real_bitree_init(real_bitree_t *tree) {
  /* Initialize the binary tree. */
  tree->size = 0;
  tree->root = NULL;
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bitree_destroy ----------------------------  *
*                                                                            *
*****************************************************************************/

void real_bitree_destroy(real_bitree_t *tree) {

  /* Remove all the nodes from the tree. */
  real_bitree_rem_left(tree, NULL);

  /* No operations are allowed now, but clear the structure as a precaution. */
  memset(tree, 0, sizeof(real_bitree_t));
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bitree_ins_left ---------------------------  *
*                                                                            *
*****************************************************************************/

int real_bitree_ins_left(real_bitree_t *tree,
			   real_bitreenode_t *node, double data) {

  real_bitreenode_t *new_node;
  real_bitreenode_t **position;

  /* Determine where to insert the node. */
  if (node == NULL) {
   /* Allow insertion at the root only in an empty tree. */
    if (real_bitree_size(tree) > 0) {
      return -1;
    }
    position = &tree->root;
  }
  else {
    /* Normally allow insertion only at the end of a branch. */
    if (real_bitree_left(node) != NULL) {
      return -1;
    }
    position = &node->left;
  }

  /* Allocate storage for the node. */
  new_node = malloc(sizeof(real_bitreenode_t));
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

int real_bitree_ins_right(real_bitree_t *tree,
			    real_bitreenode_t *node, double data) {

  real_bitreenode_t *new_node;
  real_bitreenode_t **position;

  /* Determine where to insert the node. */
  if (node == NULL) {
   /* Allow insertion at the root only in an empty tree. */
    if (real_bitree_size(tree) > 0) {
      return -1;
    }
    position = &tree->root;
   }
  else {
   /* Normally allow insertion only at the end of a branch. */
    if (real_bitree_right(node) != NULL) {
      return -1;
    }
    position = &node->right;
  }

  /* Allocate storage for the node. */
  new_node = malloc(sizeof(real_bitreenode_t));
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

void real_bitree_rem_left(real_bitree_t *tree, real_bitreenode_t *node) {

  real_bitreenode_t        **position;

  /* Do not allow removal from an empty tree. */
  if (real_bitree_size(tree) == 0)
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

   real_bitree_rem_left(tree, *position);
   real_bitree_rem_right(tree, *position);

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

void real_bitree_rem_right(real_bitree_t *tree, real_bitreenode_t *node) {

  real_bitreenode_t **position;

  /* Do not allow removal from an empty tree. */
  if (real_bitree_size(tree) == 0) {
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

   real_bitree_rem_left(tree, *position);
   real_bitree_rem_right(tree, *position);
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

int real_bitree_merge(real_bitree_t *merge, real_bitree_t *left,
			real_bitree_t *right, double data) {

  /* Initialize the merged tree. */

  real_bitree_init(merge);

  /* Insert the data for the root node of the merged tree. */
  if (real_bitree_ins_left(merge, NULL, data) != 0) {
    real_bitree_destroy(merge);
    return -1;
  }

  /* Merge the two binary trees into a single binary tree. */
  real_bitree_root(merge)->left = real_bitree_root(left);
  real_bitree_root(merge)->right = real_bitree_root(right);

  /* Adjust the size of the new binary tree. */
  merge->size = real_bitree_size(merge) + real_bitree_size(left)
    + real_bitree_size(right);

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

int real_bitree_size(real_bitree_t *tree) {
  return tree->size;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_root ------------------------------  *
*                                                                            *
*****************************************************************************/

real_bitreenode_t* real_bitree_root(real_bitree_t *tree) {
  return tree->root;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_is_eob ----------------------------  *
*                                                                            *
*****************************************************************************/

bool real_bitree_is_eob(real_bitreenode_t *node) {
  return node==NULL;
}


/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_is_leaf ---------------------------  *
*                                                                            *
*****************************************************************************/

bool real_bitree_is_leaf(real_bitreenode_t *node) {
  return node->left==NULL && node->right==NULL;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_data ------------------------------  *
*                                                                            *
*****************************************************************************/

double real_bitree_data(real_bitreenode_t *node) {
  return node->data;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_left ------------------------------  *
*                                                                            *
*****************************************************************************/

real_bitreenode_t* real_bitree_left(real_bitreenode_t *node) {
  return node->left;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_right ------------------------------  *
*                                                                            *
*****************************************************************************/

real_bitreenode_t* real_bitree_right(real_bitreenode_t *node) {
  return node->right;
}

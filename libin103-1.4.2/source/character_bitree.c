/*****************************************************************************
*                                                                            *
*  ------------------------------- bitree.c -------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "character_bitree.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------ bitree_init -----------------------------  *
*                                                                            *
*****************************************************************************/

void character_bitree_init(character_bitree_t *tree) {
  /* Initialize the binary tree. */
  tree->size = 0;
  tree->root = NULL;
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bitree_destroy ----------------------------  *
*                                                                            *
*****************************************************************************/

void character_bitree_destroy(character_bitree_t *tree) {

  /* Remove all the nodes from the tree. */
  character_bitree_rem_left(tree, NULL);

  /* No operations are allowed now, but clear the structure as a precaution. */
  memset(tree, 0, sizeof(character_bitree_t));
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bitree_ins_left ---------------------------  *
*                                                                            *
*****************************************************************************/

int character_bitree_ins_left(character_bitree_t *tree,
			   character_bitreenode_t *node, char data) {

  character_bitreenode_t *new_node;
  character_bitreenode_t **position;

  /* Determine where to insert the node. */
  if (node == NULL) {
   /* Allow insertion at the root only in an empty tree. */
    if (character_bitree_size(tree) > 0) {
      return -1;
    }
    position = &tree->root;
  }
  else {
    /* Normally allow insertion only at the end of a branch. */
    if (character_bitree_left(node) != NULL) {
      return -1;
    }
    position = &node->left;
  }

  /* Allocate storage for the node. */
  new_node = malloc(sizeof(character_bitreenode_t));
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

int character_bitree_ins_right(character_bitree_t *tree,
			    character_bitreenode_t *node, char data) {

  character_bitreenode_t *new_node;
  character_bitreenode_t **position;

  /* Determine where to insert the node. */
  if (node == NULL) {
   /* Allow insertion at the root only in an empty tree. */
    if (character_bitree_size(tree) > 0) {
      return -1;
    }
    position = &tree->root;
   }
  else {
   /* Normally allow insertion only at the end of a branch. */
    if (character_bitree_right(node) != NULL) {
      return -1;
    }
    position = &node->right;
  }

  /* Allocate storage for the node. */
  new_node = malloc(sizeof(character_bitreenode_t));
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

void character_bitree_rem_left(character_bitree_t *tree, character_bitreenode_t *node) {

  character_bitreenode_t        **position;

  /* Do not allow removal from an empty tree. */
  if (character_bitree_size(tree) == 0)
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

   character_bitree_rem_left(tree, *position);
   character_bitree_rem_right(tree, *position);

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

void character_bitree_rem_right(character_bitree_t *tree, character_bitreenode_t *node) {

  character_bitreenode_t **position;

  /* Do not allow removal from an empty tree. */
  if (character_bitree_size(tree) == 0) {
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

   character_bitree_rem_left(tree, *position);
   character_bitree_rem_right(tree, *position);
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

int character_bitree_merge(character_bitree_t *merge, character_bitree_t *left,
			character_bitree_t *right, char data) {

  /* Initialize the merged tree. */

  character_bitree_init(merge);

  /* Insert the data for the root node of the merged tree. */
  if (character_bitree_ins_left(merge, NULL, data) != 0) {
    character_bitree_destroy(merge);
    return -1;
  }

  /* Merge the two binary trees into a single binary tree. */
  character_bitree_root(merge)->left = character_bitree_root(left);
  character_bitree_root(merge)->right = character_bitree_root(right);

  /* Adjust the size of the new binary tree. */
  merge->size = character_bitree_size(merge) + character_bitree_size(left)
    + character_bitree_size(right);

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

int character_bitree_size(character_bitree_t *tree) {
  return tree->size;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_root ------------------------------  *
*                                                                            *
*****************************************************************************/

character_bitreenode_t* character_bitree_root(character_bitree_t *tree) {
  return tree->root;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_is_eob ----------------------------  *
*                                                                            *
*****************************************************************************/

bool character_bitree_is_eob(character_bitreenode_t *node) {
  return node==NULL;
}


/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_is_leaf ---------------------------  *
*                                                                            *
*****************************************************************************/

bool character_bitree_is_leaf(character_bitreenode_t *node) {
  return node->left==NULL && node->right==NULL;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_data ------------------------------  *
*                                                                            *
*****************************************************************************/

char character_bitree_data(character_bitreenode_t *node) {
  return node->data;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_left ------------------------------  *
*                                                                            *
*****************************************************************************/

character_bitreenode_t* character_bitree_left(character_bitreenode_t *node) {
  return node->left;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bitree_right ------------------------------  *
*                                                                            *
*****************************************************************************/

character_bitreenode_t* character_bitree_right(character_bitreenode_t *node) {
  return node->right;
}

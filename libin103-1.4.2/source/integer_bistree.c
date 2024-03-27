
/*****************************************************************************
*                                                                            *
*  ------------------------------- bistree.c ------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "integer_bistree.h"
#include "bitree.h"

#define compare(a,b) (((a)<(b))?-1:((a)>(b)?1:0))

static void* generic_build (const void *avl_data) {
  integer_avlnode_t *new_avl_data = malloc(sizeof(integer_avlnode_t));
  assert(new_avl_data!=NULL);
  new_avl_data->factor = ((integer_avlnode_t *)avl_data)->factor;
  new_avl_data->hidden = ((integer_avlnode_t *)avl_data)->hidden;
  new_avl_data->data = ((integer_avlnode_t *)avl_data)->data;
  return (void*) new_avl_data;
}

static void generic_destroy_right(integer_bistree_t *tree,
				  generic_bitreenode_t *node);

/*****************************************************************************
 *                                                                            *
 *  ------------------------------ rotate_left -----------------------------  *
 *                                                                            *
 *****************************************************************************/

static void generic_rotate_left(generic_bitreenode_t **node) {
  /* printf ("%s: generic_rotate_left\n", __FILE__); */
  generic_bitreenode_t *left;
  generic_bitreenode_t *grandchild;

  left = (*node)->left;

  integer_avlnode_t* nodeLeft = generic_bitree_data(left);
  if (nodeLeft->factor == integer_AVL_LFT_HEAVY) {
    /* printf ("%s: LL rotation\n", __FILE__); */
    /* Perform an LL rotation. */
    /* generic_bitreenode_t* leftLeft = generic_bitree_left(*node); */
    /* leftLeft = generic_bitree_right(left); */
    (*node)->left = left->right;

    /* generic_bitreenode_t* leftRight = generic_bitree_right(left); */
    /* leftRight = *node; */
    left->right=*node;

    ((integer_avlnode_t *)(*node)->data)->factor = integer_AVL_BALANCED;
    ((integer_avlnode_t *)left->data)->factor = integer_AVL_BALANCED;
    *node = left;
  }
  else {
    /* printf ("%s: LR rotation\n", __FILE__); */
    /* Perform an LR rotation. */
    /* grandchild = generic_bitree_right(left); */
    grandchild = left->right;

    /* generic_bitreenode_t* leftRight = generic_bitree_right(left); */
    /* leftRight = generic_bitree_left(grandchild); */
    left->right = grandchild->left;

    /* generic_bitreenode_t* leftG = generic_bitree_left(grandchild); */
    /* leftG = left; */
    grandchild->left = left;

    /* generic_bitreenode_t* leftN =  generic_bitree_left(*node); */
    /* leftN = generic_bitree_right(grandchild); */
    (*node)->left = grandchild->right;

    /* generic_bitreenode_t* rightG = generic_bitree_right(grandchild); */
    /* rightG = *node; */
    grandchild->right = *node;

    switch (((integer_avlnode_t *)generic_bitree_data(grandchild))->factor) {

    case integer_AVL_LFT_HEAVY:
      ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_RGT_HEAVY;
      ((integer_avlnode_t *)generic_bitree_data(left))->factor = integer_AVL_BALANCED;
      break;

    case integer_AVL_BALANCED:
      ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_BALANCED;
      ((integer_avlnode_t *)generic_bitree_data(left))->factor = integer_AVL_BALANCED;
      break;

    case integer_AVL_RGT_HEAVY:
      ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_BALANCED;
      ((integer_avlnode_t *)generic_bitree_data(left))->factor = integer_AVL_LFT_HEAVY;
      break;
    }

    ((integer_avlnode_t *)generic_bitree_data(grandchild))->factor = integer_AVL_BALANCED;
    *node = grandchild;
  }
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- rotate_right -----------------------------  *
*                                                                            *
*****************************************************************************/

static void generic_rotate_right(generic_bitreenode_t **node) {
  /* printf ("%s: generic_rotate_right\n", __FILE__); */

  generic_bitreenode_t *right;
  generic_bitreenode_t *grandchild;

  right = (*node)->right;/* generic_bitree_right(*node); */

  integer_avlnode_t * nodeAvl = generic_bitree_data(right);
  if (nodeAvl->factor == integer_AVL_RGT_HEAVY) {
   /* Perform an RR rotation. */
    /* printf ("%s: RR rotation: *node=%p et right=%p\n", __FILE__, (void*)*node, (void*)right); */
    /* generic_bitreenode_t *rightN = generic_bitree_right(*node); */
    /* generic_bitreenode_t *rightLeft = generic_bitree_left(right); */
    /* rightN  = rightLeft */ (*node)->right = right->left;
    /* rightLeft = *node; */ right->left = *node;

    ((integer_avlnode_t *)(*node)->data)->factor = integer_AVL_BALANCED;
    ((integer_avlnode_t *)right->data)->factor = integer_AVL_BALANCED;
    *node = right;
    /* printf ("%s: RR rotation: *node=%p et right=%p\n", __FILE__, (void*)*node, (void*)right); */
  }
  else {
   /* Perform an RL rotation. */
    /* printf ("%s: RL rotation\n", __FILE__); */
   /* grandchild = generic_bitree_left(right); */
    grandchild = right->left;

   /* generic_bitreenode_t *rightLeft = generic_bitree_left(right); */
   /* rightLeft = generic_bitree_right(grandchild); */
    right->left = grandchild->right ;

   /* generic_bitreenode_t *rightG = generic_bitree_right(grandchild); */
   /* rightG = right; */
    grandchild->right = right;

   /* generic_bitreenode_t *rightN = generic_bitree_right(*node); */
   /* rightN= generic_bitree_left(grandchild); */
    (*node)->right = grandchild->left;

   /* generic_bitreenode_t *leftG = generic_bitree_left(grandchild); */
   /* leftG= *node; */
    grandchild->left = *node;

   switch (((integer_avlnode_t *)generic_bitree_data(grandchild))->factor) {
   case integer_AVL_LFT_HEAVY:
     ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_BALANCED;
     ((integer_avlnode_t *)generic_bitree_data(right))->factor = integer_AVL_RGT_HEAVY;
     break;

   case integer_AVL_BALANCED:
     ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_BALANCED;
     ((integer_avlnode_t *)generic_bitree_data(right))->factor = integer_AVL_BALANCED;
     break;

   case integer_AVL_RGT_HEAVY:
     ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_LFT_HEAVY;
     ((integer_avlnode_t *)generic_bitree_data(right))->factor = integer_AVL_BALANCED;
     break;
   }

   ((integer_avlnode_t *)generic_bitree_data(grandchild))->factor = integer_AVL_BALANCED;
   *node = grandchild;
  }
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- destroy_left -----------------------------  *
*                                                                            *
*****************************************************************************/

static void generic_destroy_left(integer_bistree_t *tree,
				 generic_bitreenode_t *node)
{

  generic_bitreenode_t **position;

  /* Do not allow destruction of an empty tree. */

  if (generic_bitree_size(tree) == 0) {
    return;
  }

  /* Determine where to destroy nodes. */
  if (node == NULL) {
    position = &tree->root;
  }
  else {
    position = &node->left;
  }

  /* Destroy the nodes. */
  if (*position != NULL) {
    generic_destroy_left(tree, *position);
    generic_destroy_right(tree, *position);

    /* if (tree->destroy != NULL) { */
    /*   /\* Call a user-defined function to free dynamically allocated data. *\/ */
    /*   tree->destroy(((integer_avlnode_t *)(*position)->data)->data); */
   /* } */

    /* Free the AVL data in the node, then free the node itself. */
    free((*position)->data);
    free(*position);
    *position = NULL;

    /* Adjust the size of the tree to account for the destroyed node. */
    tree->size--;
  }
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- destroy_right ----------------------------  *
*                                                                            *
*****************************************************************************/

static void generic_destroy_right(integer_bistree_t *tree,
				  generic_bitreenode_t *node)
{

  generic_bitreenode_t **position;

  /* Do not allow destruction of an empty tree. */
  if (generic_bitree_size(tree) == 0) {
    return;
  }

  /* Determine where to destroy nodes. */
  if (node == NULL) {
    position = &tree->root;
  }
  else {
   position = &node->right;
  }

  /* Destroy the nodes. */
  if (*position != NULL) {
    generic_destroy_left(tree, *position);
    generic_destroy_right(tree, *position);

    if (tree->destroy != NULL) {
      /* Call a user-defined function to free dynamically allocated data. */
      /* tree->destroy(((integer_avlnode_t *)(*position)->data)->data); */
    }

    /* Free the AVL data in the node, then free the node itself. */
    free((*position)->data);
    free(*position);
    *position = NULL;

    /* Adjust the size of the tree to account for the destroyed node. */
    tree->size--;
  }
}

/*****************************************************************************
*                                                                            *
*  ------------------------ generic_insert --------------------------------  *
*                                                                            *
*****************************************************************************/

static int generic_insert(integer_bistree_t *tree,
			  generic_bitreenode_t **node,
			  int data,
			  int *balanced)
{
  integer_avlnode_t *avl_data;
  int cmpval;
  int retval;

  /* Insert the data into the tree. */
  if (generic_bitree_is_eob(*node)) {
    /* printf("%s: %s leaf\n", __FILE__, __func__); */
    /* Handle insertion into an empty tree. */
    avl_data = malloc(sizeof(integer_avlnode_t));
    if (avl_data == NULL) {
      return -1;
    }
    avl_data->factor = integer_AVL_BALANCED;
    avl_data->hidden = 0;
    avl_data->data = data;

    int code = generic_bitree_ins_left(tree, *node, avl_data);
    free (avl_data);
    return code;
  }

  else {
    /* Handle insertion into a tree that is not empty. */

    integer_avlnode_t *tempNode =  generic_bitree_data(*node);
    cmpval = compare(data, tempNode->data);

    if (cmpval < 0) {
      /* printf("%s: %s go left\n", __FILE__, __func__); */
      /* Move to the left. */
      if (generic_bitree_is_eob(generic_bitree_left(*node))) {

	avl_data = malloc(sizeof(integer_avlnode_t));
	if (avl_data == NULL) {
            return -1;
	}

	avl_data->factor = integer_AVL_BALANCED;
	avl_data->hidden = 0;
	avl_data->data = data;

	if (generic_bitree_ins_left(tree, *node, avl_data) != 0) {
	  return -1;
	}
	//free (avl_data);
	*balanced = 0;

      }

      else {
	/* generic_bitreenode_t *leftN = generic_bitree_left(*node); */
	retval = generic_insert(tree, &((*node)->left), data, balanced);
	if (retval != 0) {
	  return retval;
	}
      }

      /* Ensure that the tree remains balanced. */

      if (!(*balanced)) {

	switch (((integer_avlnode_t *)generic_bitree_data(*node))->factor) {

	case integer_AVL_LFT_HEAVY:
	  generic_rotate_left(node);
	  *balanced = 1;
	  break;

	case integer_AVL_BALANCED:
	  ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_LFT_HEAVY;
	  break;

	case integer_AVL_RGT_HEAVY:
	  ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_BALANCED;
	  *balanced = 1;

	}
      }

    } /* if (cmpval < 0) */
    else if (cmpval > 0) {
      /* printf("%s: %s go right\n", __FILE__, __func__); */
      /* Move to the right. */

      if (generic_bitree_is_eob(generic_bitree_right(*node))) {
	avl_data = malloc(sizeof(integer_avlnode_t));
	if (avl_data == NULL) {
            return -1;
	}

	avl_data->factor = integer_AVL_BALANCED;
	avl_data->hidden = 0;
	avl_data->data = data;

	if (generic_bitree_ins_right(tree, *node, avl_data) != 0) {
	  return -1;
	}
	free (avl_data);
	*balanced = 0;
      }
      else {
	/* generic_bitreenode_t* rightN = generic_bitree_right(*node); */
	retval = generic_insert(tree, &((*node)->right), data, balanced);
	if (retval != 0) {
	  return retval;
	}
      }

      /* Ensure that the tree remains balanced. */
      if (!(*balanced)) {
	switch (((integer_avlnode_t *)generic_bitree_data(*node))->factor) {

	case integer_AVL_LFT_HEAVY:
	  ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_BALANCED;
	  *balanced = 1;
	  break;

	case integer_AVL_BALANCED:
	  ((integer_avlnode_t *)generic_bitree_data(*node))->factor = integer_AVL_RGT_HEAVY;
	  break;

	case integer_AVL_RGT_HEAVY:
	  generic_rotate_right(node);
	  *balanced = 1;
	}
      }

    } /* if (cmpval > 0) */
    else {
      /* printf("%s: %s data already in tree ignore\n", __FILE__, __func__); */
      /* Handle finding a copy of the data. */
      if (!((integer_avlnode_t *)generic_bitree_data(*node))->hidden) {

         /* Do nothing since the data is in the tree and not hidden. */
	return 1;
      }
      else {
	/* Insert the new data and mark it as not hidden. */
	if (tree->destroy != NULL) {
	  /* Destroy the hidden data since it is being replaced. */
	  /* tree->destroy(((integer_avlnode_t *)generic_bitree_data(*node))->data); */
	}

	((integer_avlnode_t *)generic_bitree_data(*node))->data = data;
	((integer_avlnode_t *)generic_bitree_data(*node))->hidden = 0;

	/* Do not rebalance because the tree structure is unchanged. */
	*balanced = 1;
      }
    }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  --------------------------------- hide ---------------------------------  *
*                                                                            *
*****************************************************************************/

static int generic_hide(integer_bistree_t *tree,
			generic_bitreenode_t *node,
			int data)
{

  int cmpval;
  int retval;

  if (generic_bitree_is_eob(node)) {
    /* Return that the data was not found. */
    return -1;
  }

  integer_avlnode_t *tempNode = generic_bitree_data(node);
  cmpval = compare(data, tempNode->data);

  if (cmpval < 0) {
    /* Move to the left. */
    retval = generic_hide(tree, generic_bitree_left(node), data);
  }
  else if (cmpval > 0) {
   /* Move to the right. */
    retval = generic_hide(tree, generic_bitree_right(node), data);
  }
  else {
   /* Mark the node as hidden. */
   ((integer_avlnode_t *)generic_bitree_data(node))->hidden = 1;
   retval = 0;
  }

  return retval;
}

/*****************************************************************************
*                                                                            *
*  -------------------------------- lookup --------------------------------  *
*                                                                            *
*****************************************************************************/

static bool generic_lookup(integer_bistree_t *tree,
			  generic_bitreenode_t *node,
			  int data)
{

  int cmpval;
  int retval;

  if (generic_bitree_is_eob(node)) {
    /* Return that the data was not found. */
    return false;
  }

  integer_avlnode_t *tempNode = generic_bitree_data(node);
  cmpval = compare(data, tempNode->data);

  if (cmpval < 0) {
   /* Move to the left. */
    retval = generic_lookup(tree, generic_bitree_left(node), data);
   }
  else if (cmpval > 0) {
    /* Move to the right. */
    retval = generic_lookup(tree, generic_bitree_right(node), data);
   }
  else {
    if (!((integer_avlnode_t *)generic_bitree_data(node))->hidden) {

      /* Pass back the data from the tree. */
      /* *data = ((integer_avlnode_t *)generic_bitree_data(node))->data; */
      retval = true;
    }
    else {
      /* Return that the data was not found. */
      return false;
    }
  }

  return retval;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- bistree_init -----------------------------  *
*                                                                            *
*****************************************************************************/

void integer_bistree_init(integer_bistree_t *tree)
{
  /* Initialize the tree. */
  generic_bitree_init(tree, NULL, generic_build, free);
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bistree_destroy ---------------------------  *
*                                                                            *
*****************************************************************************/

void integer_bistree_destroy(integer_bistree_t *tree) {

  /* Destroy all nodes in the tree. */
  generic_destroy_left(tree, NULL);

  /* No operations are allowed now, but clear the structure as a precaution. */
  memset(tree, 0, sizeof(generic_bitree_t));
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bistree_insert ----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_bistree_insert(integer_bistree_t *tree, int data)
{
  int balanced = 0;
  return generic_insert(tree, &(tree->root), data, &balanced);
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bistree_remove ----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_bistree_remove(integer_bistree_t *tree,
			   int data)
{
  return generic_hide(tree, generic_bitree_root(tree), data);
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bistree_lookup ----------------------------  *
*                                                                            *
*****************************************************************************/

bool integer_bistree_lookup(integer_bistree_t *tree,
			   int data)
{
  return generic_lookup(tree, generic_bitree_root(tree), data);
}

/*****************************************************************************
*                                                                            *
*  ---------------------------- bistree_size ----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_bistree_size(integer_bistree_t *tree)
{
  assert(tree != NULL);
  return tree->size;
}

/*****************************************************************************
*                                                                            *
*  -------------------------------- heap.c --------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "integer_heap.h"

/*****************************************************************************
*                                                                            *
*  Define private macros used by the heap implementation.                    *
*                                                                            *
*****************************************************************************/

#define heap_parent(npos) ((int)(((npos) - 1) / 2))

#define heap_left(npos) (((npos) * 2) + 1)

#define heap_right(npos) (((npos) * 2) + 2)

/*****************************************************************************
*                                                                            *
*  ------------------------------- heap_init ------------------------------  *
*                                                                            *
*****************************************************************************/

void integer_heap_init(integer_heap_t *heap, integer_heap_type_t heap_type) {

  /* Initialize the heap.*/
  heap->size = 0;
  heap->heap_type = heap_type;
  heap->tree = NULL;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- heap_destroy -----------------------------  *
*                                                                            *
*****************************************************************************/

void integer_heap_destroy(integer_heap_t *heap) {
  heap->size = 0;
  /* Free the storage allocated for the heap.*/
  free(heap->tree);

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ heap_insert -----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_heap_insert(integer_heap_t *heap, int data) {

  int* tempTree;
  int temp;
  int ipos;
  int ppos;

  /* Allocate storage for the node.*/
  tempTree = realloc(heap->tree, (integer_heap_size(heap) + 1) * sizeof(int));
  if (tempTree == NULL) {
    return -1;
  }
  else {
    heap->tree = tempTree;
  }

  /* Insert the node after the last node. */
  heap->tree[integer_heap_size(heap)] = data;

  /* Heapify the tree by pushing the contents of the new node upward. */
  ipos = integer_heap_size(heap);
  ppos = heap_parent(ipos);

  bool flag = false;
  if (heap->heap_type == integer_MAX_HEAP) {
    flag = heap->tree[ppos] < heap->tree[ipos];
  }
  else {
    flag = heap->tree[ppos] > heap->tree[ipos];
  }

  while (ipos > 0 && flag) {
    /* Swap the contents of the current node and its parent. */
    temp = heap->tree[ppos];
    heap->tree[ppos] = heap->tree[ipos];
    heap->tree[ipos] = temp;

    /* Move up one level in the tree to continue heapifying. */
    ipos = ppos;
    ppos = heap_parent(ipos);

    flag = false;
    if (heap->heap_type == integer_MAX_HEAP) {
      flag = heap->tree[ppos] < heap->tree[ipos];
    }
    else {
      flag = heap->tree[ppos] > heap->tree[ipos];
    }
  }

  /* Adjust the size of the heap to account for the inserted node. */
  heap->size++;

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- heap_extract -----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_heap_extract(integer_heap_t *heap, int *data) {
  int save;
  int *tempTree;
  int temp;
  int ipos;
  int lpos;
  int rpos;
  int mpos;
  bool flag;

  /* Do not allow extraction from an empty heap. */
  if (integer_heap_size(heap) == 0) {
    return -1;
  }

  /* Extract the node at the top of the heap. */
  *data = heap->tree[0];

  /* Adjust the storage used by the heap. */
  save = heap->tree[integer_heap_size(heap) - 1];

  if (integer_heap_size(heap) - 1 > 0) {
    tempTree = realloc(heap->tree, (integer_heap_size(heap)-1) * sizeof(int));
    if (tempTree == NULL) {
      return -1;
    }
    else {
      heap->tree = tempTree;
    }

    /* Adjust the size of the heap to account for the extracted node. */
    heap->size--;
  }
  else {
    /* Manage the heap when extracting the last node. */
    free(heap->tree);
    heap->tree = NULL;
    heap->size = 0;
    return 0;
  }

  /* Copy the last node to the top. */
  heap->tree[0] = save;

  /* Heapify the tree by pushing the contents of the new top downward. */
  ipos = 0;
  lpos = heap_left(ipos);
  rpos = heap_right(ipos);

  while (1) {
    /* Select the child to swap with the current node. */
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);

    if (heap->heap_type == integer_MAX_HEAP) {
      flag = heap->tree[lpos] > heap-> tree[ipos];
    }
    else {
      flag = heap->tree[lpos] < heap-> tree[ipos];
    }

    if (lpos < integer_heap_size(heap) && flag) {
      mpos = lpos;
    }
    else {
      mpos = ipos;
    }

    if (heap->heap_type == integer_MAX_HEAP) {
      flag = heap->tree[rpos] > heap->tree[mpos];
    }
    else {
      flag = heap->tree[rpos] < heap->tree[mpos];
    }

    if (rpos < integer_heap_size(heap) && flag) {
      mpos = rpos;
    }

    /* When mpos is ipos, the heap property has been restored. */
    if (mpos == ipos) {
      break;
    }
   else {
      /* Swap the contents of the current node and the selected child. */
      temp = heap->tree[mpos];
      heap->tree[mpos] = heap->tree[ipos];
      heap->tree[ipos] = temp;

      /* Move down one level in the tree to continue heapifying. */
      ipos = mpos;
   }
  }

  return 0;
}

/*****************************************************************************
*                                                                            *
*  ------------------------------- heap_size ------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_heap_size(integer_heap_t *heap) {
  return heap -> size;
}

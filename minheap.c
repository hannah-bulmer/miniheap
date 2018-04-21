#include <stdlib.h>
#include "minheap.h"
#include <stdio.h>


struct minheap *minheap_create(void) {
  struct minheap *heap = malloc(sizeof(struct minheap));
  heap->len = 0;
  heap->maxlen = 1;
  heap->data = malloc(heap->maxlen * sizeof(int));
  return heap;
}


bool minheap_is_empty(const struct minheap *h) {
  return (h->len == 0);
}


// returns the index in the minheap where the next
// element could be placed to keep it tree-shaped
// as best as possible
int find_nearest_spot (struct minheap *h) {
  return h->len;
}


void resize_if_necessary (struct minheap *h) {
  if (h->len == h->maxlen) {
    h->maxlen *= 2;
    h->data = realloc(h->data, h->maxlen * sizeof(int));
  }
}


void minheap_insert(int item, struct minheap *h) {
  int nearest_spot = find_nearest_spot(h);
  h->len++;
  resize_if_necessary(h);
  h->data[nearest_spot] = item;
  int parent = (nearest_spot - 1) / 2;
  while (item < h->data[parent]) {
    //swap item and parent
    int temp = h->data[parent];
    h->data[parent] = item;
    h->data[nearest_spot] = temp;
    //make nearest spot be parent's spot
    nearest_spot = parent;
    parent = (nearest_spot - 1) / 2;
  }

}


int minheap_top(const struct minheap *h) {
  return (h->data[0]);
}


// returns the deepest most right node in the tree
int furthest_node(struct minheap *h) {
  return h->data[h->len-1];
}


int minheap_remove(struct minheap *h) {
  int root_node = h->data[0];
  int deepest_node = furthest_node(h);
  h->data[0] = deepest_node;
  //move down tree
  int current_index = 0;
  int left_child = 2*current_index + 1;
  int right_child = 2*current_index + 2;
  while (deepest_node > h->data[left_child] ||
         deepest_node > h->data[right_child]) {

    if (left_child >= h->len || right_child >= h->len) break;

    if (h->data[right_child] < h->data[left_child] &&
        deepest_node > h->data[right_child]){
      //swap with right child
      int temp = h->data[right_child];
      h->data[right_child] = deepest_node;
      h->data[current_index] = temp;
      current_index = right_child;
    } else {
      //swap with left child
      int temp = h->data[left_child];
      h->data[left_child] = deepest_node;
      h->data[current_index] = temp;
      current_index = left_child;
    }
    left_child = 2*current_index + 1;
    right_child = 2*current_index + 2;

    if (left_child >= h->maxlen || right_child >= h->maxlen) break;
  }
  h->len --;
  return root_node;
}


void minheap_destroy(struct minheap *h) {
  free(h->data);
  free(h);
}


void heapsort(int a[], int len) {
  struct minheap *h = minheap_create();
  for (int i = 0; i < len; i ++) {
    minheap_insert(a[i], h);
  }
  for (int i = 0; i < len; i ++) {
    a[i] = minheap_remove(h);
  }
  minheap_destroy(h);
}

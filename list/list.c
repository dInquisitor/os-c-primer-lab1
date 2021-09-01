// list/list.c
// 
// Implementation for linked list.
//
// Ibukunoluwa Esan

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "list.h"

list_t *list_alloc() {
  list_t *l = malloc(sizeof(list_t));
  return l;
}
void list_free(list_t *l) {
  if (l->head == NULL) {return;}
  node_t* node = l->head;
  node_t* to_free = NULL;
  while (node != NULL) {
    to_free = node;
    node = to_free->next;
    free(to_free);
  }
}

void list_print(list_t *l) {
  if (l->head == NULL) {return;}
  node_t* node = l->head;
  while (node->next != NULL) {
    printf("%d -> ", node->value);
    node = node->next;
  }
  printf("%d\n", node->value);
}
int list_length(list_t *l) {
  int count = 0;
  if (l->head == NULL) {return count;}
  node_t* node = l->head;
  while (node != NULL) {
    ++count;
    node = node->next;
  }
  return count;
}

void list_add_to_back(list_t *l, elem value) {
  node_t* new_node = malloc(sizeof(node_t));
  new_node->value = value;
  if (l->head == NULL) {
    l->head = new_node;
    return;
  }
  node_t* node = l->head;
  while (node->next != NULL) {
    node = node->next;
  }
  node->next = new_node; 
}
void list_add_to_front(list_t *l, elem value) {
  node_t* new_node = malloc(sizeof(node_t));
  new_node->value = value;
  if (l->head == NULL) {
    l->head = new_node;
    return;
  }
  new_node->next = l->head;
  l->head = new_node;
}
void list_add_at_index(list_t *l, elem value, int index) {
  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }
  if (index > (list_length(l) - 1)) {
    list_add_to_back(l, value);
    return;
  }
  
  node_t* new_node = malloc(sizeof(node_t));
  new_node->value = value;
  node_t* node = l->head;
  for (int i = 0; i < (index - 1); ++i) {
    node = node->next;
  }
  node_t* curr_next = node->next;
  node->next = new_node;
  new_node->next = curr_next;
}

elem list_remove_from_back(list_t *l) {
  /*remove the last one*/
  /* Should we throw error here? */
  if (l->head == NULL) {return -1;}
  
  node_t* d_head = malloc(sizeof(node_t));
  d_head->next = l->head;
  node_t* node = d_head;
  while (node->next->next != NULL) {
    node = node->next;
  }
  elem val = node->next->value;
  free(node->next);
  node->next = NULL;
  /* we removed the actual head */
  if (d_head->next == NULL) {
    l->head = NULL;
  }
  return val;
}
elem list_remove_from_front(list_t *l) {
  /* remove the first one */
  if (l->head == NULL) {return -1;}
  elem val = l->head->value;
  node_t* to_free = l->head;
  l->head = l->head->next;
  free(to_free);
  return val;
}
elem list_remove_at_index(list_t *l, int index) {
  int len = list_length(l);
  if(index < 0 || index >= len) {return -1;}
  if(index == 0) {
    return list_remove_from_front(l);
  }
  if(index == len - 1) {
    return list_remove_from_back(l);
  }
  node_t* node = l->head;
  for (int i = 0; i < (index - 1); ++i) {
    node = node->next;
  }
  elem val = node->next->value;
  node_t* to_free = node->next;
  node->next = to_free->next;
  free(to_free);
  return val;
}

bool list_is_in(list_t *l, elem value) {
  return list_get_index_of(l, value) != -1; 
}

elem list_get_elem_at(list_t *l, int index) {
  int len = list_length(l);
   if(index < 0 || index >= len) {return -1;}
  if(index == 0) {
    return l->head->value;
  }
  node_t* node = l->head;
  for (int i = 0; i < index; ++i) {
    node = node->next;
  }
  return node->value;
}

int list_get_index_of(list_t *l, elem value) {
  if (l->head == NULL) {return -1;}
  int count = 0;
  node_t* node = l->head;
  while (node != NULL) {
    if (node->value == value) {
      return count;
    }
    ++count;
    node = node->next;
  }
  return -1;
}

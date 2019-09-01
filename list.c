#include "list.h"
#include <stdlib.h>


void list_init(list_t *self){
  self->head = NULL;
  self->tail = NULL;
  self->len = 0;
  self->iter = NULL;
 }

void list_append(list_t *self, void *value){
  node_t *newNode = malloc(sizeof(node_t));
  newNode->value = value;
  newNode->next = NULL;
  self->len++;
  if(self->len == 0){
    self->head = newNode;
    self->iter = newNode;
    return;
  } 
  self->tail->next = newNode;
  return;
}

void *list_obtain(list_t *self, size_t index) {
  if (index >= self->len) {
    return NULL;
  }
  node_t *node = self->head;
  for(int cont = 0; cont<index; cont++){
    node = node->next;
  }
  return node;
}

void* list_iter_next(list_t *self){
  node_t *aux = self->iter;
  if(self->iter == NULL) return NULL;
  self->iter = self->iter->next;
  return aux->value;
}

void list_iter_reset(list_t *self){
  self->iter = self->head;
  return;
}

size_t list_len(list_t *self){
  return self->len;
}

void list_uninit(list_t *self){
  node_t *aux = self->head;
  while (aux != NULL) {
    self->head = aux->next;
    free(aux);
    aux = self->head;
  }
}

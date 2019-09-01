#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include "list.h"

typedef struct node_t {
  void *value;
  struct node_t *next;
} node_t;

typedef struct {
  node_t *head;
  node_t *tail;
  size_t len;
  node_t *iter;
} list_t;

void list_init(list_t *self);

void list_append(list_t *self, void *value);

void* list_obtain(list_t *self, size_t index);

void* list_iter_next(list_t *self);

void list_iter_reset(list_t *self);

size_t list_len(list_t *self);

void list_uninit(list_t *self);

#endif

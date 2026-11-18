int map_set(map_t *map, char *key, void *data, int dsize)
{
  map_node_t **nodeptr;
  map_node_t *node;
  unsigned int newsize;
  int err;

  nodeptr = map_getref(map, key);
  if (nodeptr) {
    memcpy((*nodeptr)->data, data, dsize);
    return 0;
  }

  node = map_newnode(key, data, dsize);
  if (!node) goto fail;

  if (map->size >= map->maxfill) {
    if (map->maxfill > 0)
      newsize = map->maxfill << 1;
    else
      newsize = 1;

    err = map_resize(map, newsize);
    if (err) goto fail;
  } else {
    map_addnode(map, node);
    map->size++;
  }

  return 0;

fail:
  if (node) free(node);
  return -1;
}
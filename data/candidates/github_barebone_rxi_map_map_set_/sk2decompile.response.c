int map_set_(map_t *map, const char *key, void *val, int size) {
  map_node_t **np;
  map_node_t *node;
  np = map_getref(map, key);
  if (np) {
    memcpy((*np)->val, val, size);
    return 0;
  }
  node = map_newnode(key, val, size);
  if (!node) goto error;
  if (map->nnodes >= map->nsize) {
    int nsize = map->nsize ? map->nsize * 2 : 1;
    if (map_resize(map, nsize)) goto error;
  }
  map_addnode(map, node);
  map->nnodes++;
  return 0;
error:
  if (node) free(node);
  return -1;
}
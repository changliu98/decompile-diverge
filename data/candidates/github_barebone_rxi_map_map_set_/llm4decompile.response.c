int map_set_(map_t *m, char *key, void *value, int vsize)
{
  map_node_t **ref, *node;

  ref = map_getref(m, key);
  if (ref != NULL) {
    memcpy((*ref)->value, value, (size_t)vsize);
    return 0;
  }

  node = map_newnode(key, value, vsize);
  if (node == NULL)
    goto fail;

  if (m->nnodes >= m->nbuckets) {
    int nbuckets = (m->nbuckets == 0) ? 1 : m->nbuckets * 2;
    int err = map_resize(m, nbuckets);
    if (err != 0)
      goto fail;
  }

  map_addnode(m, node);
  m->nnodes++;
  return 0;

 fail:
  if (node != NULL)
    free(node);
  return -1;
}
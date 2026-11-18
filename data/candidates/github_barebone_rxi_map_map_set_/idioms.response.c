int map_set_(struct map_base *m, char *key, void *value, int vsize)
{
  struct map_node **nodep;
  struct map_node *new;
  int newsize;
  nodep = map_getref(m, key);
  if (nodep) {
    memcpy((*nodep)->value, value, vsize);
    return 0;
  }
  new = map_newnode(key, value, vsize);
  if (!new)
    goto fail;
  if (m->nnodes >= m->nbuckets) {
    if (m->nbuckets == 0)
      newsize = 1;
    else
      newsize = m->nbuckets * 2;
    if (map_resize(m, newsize))
      goto fail;
  }
  map_addnode(m, new);
  m->nnodes++;
  return 0;
fail:
  if (new)
    free(new);
  return -1;
}
int __cdecl map_set_(map_base_t *m, const char *key, void *value, int vsize)
{
  int v5; // [rsp+Ch] [rbp-44h]
  map_node_t *node; // [rsp+10h] [rbp-40h]
  map_node_t **next; // [rsp+18h] [rbp-38h]

  next = map_getref(m, key);
  if ( next )
  {
    memcpy((*next)->value, value, vsize);
    return 0;
  }
  else
  {
    node = map_newnode(key, value, vsize);
    if ( !node || m->nnodes >= m->nbuckets && (!m->nbuckets ? (v5 = 1) : (v5 = 2 * m->nbuckets), map_resize(m, v5)) )
    {
      if ( node )
        free(node);
      return -1;
    }
    else
    {
      map_addnode(m, node);
      ++m->nnodes;
      return 0;
    }
  }
}
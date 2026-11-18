int __cdecl map_set_(map_base_t *m, const char *key, void *value, int vsize)
{
  map_node_t **existing_node;
  map_node_t *new_node;
  int new_bucket_count;

  existing_node = map_getref(m, key);
  
  // If the key already exists, update its value
  if (existing_node)
  {
    memcpy((*existing_node)->value, value, vsize);
    return 0;
  }

  // Key doesn't exist, create a new node
  new_node = map_newnode(key, value, vsize);
  
  // Check for failure to create a node, or if we need to resize the map
  if (!new_node || (m->nnodes >= m->nbuckets && map_resize(m, m->nbuckets == 0 ? 1 : 2 * m->nbuckets)))
  {
    if (new_node)
      free(new_node);
    return -1;
  }

  // Successfully created a node and ensured enough buckets; add to map
  map_addnode(m, new_node);
  ++m->nnodes;
  
  return 0;
}
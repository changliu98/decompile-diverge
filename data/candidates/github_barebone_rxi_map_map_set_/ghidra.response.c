int map_set_(map_base_t *m,char *key,void *value,int vsize)

{
  int iVar1;
  map_node_t **ppmVar2;
  map_node_t *node_00;
  int local_4c;
  map_node_t *node;
  map_node_t **next;
  int err;
  int n;
  int vsize_local;
  void *value_local;
  char *key_local;
  map_base_t *m_local;
  int local_c;
  
  ppmVar2 = map_getref(m,key);
  if (ppmVar2 != (map_node_t **)0x0) {
    memcpy((*ppmVar2)->value,value,(long)vsize);
    return 0;
  }
  node_00 = map_newnode(key,value,vsize);
  if (node_00 == (map_node_t *)0x0) {
LAB_001014eb:
    if (node_00 != (map_node_t *)0x0) {
      free(node_00);
    }
    local_c = -1;
  }
  else {
    if (m->nbuckets <= m->nnodes) {
      if (m->nbuckets == 0) {
        local_4c = 1;
      }
      else {
        local_4c = m->nbuckets << 1;
      }
      iVar1 = map_resize(m,local_4c);
      if (iVar1 != 0) goto LAB_001014eb;
    }
    map_addnode(m,node_00);
    m->nnodes = m->nnodes + 1;
    local_c = 0;
  }
  return local_c;
}
size_t bnode_link_set_ref(size_t *link,size_t index)

{
  ulong uVar1;
  size_t index_local;
  size_t *link_local;
  
  uVar1 = *link & 1 | (index + 1) * 2;
  *link = uVar1;
  return uVar1;
}
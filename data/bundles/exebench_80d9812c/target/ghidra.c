size_t bnode_link_set_leaf(size_t *link)

{
  ulong uVar1;
  size_t *link_local;
  
  uVar1 = *link;
  *link = uVar1 & 1;
  return uVar1 & 1;
}
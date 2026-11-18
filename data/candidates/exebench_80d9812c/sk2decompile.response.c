void bnode_link_set_leaf(bnode_link* link) {
  unsigned int l = *(unsigned int*)link;
  l = l & 1;
  *(unsigned int*)link = l;
}
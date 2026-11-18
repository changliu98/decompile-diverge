size_t bnode_link_set_leaf(bnode_link* link)
{
  return ((link)->type = ((link)->type & 0x1));
}
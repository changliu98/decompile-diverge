size_t bnode_link_set_ref(bnode_link *link, size_t index)
{
  return *link = ((index + 1) << 1) | (*link & 1);
}
size_t __cdecl bnode_link_set_leaf(size_t *link)
{
  size_t is_leaf = *link & 1;
  *link = is_leaf;
  return is_leaf;
}
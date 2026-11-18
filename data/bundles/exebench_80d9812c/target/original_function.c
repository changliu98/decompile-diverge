size_t bnode_link_set_leaf(size_t *link)
{
  return *(link) = ( ((*(link)) & 1) | ( (0) ) );
}
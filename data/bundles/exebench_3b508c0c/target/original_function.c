size_t bnode_link_set_ref (size_t *link, size_t index)
{
  return *(link) = ( ((*(link)) & 1) | ( ((((index)) + 1) << 1) ) );
}
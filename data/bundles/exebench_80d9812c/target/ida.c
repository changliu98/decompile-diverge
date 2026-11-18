size_t __cdecl bnode_link_set_leaf(size_t *link)
{
  size_t result; // rax

  result = *link & 1;
  *link = result;
  return result;
}
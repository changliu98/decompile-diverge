size_t __cdecl bnode_link_set_ref(size_t *link, size_t index)
{
  // Preserve the lowest bit (flag) of the original link
  size_t preserved_flag = *link & 1;
  
  // Calculate the new reference value and combine it with the preserved flag
  size_t result = (index << 1) | preserved_flag;
  
  *link = result;
  return result;
}
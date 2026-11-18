size_t __cdecl bnode_link_set_ref(size_t *link, size_t index)
{
  size_t result; // rax

  result = (2 * (index + 1)) | *link & 1;
  *link = result;
  return result;
}
void modify_uint_refs_new_syntax(uint *first,uint *second)

{
  uint *second_local;
  uint *first_local;
  
  *first = *first + 1;
  *second = *second - 1;
  return;
}
void modify_int_refs_new_syntax(int *first,int *second)

{
  int *second_local;
  int *first_local;
  
  *first = *first + 1;
  *second = *second + -1;
  return;
}
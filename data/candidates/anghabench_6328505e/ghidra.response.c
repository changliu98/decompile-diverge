int is_uletter(char c)

{
  bool local_a;
  char c_local;
  
  local_a = '@' < c && c < '[';
  return (int)local_a;
}
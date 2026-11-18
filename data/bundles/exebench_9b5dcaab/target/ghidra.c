void modify_calculated_address_new_syntax(int *foo)

{
  int *foo_local;
  
  foo[1] = foo[1] + 5;
  foo[2] = foo[2] + -5;
  return;
}
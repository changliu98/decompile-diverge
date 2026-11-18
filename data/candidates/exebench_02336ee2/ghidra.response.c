char foo(char *a)

{
  char *a_local;
  
  a[9] = 'a';
  return a[9];
}
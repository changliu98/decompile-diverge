int foo(int *a,int *b,int c)

{
  int c_local;
  int *b_local;
  int *a_local;
  
  *a = *a << 1;
  *b = *b / 2;
  return *a + *b;
}
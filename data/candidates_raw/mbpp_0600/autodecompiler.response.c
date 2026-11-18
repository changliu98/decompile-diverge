int foo(int n)
{
 char b;

 if((n ^ 1) == (n + 1))
  b = 1;
 else
  b = 0;

 return b & 1;
}
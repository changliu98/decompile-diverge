void f(int *a, int b)
{
  if ( *a > b )
    h( a, *a );
  else
    *a -= b;
}
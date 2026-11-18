void __cdecl func3(int i, int *j)
{
  int v2; // ecx

  if ( i <= 0 )
    v2 = *j - 1;
  else
    v2 = *j + 1;
  *j = v2;
}
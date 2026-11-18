void __cdecl chartobit(int val, char *v)
{
  char v2; // al
  char v3; // al
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 7; i > 0; --i )
  {
    v2 = 48;
    if ( val % 2 == 1 )
      v2 = 49;
    v[i] = v2;
    val /= 2;
  }
  v3 = 48;
  if ( val % 2 == 1 )
    v3 = 49;
  *v = v3;
}
void __cdecl chartobit(int val, char *v)
{
  int i;

  // Process bits 7 down to 1
  for ( i = 7; i > 0; --i )
  {
    v[i] = (val % 2 == 1) ? '1' : '0';
    val /= 2;
  }
  
  // Process the final bit (bit 0) and store it at the beginning of the array
  *v = (val % 2 == 1) ? '1' : '0';
}
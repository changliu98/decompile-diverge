void __cdecl jis_shift(int *p1, int *p2)
{
  unsigned __int8 c1 = (unsigned __int8)*p1;
  unsigned __int8 c2 = (unsigned __int8)*p2;
  
  int rowOffset = (c1 < 0x5F) ? 112 : 176;
  int colOffset;
  
  if (c1 % 2) 
  {
    // Odd rows
    colOffset = (c2 > 0x5F) ? 32 : 31;
  } 
  else 
  {
    // Even rows
    colOffset = 126;
  }
  
  *p1 = rowOffset + ((c1 + 1) >> 1);
  *p2 += colOffset;
}
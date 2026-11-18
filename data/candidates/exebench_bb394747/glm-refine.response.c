int __cdecl get_hashmask(int *size)
{
  int tsize; 

  // Round up 'tsize' to the next power of 2 that is greater than or equal to *size
  for ( tsize = 1; tsize < *size; tsize <<= 1 )
    ;

  // Update the original size pointer with the new power of 2
  *size = tsize;

  // Return the hash mask (which is the power of 2 minus 1)
  return tsize - 1;
}
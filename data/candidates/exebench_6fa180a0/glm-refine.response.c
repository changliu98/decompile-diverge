void __cdecl sortVrtx(int *vrt)
{
  int swapped;
  int tmp;
  int i;

  do
  {
    swapped = 1; // Initialize to 1 (true). If no swaps occur, it stays 1 and the loop breaks.
    for ( i = 1; i < 3; ++i )
    {
      if ( vrt[i - 1] > vrt[i] )
      {
        // Swap the elements
        tmp = vrt[i];
        vrt[i] = vrt[i - 1];
        vrt[i - 1] = tmp;
        swapped = 0; // A swap occurred, so we need another pass
      }
    }
  }
  while ( !swapped ); // Continue until a pass completes with no swaps
}
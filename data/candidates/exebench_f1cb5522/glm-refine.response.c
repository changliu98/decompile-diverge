void __cdecl argorder(int ix1, int ix2, int *ox1, int *ox2)
{
  int lower, upper;

  if (ix1 > ix2) {
    lower = ix2;
    upper = ix1;
  } else {
    lower = ix1;
    upper = ix2;
  }

  *ox1 = lower;
  *ox2 = upper;
}
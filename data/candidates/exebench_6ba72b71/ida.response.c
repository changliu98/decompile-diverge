void __cdecl measure(long *inches, int *inch, int *feet, int *yard, int *mile)
{
  *inches = 63360LL;
  *inch = *inches;
  *feet = (int)((double)(int)*inches * 0.0833333);
  *yard = (int)((double)(int)*inches * 0.0277778);
  *mile = (int)((double)(int)*inches * 0.0000158);
}
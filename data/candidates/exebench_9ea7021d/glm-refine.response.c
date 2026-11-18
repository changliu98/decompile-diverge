void __cdecl AdjustSpan(int *start, int *len, int max)
{
  int s = *start;
  int l = *len;

  // 1. Clamp the lower bound: if the start is negative, shift it to 0
  //    and subtract the overflow from the length.
  if (s < 0)
  {
    l += s;  // Equivalent to: l = l - |s|
    s = 0;
  }

  // 2. Clamp the upper bound: if the span exceeds the maximum allowed index,
  //    truncate the length to fit exactly within the boundary.
  if (l + s > max)
  {
    l = max - s;
  }

  // Write back the adjusted values
  *start = s;
  *len = l;
}
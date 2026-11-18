int __cdecl jrand_(int *n, int *ix, int *iy, int *iz)
{
  // Wichmann–Hill pseudo-random number generator state updates
  *ix = 171 * *ix % 30269;
  *iy = 172 * *iy % 30307;
  *iz = 170 * *iz % 30323;

  // Sum the normalized components
  jrand__x = (double)*ix / 30269.0 + (double)*iy / 30307.0 + (double)*iz / 30323.0;

  // Extract the fractional part of jrand__x.
  // Casting a double to int truncates towards zero, which is exactly 
  // what the original explicit cast logic was doing.
  jrand__u = jrand__x - (int)jrand__x;

  // Scale the fractional part by 'n' and shift to the range [1, n]
  return (int)((double)*n * jrand__u + 1.0);
}
// Swaps the values pointed to by p0 and p1 if *p0 is greater than *p1.
// This is a standard conditional swap operation, often used in sorting networks or algorithms.
void __cdecl Sort(int *p0, int *p1)
{
  if (*p0 > *p1)
  {
    int temp = *p0;
    *p0 = *p1;
    *p1 = temp;
  }
}
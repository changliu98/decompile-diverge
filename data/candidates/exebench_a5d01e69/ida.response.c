void __cdecl Sort(int *p0, int *p1)
{
  int temp; // [rsp+0h] [rbp-14h]

  if ( *p0 > *p1 )
  {
    temp = *p0;
    *p0 = *p1;
    *p1 = temp;
  }
}
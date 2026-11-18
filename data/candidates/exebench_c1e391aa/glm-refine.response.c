int __cdecl set_bit(int *ptr, int n)
{
  // Cast to unsigned int to prevent undefined behavior on signed left-shift 
  // and to accurately represent the underlying machine's bitwise shift logic.
  *ptr |= (int)(1U << n);
  
  return *ptr;
}
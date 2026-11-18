int
uasm_in_compat_space_p (volatile int* x)
{
  return (*x == (int) x) & ((int) (char) 1);
}
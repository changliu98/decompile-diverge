void __cdecl nm_writel(unsigned int value, unsigned int *ptr)
{
  // Dereference the pointer and write the value to the memory location.
  *ptr = value;
}
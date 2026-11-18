void __cdecl change_params(int x, int y, int *ptr, int *ptr_y)
{
  // The function unconditionally sets the dereferenced integer at 'ptr_y' to 10.
  // WARNING: If 'ptr_y' is NULL, this will cause an access violation (segfault).
  *ptr_y = 10;
}
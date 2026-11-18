// Swaps the values of two integers pointed to by px and py.
void __cdecl std::swap<int>(int *px, int *py)
{
  int temp = *px;
  *px = *py;
  *py = temp;
}
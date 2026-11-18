void __cdecl bitmap_free(unsigned int *array, int index)
{
  array[index / 32] &= ~(0x80000000 >> (index % 32));
}
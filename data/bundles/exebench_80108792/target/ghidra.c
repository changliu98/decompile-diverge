void bitmap_free(uint *array,int index)

{
  int index_local;
  uint *array_local;
  
  array[index / 0x20] =
       (0x80000000U >> ((byte)((long)index % 0x20) & 0x1f) ^ 0xffffffff) & array[index / 0x20];
  return;
}
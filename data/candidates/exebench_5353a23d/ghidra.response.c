void _vector_swap(size_t *first,size_t *second)

{
  size_t sVar1;
  size_t temp;
  size_t *second_local;
  size_t *first_local;
  
  sVar1 = *first;
  *first = *second;
  *second = sVar1;
  return;
}
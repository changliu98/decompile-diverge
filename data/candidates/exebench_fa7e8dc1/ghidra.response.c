void fancySwap(int *first,int *second)

{
  int *second_local;
  int *first_local;
  
  *first = *first ^ *second;
  *second = *first ^ *second;
  *first = *first ^ *second;
  return;
}
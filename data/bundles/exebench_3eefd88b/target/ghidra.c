int q_GetMemoryInformation(int *total,int *free)

{
  int *free_local;
  int *total_local;
  
  *total = 0xa00000;
  *free = 0x500000;
  return 0;
}
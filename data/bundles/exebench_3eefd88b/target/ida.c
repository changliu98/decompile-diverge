int __cdecl q_GetMemoryInformation(int *total, int *free)
{
  *total = 10485760;
  *free = 5242880;
  return 0;
}
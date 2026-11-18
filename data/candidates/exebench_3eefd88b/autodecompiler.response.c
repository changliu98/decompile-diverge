int q_GetMemoryInformation(unsigned int *total, unsigned int *free)
{
 *total = 1024*1024*10;
 *free = 1024*1024*5;
 return 0;
}
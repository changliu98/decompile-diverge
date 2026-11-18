int __cdecl q_GetMemoryInformation(size_t *total, size_t *free)
{
  *total = 10 << 20; // 10 MB (10 * 1024 * 1024 = 10485760)
  *free = 5 << 20;   // 5 MB  (5 * 1024 * 1024 = 5242880)
  return 0;
}
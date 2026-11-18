int q_GetMemoryInformation(unsigned int *pui32Minimum,
                           unsigned int *pui32Recommended) {
  *pui32Minimum = 10 * 1024 * 1024;
  *pui32Recommended = 5 * 1024 * 1024;
  return 0;
}
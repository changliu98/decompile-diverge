int __cdecl func0(char **listval, int size)
{
  int current_val;
  int min_val = 0x7FFFFFFF; // INT_MAX

  for (int i = 0; i < size; ++i)
  {
    // unk_2004 is the format string "%d" in the .rodata section
    if (sscanf(listval[i], "%d", &current_val) == 1)
    {
      if (current_val < min_val)
        min_val = current_val;
    }
  }
  
  return min_val;
}
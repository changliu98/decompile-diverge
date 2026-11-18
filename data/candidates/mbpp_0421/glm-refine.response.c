char *__cdecl func0(char **str_array, int size)
{
  char delim[2]; // [rsp+12h] [rbp-Eh] BYREF
  int i; // [rsp+Ch] [rbp-14h]

  // Initialize the global result buffer
  strcpy(func0_res, "");
  
  // Initialize delimiter
  strcpy(delim, "-");
  
  for (i = 0; i < size; ++i)
  {
    // Append the current string from the array
    strcat(func0_res, str_array[i]);
    
    // If this is not the last element, append the delimiter
    if (i < size - 1)
      strcat(func0_res, delim);
  }
  
  return func0_res;
}
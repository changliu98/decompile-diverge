void __cdecl right_shift_str(char *str, int shift_count)
{
  char temp; 
  int length;
  int i, j;

  // Calculate the length of the string
  length = strlen(str);

  // Perform the right shift 'shift_count' times
  for (j = 0; j < shift_count; ++j)
  {
    // Store the last character
    temp = str[length - 1];
    
    // Shift all characters to the right by one position
    for (i = length - 1; i > 0; --i)
      str[i] = str[i - 1];
      
    // Place the stored last character at the beginning
    str[0] = temp;
  }
}
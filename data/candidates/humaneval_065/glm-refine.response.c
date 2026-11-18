char *func0(int x, int shift)
{
  char rotated_str[50]; 
  char temp; 
  int i; 
  int len; 

  // Convert the integer to a string
  sprintf(num_str, "%d", x);
  len = strlen(num_str);

  if (len >= shift)
  {
    // Rotate the string to the right by 'shift' positions
    strcpy(rotated_str, &num_str[len - shift]);
    rotated_str[shift] = 0;
    strncat(rotated_str, num_str, len - shift);
    strcpy(num_str, rotated_str);
  }
  else
  {
    // Reverse the string
    for (i = 0; i < len / 2; ++i)
    {
      temp = num_str[i];
      num_str[i] = num_str[len - 1 - i];
      num_str[len - 1 - i] = temp;
    }
    
    /* 
    Alternatively, if strrev is available in your environment:
    strrev(num_str); 
    */
  }
  
  return num_str;
}
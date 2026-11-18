bool __cdecl func0(const char *a, const char *b)
{
  int len_b = strlen(b);
  
  // Allocate a buffer to hold the rotated versions of 'b'.
  // The maximum length of a rotation is len_b, plus 1 for the null terminator.
  char *rotated_b = (char *)malloc(len_b + 1);
  if (!rotated_b) return false; // Safety check for malloc failure

  // Generate all possible rotations of 'b'
  for (int i = 0; i < len_b; ++i)
  {
    // Rotation at index 'i': 
    // Suffix of 'b' starting at 'i' (length: len_b - i)
    strncpy(rotated_b, &b[i], len_b - i);
    
    // Prefix of 'b' up to 'i' (length: i)
    strncpy(&rotated_b[len_b - i], b, i);
    
    rotated_b[len_b] = '\0';

    // If this rotation is found within 'a', we are done
    if (strstr(a, rotated_b) != NULL)
    {
      free(rotated_b);
      return true;
    }
  }

  free(rotated_b);
  return false;
}
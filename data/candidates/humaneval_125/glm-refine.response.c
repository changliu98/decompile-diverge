char **__cdecl func0(const char *txt, int *returnSize)
{
  char current[101] = {0};
  char **out = NULL;
  int len = strlen(txt);
  int count = 0;
  int j = 0;

  // If the string contains a space (32) or a comma (44), split it into tokens
  if (strchr(txt, ' ') || strchr(txt, ','))
  {
    out = (char **)malloc(sizeof(char *) * (len + 1));
    
    for (int i = 0; i <= len; ++i)
    {
      if (txt[i] == ' ' || txt[i] == ',' || txt[i] == '\0')
      {
        if (j > 0)
        {
          current[j] = '\0';
          out[count++] = strdup(current);
          j = 0;
        }
      }
      else
      {
        current[j++] = txt[i];
      }
    }
  }
  else
  {
    // Otherwise, count lowercase vowels (a, e, i, o, u)
    // (islower() checks if the character is lowercase. 
    // (c - 'a') % 2 == 1 identifies letters with an odd offset from 'a', 
    // which corresponds to a, e, i, o, u)
    int num = 0;
    for (int i = 0; i < len; ++i)
    {
      if (islower(txt[i]) && (txt[i] - 'a') % 2 == 1)
        ++num;
    }
    
    out = (char **)malloc(sizeof(char *));
    out[0] = (char *)malloc(12); // 0xC = 12 bytes
    sprintf(out[0], "%d", num);
    count = 1;
  }

  *returnSize = count;
  return out;
}
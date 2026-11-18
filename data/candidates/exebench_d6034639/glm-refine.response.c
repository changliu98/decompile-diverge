int __cdecl fatfs_get_sfn_display_name(char *out, char *in)
{
  int len = 0;
  char a;

  while (*in && len <= 11)
  {
    a = *in++;
    if (a != ' ')
    {
      if (a >= 'A' && a <= 'Z')
        a += 32; // Convert to lowercase
      
      *out++ = a;
      ++len;
    }
  }
  
  *out = '\0';
  return 1;
}
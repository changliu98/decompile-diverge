static int
func0 (char **words, int nwords)
{
  int i, j;
  int has_lower, has_upper, ret;

  if (nwords == 0)
    {
      ret = 0;
      goto out;
    }

  has_lower = 0;
  has_upper = 0;

  for (i = 0; ; i++)
    {
      char *word;

      if (i >= nwords)
 break;

      word = words[i];

      for (j = 0; ; j++)
 {
   if (word[j] == '\0')
     break;

   if (!((*__ctype_b_loc ())[(unsigned int) ((unsigned char) word[j])] & (int) 0x0400))
     {
       ret = 0;
       goto out;
     }

   if ((*__ctype_b_loc ())[(unsigned int) ((unsigned char) word[j])] & (int) 0x0100)
     has_upper = 1;

   if ((*__ctype_b_loc ())[(unsigned int) ((unsigned char) word[j])] & (int) 0x0200)
     has_lower = 1;

   if (has_upper + has_lower == 2)
     {
       ret = 0;
       goto out;
     }
 }
    }

  ret = 1;

 out:

  return ret;
}
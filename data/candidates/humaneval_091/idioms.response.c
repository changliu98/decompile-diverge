int func0(char *text)
{
  int is_in_sentence = 1;
  int is_in_word = 0;
  int count = 0;
  int i = 0;
  for (i = 0; text[i]; i++)
  {
    if (is_in_word && ((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISspace))
    {
      is_in_word = 0;
      count++;
    }
    if (text[i] == 'I' && is_in_sentence)
    {
      is_in_word = 1;
    }
    else if (!((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISspace))
    {
      is_in_word = 0;
    }
    if (!((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISspace))
    {
      is_in_sentence = 0;
    }
    if (text[i] == '.' || text[i] == '?' || text[i] == '!')
    {
      is_in_sentence = 1;
    }
  }
  return count;
}
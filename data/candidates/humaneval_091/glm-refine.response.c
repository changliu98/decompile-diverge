int __cdecl func0(const char *S)
{
  int i;
  int count = 0;
  int is_standalone_I = 0;
  int is_word_start = 1;

  for (i = 0; S[i]; ++i)
  {
    // If the current character is a space and we previously found a standalone 'I'
    if (isspace((unsigned char)S[i]) && is_standalone_I)
    {
      is_standalone_I = 0;
      ++count;
    }

    if (S[i] == 'I' && is_word_start)
    {
      is_standalone_I = 1;
    }
    else if (!isspace((unsigned char)S[i]))
    {
      is_standalone_I = 0;
    }

    // A non-space character means we are no longer at the start of a word
    if (!isspace((unsigned char)S[i]))
      is_word_start = 0;

    // Sentence-ending punctuation marks the start of the next word
    if (S[i] == '.' || S[i] == '?' || S[i] == '!')
      is_word_start = 1;
  }

  return count;
}
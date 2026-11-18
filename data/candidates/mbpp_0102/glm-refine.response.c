char *__cdecl func0(const char *word, char *output)
{
  int capitalize_next = 1;
  int out_idx = 0;
  int in_idx = 0;

  while (word[in_idx])
  {
    if (word[in_idx] == '_')
    {
      capitalize_next = 1;
    }
    else if (capitalize_next)
    {
      output[out_idx++] = toupper(word[in_idx]);
      capitalize_next = 0;
    }
    else
    {
      output[out_idx++] = word[in_idx];
    }
    ++in_idx;
  }
  output[out_idx] = '\0';
  
  return output;
}
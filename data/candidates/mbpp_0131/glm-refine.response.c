char *__cdecl func0(char *str)
{
  char vowels[100];          // buffer holding vowels in original order
  int  vowel_count;          // number of vowels collected
  int  vowel_idx;            // index used to read vowels in reverse
  int  out_idx;              // write index into func0_result_string
  int  i;                    // scan index over the input string
  char c;                    // current character being inspected

  memset(vowels, 0, sizeof(vowels));

  // ---- Pass 1: collect vowels in their original order ----
  vowel_count = 0;
  for (i = 0; str[i]; ++i)
  {
    c = str[i];
    if (strchr("aeiouAEIOU", c))
      vowels[vowel_count++] = c;
  }
  vowels[vowel_count] = '\0';

  // ---- Pass 2: rebuild the string, taking vowels in reverse order ----
  vowel_idx = strlen(vowels) - 1;
  out_idx   = 0;
  for (i = 0; str[i]; ++i)
  {
    if (strchr("aeiouAEIOU", str[i]))
      func0_result_string[out_idx++] = vowels[vowel_idx--];
    else
      func0_result_string[out_idx++] = str[i];
  }
  func0_result_string[out_idx] = '\0';

  return func0_result_string;
}
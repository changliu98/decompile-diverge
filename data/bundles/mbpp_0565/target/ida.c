char *__cdecl func0(char *word, char *result)
{
  int i; // [rsp+8h] [rbp-18h]
  int length; // [rsp+Ch] [rbp-14h]

  length = strlen(word);
  for ( i = 0; i < length; ++i )
    result[i] = word[i];
  result[length] = 0;
  return result;
}
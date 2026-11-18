int __cdecl func0(char *s)
{
  const char *word; // [rsp+8h] [rbp-18h]

  word = strtok(s, " ");
  return word && (strlen(word) & 1) == 0;
}
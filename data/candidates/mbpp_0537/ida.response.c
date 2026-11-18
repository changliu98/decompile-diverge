char *__cdecl func0(char *str1)
{
  int v1; // eax
  int i; // [rsp+Ch] [rbp-344h]
  char *word; // [rsp+10h] [rbp-340h]
  int word_count; // [rsp+1Ch] [rbp-334h]
  char *words[100]; // [rsp+20h] [rbp-330h]
  char *str1a; // [rsp+340h] [rbp-10h]

  str1a = str1;
  word_count = 0;
  for ( word = strtok(str1, " "); word; word = strtok(0LL, " ") )
  {
    for ( i = 0; i < word_count; ++i )
    {
      if ( !strcmp(words[i], word) )
        return word;
    }
    v1 = word_count++;
    words[v1] = word;
  }
  return "None";
}
char *__cdecl func0(char *s)
{
  int v1; // eax
  __int64 i; // [rsp+4h] [rbp-6Ch]
  char *token; // [rsp+8h] [rbp-68h]
  char *words[10]; // [rsp+10h] [rbp-60h]
  int word_count; // [rsp+64h] [rbp-Ch]
  char *sa; // [rsp+68h] [rbp-8h]

  sa = s;
  word_count = 0;
  for ( token = strtok(s, " "); token; token = strtok(0LL, " ") )
  {
    v1 = word_count++;
    words[v1] = token;
  }
  func0_result = 0;
  for ( i = (unsigned int)(word_count - 1); (int)i >= 0; LODWORD(i) = i - 1 )
  {
    strcat(&func0_result, words[(int)i]);
    if ( (int)i > 0 )
      strcat(&func0_result, " ");
  }
  return &func0_result;
}
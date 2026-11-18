char *__cdecl func0(const char *test_str, int K)
{
  size_t v2; // rax
  int v3; // eax
  size_t len; // [rsp+8h] [rbp-418h]
  const char *token; // [rsp+10h] [rbp-410h]
  char *res; // [rsp+18h] [rbp-408h]
  char temp_copy[1000]; // [rsp+20h] [rbp-400h] BYREF
  int Ka; // [rsp+414h] [rbp-Ch]
  const char *test_stra; // [rsp+418h] [rbp-8h]

  test_stra = test_str;
  Ka = K;
  strncpy(temp_copy, test_str, 0x3E8uLL);
  temp_copy[999] = 0;
  v2 = strlen(test_stra);
  res = (char *)malloc(v2 + 1);
  if ( !res )
  {
    perror("malloc failed");
    exit(1);
  }
  *res = 0;
  for ( token = strtok(temp_copy, " "); token; token = strtok(0LL, " ") )
  {
    v3 = strlen(token);
    if ( v3 != Ka )
    {
      strcat(res, token);
      strcat(res, " ");
    }
  }
  len = strlen(res);
  if ( len && res[len - 1] == 32 )
    res[len - 1] = 0;
  return res;
}
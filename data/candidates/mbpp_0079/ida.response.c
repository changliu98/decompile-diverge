int __cdecl func0(char *s)
{
  const char *token; // [rsp+8h] [rbp-18h]

  token = strtok(s, " ");
  return token && (strlen(token) & 1) != 0;
}
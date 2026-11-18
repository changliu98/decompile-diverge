int __cdecl func0(char *s)
{
  const char *token = strtok(s, " ");
  return token != NULL && (strlen(token) & 1) != 0;
}
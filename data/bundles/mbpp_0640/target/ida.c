char *__cdecl func0(char *item)
{
  size_t v1; // rax
  size_t v2; // rax
  char *dest; // [rsp+0h] [rbp-80h]
  char *src; // [rsp+8h] [rbp-78h]
  int end; // [rsp+10h] [rbp-70h]
  char *result; // [rsp+18h] [rbp-68h]
  regmatch_t matches[2]; // [rsp+20h] [rbp-60h] BYREF
  regex_t regex; // [rsp+38h] [rbp-48h] BYREF
  char *itema; // [rsp+78h] [rbp-8h]

  itema = item;
  v1 = strlen(item);
  result = (char *)malloc(v1 + 1);
  strcpy(result, item);
  if ( !regcomp(&regex, " ?\\([^)]+\\)", 1) )
  {
    while ( !regexec(&regex, result, 2uLL, matches, 0) )
    {
      end = matches[0].rm_eo;
      dest = &result[matches[0].rm_so];
      src = &result[matches[0].rm_eo];
      v2 = strlen(result);
      memmove(dest, src, v2 - end + 1);
    }
    regfree(&regex);
  }
  return result;
}
char *__cdecl func0(const char *ip_0)
{
  size_t v1; // rax
  size_t start; // [rsp+8h] [rbp-78h]
  size_t len; // [rsp+10h] [rbp-70h]
  char *current_location; // [rsp+18h] [rbp-68h]
  char *result; // [rsp+20h] [rbp-60h]
  char pattern[5]; // [rsp+2Bh] [rbp-55h] BYREF
  regmatch_t matches[1]; // [rsp+30h] [rbp-50h] BYREF
  regex_t regex; // [rsp+38h] [rbp-48h] BYREF
  const char *ip_0a; // [rsp+78h] [rbp-8h]

  ip_0a = ip_0;
  strcpy(pattern, "\\.0+");
  v1 = strlen(ip_0);
  result = (char *)malloc(v1 + 1);
  regcomp(&regex, pattern, 1);
  strcpy(result, ip_0a);
  for ( current_location = result; !regexec(&regex, current_location, 1uLL, matches, 0); current_location += start + 1 )
  {
    len = strlen(current_location);
    start = matches[0].rm_so;
    memmove(&current_location[matches[0].rm_so + 1], &current_location[matches[0].rm_eo], len - matches[0].rm_eo + 1);
  }
  regfree(&regex);
  return result;
}
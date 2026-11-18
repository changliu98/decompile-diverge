// bad sp value at call has been detected, the output may be wrong!
char **__cdecl func0(const char *text, int *count)
{
  size_t v2; // rax
  int v3; // eax
  __int64 v5; // [rsp+0h] [rbp-B0h] BYREF
  char *v6; // [rsp+8h] [rbp-A8h]
  char *word; // [rsp+10h] [rbp-A0h]
  int end; // [rsp+18h] [rbp-98h]
  int start; // [rsp+1Ch] [rbp-94h]
  char *p; // [rsp+20h] [rbp-90h]
  unsigned __int64 __vla_expr0; // [rsp+28h] [rbp-88h]
  __int64 *v12; // [rsp+30h] [rbp-80h]
  int word_count; // [rsp+3Ch] [rbp-74h]
  char pattern[16]; // [rsp+40h] [rbp-70h] BYREF
  regmatch_t matches[1]; // [rsp+58h] [rbp-58h] BYREF
  regex_t regex; // [rsp+60h] [rbp-50h] BYREF
  int *counta; // [rsp+A0h] [rbp-10h]

  counta = count;
  strcpy(pattern, "\\b[a-zA-Z]{5}\\b");
  word_count = 0;
  v2 = strlen(text);
  v12 = &v5;
  v6 = (char *)&v5 - ((v2 + 16) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = v2 + 1;
  strcpy(v6, text);
  regcomp(&regex, pattern, 1);
  for ( p = v6; !regexec(&regex, p, 1uLL, matches, 0); p += end )
  {
    start = matches[0].rm_so;
    end = matches[0].rm_eo;
    word = (char *)malloc(matches[0].rm_eo - matches[0].rm_so + 1);
    strncpy(word, &p[start], end - start);
    word[end - start] = 0;
    v3 = word_count++;
    func0_words[v3] = word;
  }
  regfree(&regex);
  *counta = word_count;
  return (char **)func0_words;
}
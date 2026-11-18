// Splits a string by spaces into a NULL-terminated array of token strings.
// Returns NULL on allocation failure.
char **__cdecl split_string_by_spaces(const char *string)
{
  char *token_dup;        // rax
  int slot;               // ecx
  const char *token;      // [rsp+0h]  [rbp-40h]
  int index;              // [rsp+Ch]  [rbp-34h]
  char *copy;             // [rsp+10h] [rbp-30h]
  char **tokens;          // [rsp+18h] [rbp-28h]
  const char *p;          // [rsp+20h] [rbp-20h]
  int token_count;        // [rsp+2Ch] [rbp-14h]

  // Count tokens by counting spaces (tokens = spaces + 1)
  token_count = 1;
  for ( p = string; *p; ++p )
  {
    if ( *p == ' ' )
      ++token_count;
  }

  // Allocate array of pointers, +1 for NULL terminator
  tokens = (char **)malloc(8LL * (token_count + 1));
  if ( !tokens )
    return NULL;

  // Make a mutable copy for strtok to chew on
  copy = strdup(string);
  if ( copy )
  {
    index = 0;
    for ( token = strtok(copy, " "); token; token = strtok(NULL, " ") )
    {
      token_dup = strdup(token);
      slot = index++;
      tokens[slot] = token_dup;
    }
    tokens[index] = NULL;
    free(copy);
    return tokens;
  }
  else
  {
    free(tokens);
    return NULL;
  }
}
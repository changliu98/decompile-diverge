char **split3(char *str, int *num) {
 char **tokens = NULL;
 *num = 0;

 int len = strlen(str);
 int i = 0;
 while (1) {
  if (i >= len)
   break;

  if (!((*(*___ctype_b_loc ()) + (unsigned int) (unsigned char) (str[i])) & (int) 0x200)) {
   ++i;
   continue;
  }

  int j = i + 1;
  while (1) {
   if (j >= len || !((*(*___ctype_b_loc ()) + (unsigned int) (unsigned char) (str[j])) & (int) 0x200))
    break;
   ++j;
  }

  int toklen = j - i;
  char *tok = malloc(toklen + 1);
  strncpy(tok, str + i, toklen);
  tok[toklen] = '\0';

  tokens = realloc(tokens, (*num + 1) * sizeof(char *));
  tokens[*num] = tok;
  ++*num;

  i = j;
 }

 return tokens;
}
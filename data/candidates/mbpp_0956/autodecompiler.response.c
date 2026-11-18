char **func0(char *str, int *num)
{
 char **tokens;
 int len = strlen(str);
 int i, j, k, l;

 tokens = (char **)malloc(sizeof(char *) * len);

 *num = 0;
 for(i = 0, j = 1; ; j++) {
  if(j > len) break;

  if(j == len || (((___ctype_b_loc ()[(int) ((str[j]))] & (unsigned short int) 0x0100)) && !((___ctype_b_loc ()[(int) ((str[j-1]))] & (unsigned short int) 0x0100)))) {
   int size = j - i;
   tokens[*num] = (char *)malloc(size + 1);
   strncpy(tokens[*num], str + i, size);
   tokens[*num][size] = '\0';
   (*num)++;
   i = j;
  }
 }

 return tokens;
}
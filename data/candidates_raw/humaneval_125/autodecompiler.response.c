char ** get_word_list(char * line, int * list_size)
{
 char word[100 + 1];
 int word_len = 0, word_num = 0, len = strlen(line), i, j;
 char ** list = NULL;

 memset(word, 0, sizeof(word));

 if (strchr(line, ' ') || strchr(line, ',')) {
  list = (char **)malloc((len + 1) * sizeof(char *));
  for (i = 0, j = 0; i <= len; ++i) {
   if (line[i] == ' ' || line[i] == ',' || line[i] == '\0') {
    if (word_len > 0) {
     word[word_len] = '\0';
     list[j++] = strdup(word);
     word_len = 0;
    }
   } else {
    word[word_len++] = line[i];
   }
  }
 } else {
  for (i = 0; i < len; ++i) {
   if (((*___ctype_b_loc ())[(int) ((line[i]))] & (unsigned short int) 512) && ((line[i] - 'a') % 2 == 1))
    word_num++;
  }

  list = (char **)malloc(sizeof(char *));
  list[0] = (char *)malloc(12 * sizeof(char));
  sprintf(list[0], "%d", word_num);

  j = 1;
 }

 *list_size = j;

 return list;
}
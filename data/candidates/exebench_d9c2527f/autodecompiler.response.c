char *get_word(char *word, int *len)
{
 int pos = 0;

 if (word) {
  while (*word == '-')
   word++;

  while ((pos < 64) && ((*word >= 'a') && (*word <= 'z'))) {
   char ok = 0;

   if (((*word >= '0') && (*word <= '9')) ||
       ((*word >= 'a') && (*word <= 'z')) ||
       (*word == '-') || (*word == '_'))
    ok = 1;

   if (!ok)
    break;
   else
    word++;
   pos++;
  }
 }

 *len = pos;
 return word;
}
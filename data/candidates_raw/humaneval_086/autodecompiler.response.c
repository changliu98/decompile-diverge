char* arrange(char *s)
{
 int len = strlen(s);
 char *word = (char *)malloc((len + 2) * sizeof(char));
 int i, j, k, m, n, p, q;
 int wlen = 0, wstart = 0, wend = 0, flag = 0;
 int index = 0;
 char temp[30];
 for (i = 0; ; i++) {
  if (i > len)
   break;
  if (s[i] == ' ' || s[i] == '\0') {
   flag = 1;
   wend = i - 1;
  } else {
   flag = 0;
   temp[wlen++] = s[i];
  }
  if (flag) {
   for (m = 0; m < wlen - 1; m++)
    for (n = m + 1; n < wlen; n++) {
     if (temp[m] > temp[n]) {
      char swap = temp[m];
      temp[m] = temp[n];
      temp[n] = swap;
     }
    }
   if (index > 0)
    word[index++] = ' ';
   for (p = 0; p < wlen; p++)
    word[index++] = temp[p];
   wlen = 0;
  }
 }
 word[index] = '\0';
 return word;
}
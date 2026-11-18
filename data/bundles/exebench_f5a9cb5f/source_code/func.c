
void reverse(char s[])
{
  int c, i, j;
  for(j = 0; s[j] != 0; j++)
   ;

  for(i=0, j = j - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

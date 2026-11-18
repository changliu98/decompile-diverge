char *func0(char *s)
{
  int i,j;
  size_t len;
  char *r;

  len = strlen(s);
  size_t new_len = 0;
  r = (char *)malloc(len*2);

  j=0;
  for(i=0;i<len;i++) {
    if(i>0 && (((*___ctype_b_loc ())[(int) ((s[i]))] & (unsigned short int) 256) != 0) && (((*___ctype_b_loc ())[(int) ((s[i-1]))] & (unsigned short int) 512) != 0 || ((*___ctype_b_loc ())[(int) ((s[i-1]))] & (unsigned short int) 2048) != 0)) {
      r[j++] = '_';
      r[j++] = tolower(s[i]);
    }
    else if(i>0 && (((*___ctype_b_loc ())[(int) ((s[i]))] & (unsigned short int) 256) != 0) && (((*___ctype_b_loc ())[(int) ((s[i-1]))] & (unsigned short int) 256) != 0) && (((*___ctype_b_loc ())[(int) ((s[i+1]))] & (unsigned short int) 512) != 0)) {
      r[j++] = '_';
      r[j++] = tolower(s[i]);
    }
    else
      r[j++] = tolower(s[i]);
  }
  r[j] = '\0';

  return r;
}
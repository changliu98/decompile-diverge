void set_nb(char *s,char c,int *nb)

{
  int i2;
  int i1;
  int *nb_local;
  char c_local;
  char *s_local;
  
  i1 = 0;
  i2 = 0;
  while (s[i1] != '\0') {
    if ((i1 == i2) && (s[i1] == c)) {
      i1 = i1 + 1;
      i2 = i2 + 1;
    }
    else if ((s[i2] == c) || (s[i2] == '\0')) {
      *nb = *nb + 1;
      i1 = i2;
    }
    else {
      i2 = i2 + 1;
    }
  }
  return;
}
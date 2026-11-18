void reverse(char *s) {
  int len;
  int i = 0;
  char temp;

  while(1) {
    if ((int)*(s+i) == 0) {
      len = i;
      break;
    }
    i++;
  }

  i = 0;
  while(i < len/2) {
    temp = *(s+i);
    *(s+i) = *(s+len-(i+1));
    *(s+len-(i+1)) = temp;
    i++;
  }
}
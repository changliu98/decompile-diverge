void reverse(char* s){

  int length = 0;
  char* p = s;

  while(*p != 0){

    length++;
    p++;
  }

  int i = 0;
  char c;

  while(i<=length/2 -1){

    c = *(s+i);
    *(s+i) = *(s + length - 1 - i);
    *(s + length - 1 - i) = c;
    i++;
  }
}
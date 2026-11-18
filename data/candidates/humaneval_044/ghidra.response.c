void func0(int x,int base,char *out)

{
  int j;
  char temp [33];
  int index;
  char *out_local;
  int base_local;
  int x_local;
  
  index = 0;
  for (x_local = x; 0 < x_local; x_local = x_local / base) {
    temp[index] = (char)(x_local % base) + '0';
    index = index + 1;
  }
  j = 0;
  while (0 < index) {
    index = index + -1;
    out[j] = temp[index];
    j = j + 1;
  }
  out[j] = '\0';
  return;
}
int func0(char *strr)

{
  int i;
  int summ;
  char *strr_local;
  int local_c;
  
  summ = 0;
  for (i = 0; strr[i] != '\0'; i = i + 1) {
    summ = strr[i] + -0x60 + summ;
  }
  if (summ % 0x1a == 0) {
    local_c = 0x7a;
  }
  else {
    local_c = summ % 0x1a + 0x60;
  }
  return local_c;
}
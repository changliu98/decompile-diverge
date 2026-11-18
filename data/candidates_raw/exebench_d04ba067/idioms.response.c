int itoa(int num, char *strb){
  int numc = num;
  char *strba = strb;
  int i = 0;
  int j = 0;
  char str[16];
  do{
    str[i++] = (char)(numc % 10 + '0');
    numc /= 10;
  }while(numc);
  do{
    strba[j] = str[i - j - 1];
    j++;
  }while(j < i);
  return j;
}
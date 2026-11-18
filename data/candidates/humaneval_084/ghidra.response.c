char * func0(int N)

{
  char cVar1;
  char *pcVar2;
  char temp;
  int i_1;
  int index;
  char *bi;
  int i;
  int sum;
  char str [6];
  int N_local;
  
  sprintf(str,"%d",(ulong)(uint)N);
  sum = 0;
  for (i = 0; str[i] != '\0'; i = i + 1) {
    sum = str[i] + -0x30 + sum;
  }
  pcVar2 = malloc(0x21);
  index = 0;
  if (sum == 0) {
    index = 1;
    *pcVar2 = '0';
  }
  else {
    for (; 0 < sum; sum = sum / 2) {
      pcVar2[index] = (char)(sum % 2) + '0';
      index = index + 1;
    }
  }
  pcVar2[index] = '\0';
  for (i_1 = 0; i_1 < index / 2; i_1 = i_1 + 1) {
    cVar1 = pcVar2[i_1];
    pcVar2[i_1] = pcVar2[(index - i_1) + -1];
    pcVar2[(index - i_1) + -1] = cVar1;
  }
  return pcVar2;
}
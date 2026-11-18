char * func0(char *str1)

{
  char cVar1;
  char *pcVar2;
  size_t sVar3;
  char char1_1;
  int k;
  char char1;
  char vowels [100];
  int j;
  int i;
  char *str1_local;
  
  j = 0;
  memset(vowels,0,100);
  for (i = 0; str1[i] != '\0'; i = i + 1) {
    cVar1 = str1[i];
    pcVar2 = strchr("aeiouAEIOU",(int)cVar1);
    if (pcVar2 != (char *)0x0) {
      vowels[j] = cVar1;
      j = j + 1;
    }
  }
  vowels[j] = '\0';
  j = 0;
  sVar3 = strlen(vowels);
  k = (int)sVar3 + -1;
  for (i = 0; str1[i] != '\0'; i = i + 1) {
    pcVar2 = strchr("aeiouAEIOU",(int)str1[i]);
    if (pcVar2 == (char *)0x0) {
      func0::result_string[j] = str1[i];
    }
    else {
      func0::result_string[j] = vowels[k];
      k = k + -1;
    }
    j = j + 1;
  }
  func0::result_string[j] = '\0';
  return func0::result_string;
}
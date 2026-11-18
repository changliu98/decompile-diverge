char * func0(char *s)

{
  char cVar1;
  size_t sVar2;
  char *pcVar3;
  int j_1;
  char temp;
  int k;
  int j;
  int i;
  int current_index;
  int out_index;
  char current [51];
  char *out;
  int len;
  char *s_local;
  
  sVar2 = strlen(s);
  pcVar3 = malloc((long)((int)sVar2 + 2));
  out_index = 0;
  current_index = 0;
  for (i = 0; i <= (int)sVar2; i = i + 1) {
    if ((s[i] == ' ') || (s[i] == '\0')) {
      for (j = 0; k = j, j < current_index + -1; j = j + 1) {
        while (k = k + 1, k < current_index) {
          if (current[k] < current[j]) {
            cVar1 = current[j];
            current[j] = current[k];
            current[k] = cVar1;
          }
        }
      }
      if (0 < out_index) {
        pcVar3[out_index] = ' ';
        out_index = out_index + 1;
      }
      for (j_1 = 0; j_1 < current_index; j_1 = j_1 + 1) {
        pcVar3[out_index] = current[j_1];
        out_index = out_index + 1;
      }
      current_index = 0;
    }
    else {
      current[current_index] = s[i];
      current_index = current_index + 1;
    }
  }
  pcVar3[out_index] = '\0';
  return pcVar3;
}
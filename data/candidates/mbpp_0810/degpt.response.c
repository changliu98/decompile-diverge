char * func0(int a,int b,int c,int d)

{
  char *pcVar1;
  int i_3;
  int i_2;
  int i_1;
  int i;
  int index;
  char *result;
  int total;
  int d_local;
  int c_local;
  int b_local;
  int a_local;
  
  total = 0;
  if (0 < a) {
    total = a;
  }
  if (0 < b) {
    total = b + total;
  }
  if (0 < c) {
    total = c + total;
  }
  if (0 < d) {
    total = d + total;
  }
  pcVar1 = malloc((long)(total + 1));
  if (pcVar1 == (char *)0x0) {
    perror("Failed to allocate memory");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  index = 0;
  for (i = 0; i < a; i = i + 1) {
    pcVar1[index] = 'p';
    index = index + 1;
  }
  for (i_1 = 0; i_1 < b; i_1 = i_1 + 1) {
    pcVar1[index] = 'q';
    index = index + 1;
  }
  for (i_2 = 0; i_2 < c; i_2 = i_2 + 1) {
    pcVar1[index] = 'r';
    index = index + 1;
  }
  for (i_3 = 0; i_3 < d; i_3 = i_3 + 1) {
    pcVar1[index] = 's';
    index = index + 1;
  }
  pcVar1[index] = '\0';
  return pcVar1;
}
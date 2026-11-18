char* func0(char** test_tup, int size) {
 int i;
 char delim[2];
 strcpy(func0::res, "");
 delim[0] = ' ';
 delim[1] = '\0';
 for (i = 0; i < size; i++) {
  strcat(func0::res, test_tup[i]);
  if (i < size - 1) {
   strcat(func0::res, delim);
  }
 }
 return func0::res;
}
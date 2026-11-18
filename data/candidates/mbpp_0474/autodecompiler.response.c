char *func0(char *arg0, char arg1, char arg2) {
 int i;
 strcpy(func0_str2, arg0);
 for (i = 0; ; ++i) {
  if ((unsigned)i >= strlen(func0_str2)) break;
  if (func0_str2[i] == arg1) func0_str2[i] = arg2;
 }
 return func0_str2;
}
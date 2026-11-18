char *func0(char *str[], int n)
{
 int i;
 strcpy(func0_ans, "");
 for (i = 0; ; i++) {
  if (i >= n) break;
  strcat(func0_ans, " ");
  strcat(func0_ans, str[i]);
 }
 return func0_ans;
}
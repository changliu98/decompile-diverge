char *func0(char *input)
{
 int has0 = 0;
 int has1 = 0;
 int hasOther = 0;
 int i = 0;
 char *ret;

 while (1) {
  if (i >= strlen(input)) {
   break;
  }

  if (input[i] == '0') {
   has0 = 1;
  } else if (input[i] == '1') {
   has1 = 1;
  } else {
   hasOther = 1;
   break;
  }

  i++;
 }

 if ((has0 || has1) && !hasOther) {
  ret = "YES";
 } else {
  ret = "NO";
 }

 return ret;
}
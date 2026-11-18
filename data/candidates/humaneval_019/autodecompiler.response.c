char *func0(char *in)
{
 char numstr[10][8] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
 int numcount[10];
 char tmp[10];
 int i, j, k, l;
 int inlen;

 memset(numcount, 0, sizeof(numcount));

 for (l = 0; *in; in++) {
  for (i = 0; *in && *in != ' '; in++, i++)
   tmp[i] = *in;
  tmp[i] = '\0';
  for (j = 0; j < 10; j++)
   if (!strcmp(tmp, numstr[j]))
   numcount[j]++;
 }

 for (l = 0, i = 0; i < 10; i++) {
  for (j = 0; j < numcount[i]; j++) {
   for (k = 0; numstr[i][k]; k++, l++)
    func0_out[l] = numstr[i][k];
   func0_out[l++] = ' ';
  }
 }

 if (l > 0)
  func0_out[--l] = '\0';
 else
  func0_out[0] = '\0';

 return func0_out;
}
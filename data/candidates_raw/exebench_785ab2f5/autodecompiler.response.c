void replaceLetters(char *str)
{
 int i, j;
 char *letters = "OIZEASGTBq";
 char *nums = "01234567890";

 for (i = 0; str[i] != '\0'; i++) {
  for (j = 0; letters[j] != '\0'; j++) {
   if (str[i] == letters[j]) {
    str[i] = nums[j];
    break;
   }
  }
 }
}
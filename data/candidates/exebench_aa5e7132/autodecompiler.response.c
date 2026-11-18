void GetWord(char *str1, char *str2, int size) {
 int i = 0;
 while(1) {
  char condition = (*str2 > 32) || (*str2 < 1);
  if(!condition) break;
  str2++;
 }
 while(1) {
  char condition = (*str2 > 32) || (*str2 < 1) || (i >= size-1);
  if(condition) break;
  *str1++ = *str2++;
  i++;
 }
 *str1 = 0;
}
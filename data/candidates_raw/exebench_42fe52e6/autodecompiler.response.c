int int_to_str(char *str, int num)
{
 int i;
 int j;
 int abs_num;
 int divisor;
 int remainder;
 int num_char_count;

 if (num == 0) {
  str[0] = '0';
  str[1] = '\0';
  return 2;
 }

 num_char_count = 0;
 divisor = 1;
 if (num < 0) {
  abs_num = num - (num << 1);
 } else {
  abs_num = num;
 }

 while (1) {
  remainder = abs_num % divisor;
  if (remainder == abs_num) {
   break;
  }
  num_char_count++;
  divisor *= 10;
 }

 if (num < 0) {
  num_char_count++;
 }

 divisor = 1;
 for (j = num_char_count - 1; j >= 0; j--) {
  remainder = abs_num % divisor;
  str[j] = ((abs_num - remainder) / divisor) % 10 + '0';
  divisor *= 10;
 }

 if (num < 0) {
  str[0] = '-';
 }

 str[num_char_count] = '\0';

 return num_char_count;
}
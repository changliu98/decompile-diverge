
void util_word_to_dec(char *dst, unsigned int w)
{
 char dig_array[11];
 int digval, i;

 for (i=0; i<10; i++) dig_array[i] = '0';
 dig_array[10] = '\0';
 i = 9;
 while (w > 0)
 {
  digval = w % 10;
  w = w / 10;
  dig_array[i--] = ((char)digval) + '0';
 }
 i = 0;

 while ((dig_array[i] == '0') && (i < 9)) i++;

 while (dig_array[i] != '\0')
 {
  *(dst++) = dig_array[i++];
 }
 *dst = '\0';
}

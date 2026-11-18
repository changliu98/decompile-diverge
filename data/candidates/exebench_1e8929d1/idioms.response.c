void convert2ASCII(char input, char *output)
{
 char temp = (char)(input / 16);
 if (temp < 10)
  output[0] = (char)(temp + '0');
 else
  output[0] = (char)(temp - 10 + 'a');
 temp = (char)(input % 16);
 if (temp < 10)
  output[1] = (char)(temp + '0');
 else
  output[1] = (char)(temp - 10 + 'a');
}
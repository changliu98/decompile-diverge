void octal_to_str(char *str, char octal)
{
 if (!str)
  return;

 str[0] = (octal & 0xc0) >> 6;
 str[1] = (octal & 0x38) >> 3;
 str[2] = (octal & 0x07);

 octal = 0;
 while (octal < 4) {
  str[octal] += '0';
  octal++;
 }
}
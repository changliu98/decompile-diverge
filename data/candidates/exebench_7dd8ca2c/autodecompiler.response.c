void hex_to_word(char *str, char c)
{
 if(str == NULL)
  return;

 str[0] = (c & 0xF0) >> 4;
 str[1] = (c & 0x0F);

 for(c = 0; c < 3; c++)
 {
  switch(str[c])
  {
   case 10:
   case 11:
   case 12:
   case 13:
   case 14:
   case 15:
    str[c] += 55;
    break;
   default:
    str[c] += 48;
    break;
  }
 }
}
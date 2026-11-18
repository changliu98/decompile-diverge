
void ltostr(unsigned int uiValue, char *pString)
{
 int i;
 unsigned int value;
 pString[0] = '\0';
 pString[8] = '\0';
 for(i =0; i<8; i++){
  value = uiValue & 0xf;
  value += 48;
  if(value >= 58)
   value += 7;
  pString[7-i] = (char)value;
  uiValue = uiValue >> 4;
 }
 return;
}

void IntToHex(unsigned int Value, char *HexString)
{
 unsigned int Temp;
 int i;

 HexString[0] = '\0';
 HexString[8] = '\0';

 for(i=0;i<9;i++)
 {
  if (i>8) break;
  Temp = Value & 0x0000000f;
  Temp += 0x30;
  if (Temp >= 0x3b) Temp += 0x07;
  HexString[7-i] = Temp;
  Value = Value >> 4;
 }
}
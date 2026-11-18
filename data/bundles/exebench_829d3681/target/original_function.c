void word2string(unsigned int value, char *buffer)
{
 char *p = buffer;
 static unsigned int _smth[5] = {10000, 1000, 100, 10, 1};


 if (value == 0) {

  *(unsigned int *)(p) = 0x002030;
  return;
 }


 for(int c = 0; c < 5; c++) {
  if(value / _smth[c] + p == buffer) continue;
  *p = value / _smth[c] + 0x30;
  p++;
  value %= _smth[c];

 }





 *(unsigned short *)(p) = 0x20;


}
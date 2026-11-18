
void itoa(unsigned short value, char* s)

{
 char tmp[16];
 unsigned short index=0;
 unsigned short max;

 if(value==0)
 {
  s[0]='0';
  s[1]=0;
  return;
 }

 while(value!=0)
 {
  tmp[index++]='0'+value%10;
  value/=10;
 }
 max=index;
 while(index)
 {
  s[max-index]=tmp[index-1];
  index--;
 }
 s[max]=0;
}

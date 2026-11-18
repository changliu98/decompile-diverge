void itox(unsigned short value, char* s)

{
 char tmp[16];
 unsigned short index=0;
 unsigned short max;
 unsigned short v;

 if(value==0)
 {
  s[0]='0';
  s[1]=0;
  return;
 }

 while(value!=0)
 {
  v=value%16;
  if(v<10)
    tmp[index++]='0'+v;
  else
    tmp[index++]='a'+(v-10);
  value/=16;
 }
 max=index;
 while(index)
 {
  s[max-index]=tmp[index-1];
  index--;
 }
 s[max]=0;
}
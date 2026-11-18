
int itochar(int num,char* strb)
{
 unsigned char i = 0;
 unsigned char j = 0;
 char stra[16];
 do
 {
  stra[i++]=num%10+48;
  num=num/10;
 }while(num);
 do
 {
  strb[j] = stra[i-j-1];
 }while((++j)<i);
 return j;
}

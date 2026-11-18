
int maxdig(int *num,int *max)
{
 static int dig;

 if (*num==0)
  return *max;
 dig=*num%10;
 if(dig>=*max)
  *max=dig;
 *num=*num/10;
 maxdig(num,max);


}

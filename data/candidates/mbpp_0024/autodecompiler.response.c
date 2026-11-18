int func0(int num_bin)
{
 int num_dec=0, i=0, digit;
 int num_bin_tmp=num_bin;

 while(1)
 {
  if(num_bin==0)
  break;

  digit=num_bin%10;
  num_dec+=digit*pow((double)2,i);
  num_bin/=10;
  i++;
 }

 return num_dec;
}
void chartobit(int num, char *bit)
{
 int i;
 for(i = 7; i > 0; i--)
 {
  bit[i] = (num%2 == 0)?'0':'1';
  num /= 2;
 }
 bit[0] = (num%2 == 0)?'0':'1';
}
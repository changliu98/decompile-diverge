int decToBin(int n, int *binary)
{
 int i=1, remainder, bits=0;

 while(i<=n)
 {
  i*=2;
  bits++;
 }

 for(i=(bits-1); i>=0; i--)
 {
  remainder = n%2;

  if(remainder < 0)
  {
   binary[bits-1-i] = 0;
  }
  else
  {
   binary[bits-1-i] = remainder;
   n = n - i;
  }
 }
 return(bits);
}
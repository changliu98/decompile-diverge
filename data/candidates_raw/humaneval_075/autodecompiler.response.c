int isSquare(int n)
{
 int i, c;
 int isSquare;

 if(n < 3)
 {
  isSquare = 0;
 }
 else
 {
  c = 0;
  for(i = 2; ; i++)
  {
   if(i * i > n)
   {
    break;
   }

   while(n % i == 0)
   {
    n /= i;
    c++;
   }
  }

  if(n > 1)
  {
   c++;
  }

  isSquare = (c == 3);
 }

 return isSquare;
}
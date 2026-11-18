void removeslave(int *slave, int n)
{
  int i;

  for (i = 9; i >= 0; i--)
    {
      if (slave[i])
 {
   slave[i] = 0;
   n--;
 }
      if (n == 0)
 break;
    }
}
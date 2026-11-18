void
chartobit(int val, char v[])
{
 int i;
 for (i = 7; i > 0; --i)
  {
   v[i] = (val % 2 == 1) ? '1' : '0';
   val /= 2;
  }
 v[0] = (val % 2 == 1) ? '1' : '0';
}
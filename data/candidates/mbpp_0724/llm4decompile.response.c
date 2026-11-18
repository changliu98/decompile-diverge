int func0(int base, int power)
{
 int digits[1000];
 int size = 1;
 int i, p, carry, sum;

 digits[0] = 1;

 for (p = 0; p < power; p++)
 {
  carry = 0;
  for (i = 0; i < size; i++)
  {
   long tmp = digits[i] * base + carry;
   digits[i] = tmp % 10;
   carry = tmp / 10;
  }
  while (carry > 0)
  {
   digits[size] = carry % 10;
   size++;
   carry /= 10;
  }
 }

 sum = 0;
 for (i = 0; i < size; i++)
  sum += digits[i];

 return sum;
}
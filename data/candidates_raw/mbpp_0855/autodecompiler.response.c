int even_parity(int value)
{
 int count = 0;
 while (value) {
  value &= value - 1;
  count++;
 }
 return !(count % 2);
}
float func0(int a, int b)
{
 int temp = b;
 int digits = 0;

 if (temp) {
  while (temp) {
   temp /= 10;
   digits++;
  }
 } else {
  digits = 1;
 }

 return (float)a + (float)b / pow(10.0, digits);
}
int func0(int number)
{
 int sum;
 int count;

 if(number % 2 != 0)
 {
  printf("Invalid Input\n");
  sum = -1;
 }
 else
 {
  sum = 0;
  count = 0;
  while(1)
  {
   if(number < 2)
    break;
   count++;
   sum += number;
   number -= 2;
  }
  sum /= count;
 }

 return sum;
}
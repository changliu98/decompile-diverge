int func0(int *input, int size)
{
 int max = -(1<<31), min = (1<<31)-1;
 int i;

 for(i = 0; ; ++i)
 {
  if(i >= size)
   break;
  if(input[i] > max)
   max = input[i];
  if(input[i] < min)
   min = input[i];
 }

 return max + min;
}
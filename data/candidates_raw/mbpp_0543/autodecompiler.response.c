int calculate_number_length(long int num1, long int num2)
{
  long int sum = num1 + num2;
  int num_length = 0;

  while(1)
  {
    if(sum > 0)
    {
      sum = sum / 10;
      num_length++;
    }
    else
      break;
  }

  return num_length;
}
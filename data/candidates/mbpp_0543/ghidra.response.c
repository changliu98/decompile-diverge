int func0(longlong num1,longlong num2)

{
  int count;
  longlong number;
  longlong num2_local;
  longlong num1_local;
  
  count = 0;
  for (number = num1 + num2; 0 < number; number = number / 10) {
    count = count + 1;
  }
  return count;
}
double average(int numbers[], int numbersCount) {
 int i, sum = 0;
 for (i = 0; i < numbersCount; ++i)
  sum += numbers[i];
 return (double)sum / numbersCount;
}
double func0(int numbers[], int numbersCount) {
 int i, sum = 0;
 for (i = 0; ; ++i) {
  if (i >= numbersCount)
   break;
  sum += numbers[i];
 }
 return (double)sum / (double)numbersCount;
}
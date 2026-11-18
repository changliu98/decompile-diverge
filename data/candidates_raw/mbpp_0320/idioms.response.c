int sumsquaredif(int n)
{
  int sumofsquares = 0;
  int squareofsum = 0;
  int i;
  for (i = 1; i <= n; i++)
  {
    sumofsquares += i * i;
    squareofsum += i;
  }
  return squareofsum * squareofsum - sumofsquares;
}